//
//  CPDFDeferredSignSession.h
//  ComPDFKit
//
//  Copyright © 2014-2026 PDF Technologies, Inc. All Rights Reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE ComPDFKit LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <ComPDFKit/CPDFKitPlatform.h>

NS_ASSUME_NONNULL_BEGIN

@class CPDFDocument;

/**
 * Two-phase ("deferred") signing, for a signer that never releases its private key:
 * an HSM, a UKey, a cloud KMS, or your own signing service.
 *
 * Phase 1 creates a signature field, reserves a `/Contents` placeholder, writes the real
 * `/ByteRange` and hands back a hash. That hash goes to the external signer. Phase 2 writes
 * what the signer returned into the placeholder.
 *
 * Nothing here touches the filesystem: PDFs go in and come out as NSData.
 *
 * The two phases may run in different processes or on different machines. Phase 2 does not
 * need the CPDFDocument back — everything it needs is in the session string. What must
 * survive between them is: the prepared PDF bytes, `session`, and the signer's answer.
 *
 * Typical flow:
 *
 *     CPDFDeferredSignPrepareOptions *options = [[CPDFDeferredSignPrepareOptions alloc] init];
 *     options.fieldName = @"Signature1";
 *     options.pageIndex = 0;
 *     options.rect = CGRectMake(100, 100, 200, 80);
 *
 *     CPDFDeferredSignPrepareResult *prepared =
 *         [CPDFDeferredSignSession prepareWithDocument:document
 *                                           sourceData:sourceData
 *                                              options:options];
 *
 *     // Hand prepared.hashToSign to the signer; keep prepared.preparedData and
 *     // prepared.session until the answer comes back.
 *
 *     CPDFDeferredSignFillResult *signed =
 *         [CPDFDeferredSignSession fillSession:prepared.session
 *                                 preparedData:prepared.preparedData
 *                               signatureValue:signatureFromSigner
 *                                      options:fillOptions];
 *
 * Both phases report failure through `errorCode` / `errorMessage` rather than by returning
 * nil. Codes prefixed `sdk.` mean the arguments were rejected before any work started;
 * codes prefixed `session.` come from the signing engine.
 */

#pragma mark - Digest and hash mode

/**
 * Digest algorithm applied to the bytes being signed.
 *
 * SHA-256 is the only value this API exposes, on the core team's recommendation. The core
 * library also implements SHA-384 and SHA-512, and the wider signature API carries SM3;
 * they are held back here until there is a caller for them, so that every value in this
 * enum is one the deferred-signing path has actually been exercised with.
 *
 * `Unknown` is rejected with `sdk.invalid_argument` rather than quietly downgraded — a
 * caller must never hand its signer a hash of a kind it did not ask for. The same is true
 * of any value added later but not yet wired up.
 */
typedef NS_ENUM(NSInteger, CPDFSignatureDigestAlgorithm) {
    CPDFSignatureDigestAlgorithmSHA256 = 0,
    CPDFSignatureDigestAlgorithmUnknown,
};

/**
 * What `hashToSign` actually contains.
 *
 * Prefer `DocumentDigest`. It produces the same hash for both fill methods, so the choice
 * between "the signer returns a whole container" and "the signer returns a raw signature
 * value" can be deferred until the signer's answer comes back.
 */
typedef NS_ENUM(NSInteger, CPDFDeferredSignHashMode) {
    /**
     * `hashToSign` is the plain digest of the bytes covered by `/ByteRange`. Fill with
     * either `fillSession:preparedData:containerDER:verifiesMessageDigest:` or
     * `fillSession:preparedData:signatureValue:options:`.
     */
    CPDFDeferredSignHashModeDocumentDigest = 0,

    /**
     * `hashToSign` is the digest of the DER-encoded CMS signedAttrs built at prepare time,
     * which binds signing time and certificate into the signature. Requires
     * `signerCertificateDER`, and only `fillSession:preparedData:signatureValue:options:`
     * can complete it.
     */
    CPDFDeferredSignHashModeSignedAttributes,
};

#pragma mark - Phase 1 options

/**
 * Phase 1 input.
 */
@interface CPDFDeferredSignPrepareOptions : NSObject

/**
 * Signature field name (`/T`). Empty picks the first unused "SignatureN", the same scheme
 * Acrobat uses.
 *
 * Must not contain '.', and must not already belong to another top-level field: PDF treats
 * two fields of the same name as one field, so the new signature would be folded into the
 * existing one instead of standing on its own.
 */
@property (nonatomic,copy) NSString *fieldName;

/**
 * Page the signature field is created on, zero-based.
 */
@property (nonatomic,assign) NSInteger pageIndex;

/**
 * Field rectangle in page coordinates. `CGRectZero` creates an invisible signature.
 *
 * This only sets the area — no `/AP` appearance stream is generated. A visible signature
 * appearance has to be produced before preparing.
 */
@property (nonatomic,assign) CGRect rect;

/** Defaults to `CPDFDeferredSignHashModeDocumentDigest`. */
@property (nonatomic,assign) CPDFDeferredSignHashMode hashMode;

/** Defaults to `CPDFSignatureDigestAlgorithmSHA256`. */
@property (nonatomic,assign) CPDFSignatureDigestAlgorithm digestAlgorithm;

/**
 * `/Contents` placeholder capacity in container bytes; the hex region written into the
 * prepared PDF is twice this long. 0 selects the default of 16384.
 *
 * The capacity is frozen once phase 1 finishes — a container that does not fit cannot be
 * filled in, and the only remedy is to prepare again with a larger value. Raise it when the
 * container will carry a long certificate chain or a timestamp.
 *
 * Values above `INT_MAX` are rejected with `sdk.invalid_argument` rather than truncated.
 */
@property (nonatomic,assign) NSInteger estimatedContentsSize;

/**
 * DER-encoded signer certificate. Required for `SignedAttributes`; optional otherwise,
 * where it can also be supplied at fill time instead.
 */
@property (nonatomic,copy,nullable) NSData *signerCertificateDER;

/**
 * DER-encoded intermediate and root certificates, embedded so verifiers can build the chain
 * offline. Optional.
 */
@property (nonatomic,copy,nullable) NSArray<NSData *> *certificateChainDER;

/**
 * Signing time baked into signedAttrs. nil uses the current time.
 *
 * Only meaningful in `SignedAttributes` mode, where it is frozen into the session: it has
 * already been hashed into what the signer signs, so it cannot be changed afterwards.
 *
 * A date of exactly 1970-01-01T00:00:00Z is indistinguishable from nil.
 */
@property (nonatomic,copy,nullable) NSDate *signingTime;

/**
 * Add the ESS signing-certificate-v2 signed attribute, binding the signature to this exact
 * certificate. Defaults to YES. Not required by Acrobat; turn it off if the signer's
 * toolchain cannot cope with it. Only meaningful in `SignedAttributes` mode.
 */
@property (nonatomic,assign) BOOL includesSigningCertificateV2;

@end

#pragma mark - Phase 1 result

/**
 * Phase 1 output.
 */
@interface CPDFDeferredSignPrepareResult : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@property (nonatomic,readonly) BOOL success;

/**
 * The prepared PDF: the source document plus an empty signature field and a zero-filled
 * `/Contents` placeholder.
 *
 * Phase 2 reads these bytes again, so they must be kept and handed back unchanged. They may
 * be stored or moved anywhere; the session does not record a location. What they may not do
 * is change — a single altered byte fails the fill with `session.fill_failed`.
 */
@property (nonatomic,readonly,copy,nullable) NSData *preparedData;

/**
 * The signature field that was created: the requested name, or the generated "SignatureN".
 */
@property (nonatomic,readonly,copy,nullable) NSString *fieldName;

/**
 * The bytes to hand to the external signer.
 *
 * @warning Already digested. This is a raw hash, not a DER DigestInfo and not base64.
 * Confirm the signing service takes a precomputed hash — a service that digests its input
 * again produces a double hash and a signature nothing will verify.
 *
 * Base64 it with `-[NSData base64EncodedStringWithOptions:]` when the transport is JSON or
 * XML; decode the answer with `-[NSData initWithBase64EncodedString:options:]`.
 */
@property (nonatomic,readonly,copy,nullable) NSData *hashToSign;

/**
 * "SHA256", "SHA384" or "SHA512". The external signer must use this same digest.
 */
@property (nonatomic,readonly,copy,nullable) NSString *digestAlgorithm;

/**
 * Digest of the `/ByteRange`-covered bytes. Equals `hashToSign` in `DocumentDigest` mode.
 */
@property (nonatomic,readonly,copy,nullable) NSData *documentDigest;

/**
 * Offset of the first hex digit inside `/Contents`, counted from the start of
 * `preparedData`; the byte before it is the '<'. Only needed to describe the placeholder to
 * a signer that writes the container itself. Filling through this class does not need it.
 */
@property (nonatomic,readonly) unsigned long long contentsOffset;

/**
 * Placeholder capacity in container bytes. The hex region in `preparedData` is twice this
 * long.
 */
@property (nonatomic,readonly) NSInteger contentsSize;

/**
 * DER-encoded signedAttrs. nil unless `hashMode` was `SignedAttributes`.
 */
@property (nonatomic,readonly,copy,nullable) NSData *signedAttributesDER;

/**
 * Opaque, printable session state — plain ASCII, safe in a file, a database column or an
 * HTTP payload. Persist it as-is; do not parse and rebuild it. Phase 2 takes it back
 * verbatim.
 */
@property (nonatomic,readonly,copy,nullable) NSString *session;

/**
 * nil on success. `sdk.invalid_argument` / `sdk.document_missing` mean the arguments were
 * rejected before any work started; `sdk.license_denied` means the license does not allow
 * digital signatures. Other codes come from the signing engine.
 */
@property (nonatomic,readonly,copy,nullable) NSString *errorCode;

/** A human-readable description of the failure. nil on success. */
@property (nonatomic,readonly,copy,nullable) NSString *errorMessage;

@end

#pragma mark - Phase 2 options and result

/**
 * Certificate material for the raw-signature-value fill.
 *
 * Phase 2 usually runs somewhere else than phase 1, so the certificate is passed in here
 * rather than assumed to be around. What is left nil falls back to whatever phase 1 stored
 * in the session, which is what a single-process caller gets for free.
 *
 * Only consulted for `DocumentDigest` sessions. In `SignedAttributes` mode the certificate
 * is already hashed into the attributes the signer signed, so the session copy is the only
 * one that can be correct and anything set here is ignored.
 */
@interface CPDFDeferredSignFillOptions : NSObject

@property (nonatomic,copy,nullable) NSData *signerCertificateDER;

@property (nonatomic,copy,nullable) NSArray<NSData *> *certificateChainDER;

@end

/**
 * Phase 2 output.
 */
@interface CPDFDeferredSignFillResult : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@property (nonatomic,readonly) BOOL success;

/** The finished, signed PDF. nil unless `success`. */
@property (nonatomic,readonly,copy,nullable) NSData *signedData;

/**
 * nil on success. Common values:
 *
 * - `sdk.invalid_argument` — an argument was empty or malformed; nothing was attempted.
 * - `session.invalid` — the session string is not the one phase 1 produced.
 * - `session.container_invalid` — the container is not parseable PKCS#7 SignedData.
 * - `session.container_too_large` — raise `estimatedContentsSize` and prepare again.
 * - `session.message_digest_mismatch` — the container was signed over a different document.
 * - `session.fill_failed` — the prepared bytes are not the ones phase 1 produced.
 */
@property (nonatomic,readonly,copy,nullable) NSString *errorCode;

/** A human-readable description of the failure. nil on success. */
@property (nonatomic,readonly,copy,nullable) NSString *errorMessage;

@end

#pragma mark - CPDFDeferredSignSession

@interface CPDFDeferredSignSession : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/**
 * Phase 1. Creates the signature field, returns the prepared PDF and the hash the external
 * signer must sign.
 *
 * @warning `document` must be the document loaded from exactly these `sourceData` bytes,
 * with no unsaved changes — the digest is computed over them. A document opened from a file
 * satisfies this when `sourceData` is that file's contents, which is the usual way to use
 * this: keep the *prepared* PDF out of the filesystem even though the source came from it.
 *
 * @warning The call modifies `document` in memory. Do not save it afterwards. To keep
 * working on the file, load the prepared PDF instead.
 *
 * One call creates one signature field. To sign twice, run the whole flow again with the
 * first signed PDF as the source.
 *
 * Requires the digital-signature license. Phase 2 does not re-check it.
 *
 * @param document The document loaded from `sourceData`.
 * @param sourceData The source PDF.
 * @param options Field placement, digest and certificate settings.
 *
 * @return Never nil. On success, `preparedData` and `session` must both be kept — phase 2
 * needs them.
 */
+ (CPDFDeferredSignPrepareResult *)prepareWithDocument:(CPDFDocument *)document
                                            sourceData:(NSData *)sourceData
                                               options:(CPDFDeferredSignPrepareOptions *)options;

/**
 * Phase 2, for a signer that returns a finished detached CMS/PKCS#7 SignedData.
 *
 * The prepared PDF is validated first — length, placeholder position, and the `/ByteRange`
 * digest — before a single byte is produced, so a rejected fill can be retried with the same
 * `preparedData`.
 *
 * @warning Blocks on crypto over the whole PDF. Call it off the main thread.
 *
 * @param session The session string from phase 1.
 * @param preparedData Exactly the bytes phase 1 returned.
 * @param containerDER The DER-encoded detached CMS/PKCS#7 container.
 * @param verifiesMessageDigest When YES and the container carries signedAttrs, its
 * messageDigest attribute is compared against the digest recorded in the session. This is
 * what catches a container produced over some other document. Containers without signedAttrs
 * skip the check. Leave it YES unless the signer is known to omit signedAttrs.
 *
 * @return Never nil.
 */
+ (CPDFDeferredSignFillResult *)fillSession:(NSString *)session
                               preparedData:(NSData *)preparedData
                               containerDER:(NSData *)containerDER
                      verifiesMessageDigest:(BOOL)verifiesMessageDigest;

/**
 * Phase 2, for a signer that only performs the private-key operation. The detached PKCS#7
 * container is assembled around `signatureValue` for you.
 *
 * What gets assembled follows the session's hash mode: a `DocumentDigest` session produces
 * SignedData with no signed attributes, a `SignedAttributes` session one carrying the
 * attributes frozen at prepare time.
 *
 * @warning Blocks on crypto over the whole PDF. Call it off the main thread.
 *
 * @param session The session string from phase 1.
 * @param preparedData Exactly the bytes phase 1 returned.
 * @param signatureValue Raw signature bytes — for RSA the modulus-sized block, for ECDSA the
 * DER `SEQUENCE { r, s }`. Never a container. RSA-PSS is not supported by this assembly
 * path; confirm the padding with the signing service.
 * @param options The signer certificate, when phase 1 did not already put it in the session.
 * Ignored for a `SignedAttributes` session. Pass nil to use the session's copy.
 *
 * @return Never nil.
 */
+ (CPDFDeferredSignFillResult *)fillSession:(NSString *)session
                               preparedData:(NSData *)preparedData
                             signatureValue:(NSData *)signatureValue
                                    options:(nullable CPDFDeferredSignFillOptions *)options;

@end

NS_ASSUME_NONNULL_END
