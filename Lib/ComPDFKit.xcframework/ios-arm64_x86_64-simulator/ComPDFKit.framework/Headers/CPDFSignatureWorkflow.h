//
//  CPDFSignatureWorkflow.h
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
#import <ComPDFKit/CPDFTSAClient.h>
#import <ComPDFKit/CPDFSignExternal.h>
#import <ComPDFKit/CPDFSignatureValidation.h>
#import <ComPDFKit/CPDFSignatureWidgetAnnotation.h>

NS_ASSUME_NONNULL_BEGIN

@class CPDFDocument;
@class CPDFExternalSigningSessionImportResult;

#pragma mark - Profile

/// The signature profile a one-shot signing call produces.
///
/// @note Baseline-LT and Baseline-LTA are not here. They need LTV material and
/// document-timestamp orchestration that a single call cannot express — use
/// `CPDFPadesSigner`, which drives this workflow and then adds those passes.
typedef NS_ENUM(NSInteger, CPDFSignatureProfile) {
    /// A plain `adbe.pkcs7.detached` signature. The widest-compatibility choice.
    CPDFSignatureProfilePKCS7Detached = 0,
    /// PAdES Baseline-B: an `ETSI.CAdES.detached` signature, no timestamp.
    CPDFSignatureProfilePAdESB,
    /// PAdES Baseline-T: Baseline-B plus a signature timestamp. Needs a TSA.
    CPDFSignatureProfilePAdEST,
    /// A document timestamp (`ETSI.RFC3161`) rather than an identity signature.
    /// Pair with `+[CPDFSigningIdentity documentTimestampIdentityWithServerURL:]`.
    CPDFSignatureProfileDocumentTimestamp,
};

#pragma mark - Signing identity

/// The key material a signing call uses.
///
/// The two factories cover the two things the shipped core library can sign with:
/// a PKCS#12 bundle, and a bare timestamp authority for document timestamps. For a
/// key the SDK cannot hold — a card, an HSM, a remote service — use
/// `CPDFSignExternal` with `-signExternalDetachedPKCS7ToPath:options:signer:` instead
/// and leave `CPDFSignatureCreateOptions.signer` nil.
@interface CPDFSigningIdentity : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/// A signer backed by a PKCS#12 (`.pfx` / `.p12`) file.
///
/// @param path Filesystem path to the PKCS#12 bundle.
/// @param password The bundle password, or nil when it has none.
+ (instancetype)identityWithPKCS12Path:(NSString *)path
                              password:(nullable NSString *)password;

/// As above, with an RFC 3161 timestamp authority the core library contacts itself.
///
/// @param timestampServerURL The TSA endpoint. Prefer `tsaClient` when you need
/// authentication, a proxy, or control over the transport — see its documentation.
+ (instancetype)identityWithPKCS12Path:(NSString *)path
                              password:(nullable NSString *)password
                    timestampServerURL:(nullable NSString *)timestampServerURL;

/// A document-timestamp signer. It carries no identity: the resulting signature only
/// attests that the bytes existed at the time the TSA asserts.
+ (instancetype)documentTimestampIdentityWithServerURL:(NSString *)timestampServerURL;

/// A document-timestamp signer driven by your own TSA client.
+ (instancetype)documentTimestampIdentityWithTSAClient:(id<CPDFTSAClient>)tsaClient;

/// A timestamp client that replaces the core library's built-in HTTP transport.
///
/// Set this when the TSA needs credentials, a client certificate, or a proxy the
/// core library's blocking socket code cannot provide. It takes precedence over any
/// `timestampServerURL` passed to the factory.
///
/// @note Setting this on a document-timestamp identity created from a URL replaces
/// that URL's transport, not the URL itself.
@property (nonatomic,strong,nullable) id<CPDFTSAClient> tsaClient;

@end

#pragma mark - Create options

/// Everything one signing call needs.
@interface CPDFSignatureCreateOptions : NSObject

/// Defaults to `PKCS7Detached`.
@property (nonatomic,assign) CPDFSignatureProfile profile;

/// The signature field to sign. Empty or nil creates a new field with a generated name.
@property (nonatomic,copy,nullable) NSString *fieldName;

/// Zero-based page for a newly created widget. Defaults to -1, meaning the SDK picks.
@property (nonatomic,assign) NSInteger pageIndex;

/// The widget rectangle in PDF page space — origin bottom-left, points.
@property (nonatomic,assign) CGRect bounds;

/// Whether the signature has a visible appearance. Defaults to `YES`.
/// An invisible signature protects the document just as well; it simply draws nothing.
@property (nonatomic,assign) BOOL visible;

@property (nonatomic,copy,nullable) NSString *reason;
@property (nonatomic,copy,nullable) NSString *location;
@property (nonatomic,copy,nullable) NSString *contact;

/// The `/App` producer string recorded in the signature dictionary.
@property (nonatomic,copy,nullable) NSString *signatureCreator;

/// Bytes reserved for the `/Contents` placeholder. 0 — the default — uses the SDK's
/// own estimate.
///
/// @note Raise this when the container will be unusually large: a long certificate
/// chain, an embedded timestamp token, or LTV material. A container that does not fit
/// the placeholder fails the signing call rather than silently truncating.
@property (nonatomic,assign) NSInteger estimatedContentsSize;

/// Whether to reload the signed file and produce `postSignReport`. Defaults to `YES`.
///
/// @note This re-reads and re-parses the output. Turn it off for bulk signing where
/// you validate separately.
@property (nonatomic,assign) BOOL verifiesAfterSign;

/// The key material. Required for every call except the external-signing ones, where
/// the signer is passed to the method directly.
@property (nonatomic,strong,nullable) CPDFSigningIdentity *signer;

/// The visible appearance. Ignored when `visible` is `NO`.
///
/// Reuses the existing appearance type, so a configuration you already build for
/// `-[CPDFSignatureWidgetAnnotation signAppearanceConfig:]` works unchanged.
///
/// @note The content type is derived from what you actually set — text, image, or
/// both. Ink paths, font size, and rotation are not exposed here; a signature that
/// needs them must go through `CPDFSignatureWidgetAnnotation`.
@property (nonatomic,strong,nullable) CPDFSignatureConfig *appearance;

/// A timestamp client for the signature timestamp of a PAdES-T signature.
///
/// Equivalent to setting `CPDFSigningIdentity.tsaClient`; set either. When both are
/// set, this one wins.
@property (nonatomic,strong,nullable) id<CPDFTSAClient> tsaClient;

/// Digest choice and weak-algorithm rules for this signing operation.
///
/// @note The core library does not propagate this into `postSignValidationOptions`,
/// so a custom policy would otherwise be ignored by the post-sign check.
/// `CPDFSignatureWorkflow` copies it across for you: the
/// post-sign report is always evaluated under the policy you signed with, and
/// `postSignValidationOptions.algorithmPolicy` is overwritten. To verify under a
/// different policy, call `-validatePath:options:` separately.
@property (nonatomic,copy) CPDFSignatureAlgorithmPolicy *algorithmPolicy;

/// Which checks the post-sign validation runs. Only consulted when
/// `verifiesAfterSign` is `YES`.
///
/// @warning `checksRevocation` defaults to `NO`. Turning it on makes the signing call
/// perform OCSP / CRL fetches inline — see the threading note on `CPDFSignatureWorkflow`.
@property (nonatomic,copy) CPDFSignatureValidationOptions *postSignValidationOptions;

@end

#pragma mark - Create result

/// The outcome of a signing call.
@interface CPDFSignatureCreateResult : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/// Whether a signed file was produced. Check this before anything else — a `YES` here
/// with a failing `postSignReport` means the file was written but does not verify.
@property (nonatomic,readonly) BOOL success;

/// The field that was signed, including a name the SDK generated for you.
@property (nonatomic,readonly,copy) NSString *fieldName;

@property (nonatomic,readonly,copy) NSString *outputPath;

/// The `/SubFilter` actually written, e.g. `ETSI.CAdES.detached` for PAdES.
@property (nonatomic,readonly,copy) NSString *subFilter;

@property (nonatomic,readonly,copy) NSString *digestAlgorithm;

/// The post-sign verification report. Meaningful only when
/// `CPDFSignatureCreateOptions.verifiesAfterSign` was `YES`.
@property (nonatomic,readonly,strong) CPDFSignatureValidationReport *postSignReport;

/// What went wrong. Non-empty when `success` is `NO`.
@property (nonatomic,readonly,copy) NSArray<CPDFValidationReportItem *> *errors;

/// Non-fatal findings — a weak algorithm that policy only warns about, an
/// unreachable revocation responder.
@property (nonatomic,readonly,copy) NSArray<CPDFValidationReportItem *> *warnings;

@end

#pragma mark - Validation options / result

@interface CPDFSignatureWorkflowValidationOptions : NSObject <NSCopying>

/// The single field to validate. Nil or empty — the default — validates every
/// signature in the document.
@property (nonatomic,copy,nullable) NSString *fieldName;

@property (nonatomic,copy) CPDFSignatureValidationOptions *validationOptions;

@end

/// The document-level verification result.
@interface CPDFSignatureWorkflowValidationResult : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/// `YES` only when `overallStatus` is `Valid`.
///
/// @warning This tracks the verdict, not whether the run completed: a document that was
/// examined end to end and produced a full report still reports `success == NO` whenever
/// the verdict is `Invalid` or `Indeterminate`, with `errors` left empty. So a `NO` here
/// does not mean validation failed to run, and it does not mean the signature is broken —
/// an untrusted timestamp chain or missing LTV material lands in the same bucket. Read
/// `overallStatus` and `reports` to tell those cases apart.
@property (nonatomic,readonly) BOOL success;

@property (nonatomic,readonly,copy) NSString *inputPath;

/// The aggregate verdict over every signature examined.
@property (nonatomic,readonly) CPDFValidationStatus overallStatus;

/// One report per signature, in document order.
@property (nonatomic,readonly,copy) NSArray<CPDFSignatureValidationReport *> *reports;

@property (nonatomic,readonly,copy) NSArray<CPDFValidationReportItem *> *errors;
@property (nonatomic,readonly,copy) NSArray<CPDFValidationReportItem *> *warnings;

@end

#pragma mark - Two-phase external signing

/// The state of a signature placeholder waiting to be filled.
///
/// Sign `documentDigest` with whatever holds the key, wrap the result in a CMS
/// container — `+[CPDFDetachedPKCS7ContainerOptions buildDetachedPKCS7ContainerWithOptions:]`
/// will do that — and pass both back through `CPDFFillSignatureOptions`.
@interface CPDFPreparedExternalSignatureInfo : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/// The PDF holding the placeholder. Do not modify this file: every byte offset below
/// refers to it, and the digest was taken over its bytes.
@property (nonatomic,readonly,copy) NSString *preparedPath;

@property (nonatomic,readonly,copy) NSString *fieldName;

/// The four ByteRange integers, as written in the prepared PDF.
@property (nonatomic,readonly,copy) NSArray<NSNumber *> *byteRange;

/// Offset of the `/Contents` placeholder within the prepared file.
@property (nonatomic,readonly) unsigned long contentsOffset;

/// Size of the placeholder in bytes. The DER container must fit within it.
@property (nonatomic,readonly) NSInteger contentsSize;

@property (nonatomic,readonly) unsigned long fileSize;

/// The digest algorithm's name, as recorded by the core library.
@property (nonatomic,readonly,copy) NSString *digestAlgorithm;

/// The digest over the ByteRange bytes. This is what gets signed.
@property (nonatomic,readonly,copy) NSData *documentDigest;

/// A stable, line-oriented ASCII rendering of this state.
///
/// Persist or transmit this rather than the object: it is versioned and independent
/// of in-memory layout, so it survives the trip to another process or machine.
- (NSString *)exportSessionMetadata;

/// Write `-exportSessionMetadata` to a file.
- (BOOL)saveSessionMetadataToPath:(NSString *)metadataPath;

/// Reconstruct from text produced by `-exportSessionMetadata`.
+ (CPDFExternalSigningSessionImportResult *)importSessionMetadata:(NSString *)metadata;

/// Reconstruct from a file written by `-saveSessionMetadataToPath:`.
+ (CPDFExternalSigningSessionImportResult *)loadSessionMetadataFromPath:(NSString *)metadataPath;

@end

@interface CPDFPrepareSignatureResult : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@property (nonatomic,readonly) BOOL success;

/// Nil when `success` is `NO`.
@property (nonatomic,readonly,strong,nullable) CPDFPreparedExternalSignatureInfo *preparedSignature;

/// The same text `-[CPDFPreparedExternalSignatureInfo exportSessionMetadata]` returns,
/// provided here so a cross-process caller need not make a second call.
@property (nonatomic,readonly,copy) NSString *externalSigningSessionMetadata;

@property (nonatomic,readonly,copy) NSArray<CPDFValidationReportItem *> *errors;
@property (nonatomic,readonly,copy) NSArray<CPDFValidationReportItem *> *warnings;

@end

@interface CPDFExternalSigningSessionImportResult : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@property (nonatomic,readonly) BOOL success;
@property (nonatomic,readonly,strong,nullable) CPDFPreparedExternalSignatureInfo *preparedSignature;
@property (nonatomic,readonly,copy) NSString *errorCode;
@property (nonatomic,readonly,copy) NSString *errorMessage;

@end

@interface CPDFFillSignatureOptions : NSObject

/// The placeholder to fill, from `-prepareSignatureToPath:options:` or from importing
/// its metadata.
@property (nonatomic,strong,nullable) CPDFPreparedExternalSignatureInfo *preparedSignature;

/// The complete DER-encoded CMS / PKCS#7 container. Not a bare signature value —
/// use `+[CPDFDetachedPKCS7ContainerOptions buildDetachedPKCS7ContainerWithOptions:]`
/// to wrap one.
@property (nonatomic,copy,nullable) NSData *signatureContents;

/// Whether to reload the filled file and produce `postFillReport`. Defaults to `YES`.
@property (nonatomic,assign) BOOL verifiesAfterFill;

@property (nonatomic,copy) CPDFSignatureValidationOptions *postFillValidationOptions;

@end

@interface CPDFFillSignatureResult : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@property (nonatomic,readonly) BOOL success;
@property (nonatomic,readonly,copy) NSString *outputPath;
@property (nonatomic,readonly,strong) CPDFSignatureValidationReport *postFillReport;
@property (nonatomic,readonly,copy) NSArray<CPDFValidationReportItem *> *errors;
@property (nonatomic,readonly,copy) NSArray<CPDFValidationReportItem *> *warnings;

@end

#pragma mark - Workflow

/// One-call signing and structured verification.
///
/// This sits above `CPDFSignature` / `CPDFSigner`: rather than handing you a signature
/// dictionary to populate, it creates the field, signs it, writes the output, and —
/// unless you turn that off — reloads the result and reports on it. The lower-level
/// API is unchanged and still available for callers that need the finer control.
///
/// ## Threading
///
/// Every method is synchronous and blocking. Signing reads and rewrites the whole
/// file; verification reads it again. When a TSA is configured, or when
/// `checksRevocation` is on, the core library performs network I/O inline with no
/// timeout you can set from here.
///
/// @warning Do not call any of these from the main thread. Supply a
/// `CPDFTSAClient` — `CPDFURLSessionTSAClient`, for instance — rather than a bare
/// `timestampServerURL` whenever you need a timeout, a proxy, or App Transport
/// Security compliance: the core library's own HTTP client bypasses `NSURLSession`
/// entirely.
///
/// ## Choosing a method
///
/// - The key is a PKCS#12 file → `-signToPath:options:`
/// - The key is on a card, in an HSM, or behind a service → `-signExternalDetachedPKCS7ToPath:options:signer:`
/// - The container comes back whole from a signing appliance → `-signWithContainerToPath:options:container:`
/// - Signing happens in another process or on another machine →
///   `-prepareSignatureToPath:options:`, then `-fillSignatureAtPath:options:`
@interface CPDFSignatureWorkflow : NSObject

/// A workflow with no document. Only the path-based `-validatePath:options:` works;
/// the signing methods report an input error.
- (instancetype)init NS_DESIGNATED_INITIALIZER;

/// A workflow bound to an open document.
///
/// @param document The document to sign or validate. It must be backed by a file on
/// disk: the source bytes come from `document.documentURL`, not from the in-memory
/// object. Unsaved edits are not included — save first.
- (instancetype)initWithDocument:(CPDFDocument *)document NS_DESIGNATED_INITIALIZER;

@property (nonatomic,readonly,weak,nullable) CPDFDocument *document;

#pragma mark Signing

/// Sign the document and write the result to `savePath`.
///
/// @param savePath Where to write the signed PDF. Signing never edits in place.
/// @param options The profile, field, appearance, and signer.
/// @return The outcome, including the post-sign report when `verifiesAfterSign` is on.
- (CPDFSignatureCreateResult *)signToPath:(NSString *)savePath
                                  options:(CPDFSignatureCreateOptions *)options;

/// Sign with a key the SDK cannot hold, letting the SDK build the PKCS#7 container.
///
/// Prepares the placeholder, asks `signer` to sign, collects its certificate and
/// chain, assembles a detached container, and fills it — all in one call.
/// `options.signer` is ignored.
///
/// @param signer Your key. Called synchronously on the calling thread.
- (CPDFSignatureCreateResult *)signExternalDetachedPKCS7ToPath:(NSString *)savePath
                                                       options:(CPDFSignatureCreateOptions *)options
                                                        signer:(id<CPDFSignExternal>)signer;

/// Sign using a provider that returns a complete CMS container.
///
/// @param container Your container source. Called synchronously.
- (CPDFSignatureCreateResult *)signWithContainerToPath:(NSString *)savePath
                                               options:(CPDFSignatureCreateOptions *)options
                                             container:(id<CPDFSignContainer>)container;

#pragma mark Two-phase signing

/// Write a PDF with a real ByteRange and an empty `/Contents` placeholder.
///
/// The returned digest is what the external key signs. `options.signer` is ignored.
///
/// @param preparedPath Where to write the placeholder PDF. Treat it as immutable
/// until `-fillSignatureAtPath:options:` consumes it.
- (CPDFPrepareSignatureResult *)prepareSignatureToPath:(NSString *)preparedPath
                                               options:(CPDFSignatureCreateOptions *)options;

/// Write a finished container into a prepared placeholder.
///
/// Needs no document — the prepared file supplies everything — so a workflow created
/// with `-init` can perform this half.
///
/// @param savePath Where to write the signed PDF.
/// @param options The prepared state and the DER container.
- (CPDFFillSignatureResult *)fillSignatureAtPath:(NSString *)savePath
                                         options:(CPDFFillSignatureOptions *)options;

#pragma mark Validation

/// Validate every signature in a PDF on disk.
///
/// Needs no document, so this works on a workflow created with `-init`.
///
/// @param path The signed PDF to examine.
/// @param options Which checks to run and what to trust. Nil uses the defaults —
/// which means no revocation checking and no trust anchors, so chain results come
/// back `Indeterminate` rather than `Valid`.
- (CPDFSignatureWorkflowValidationResult *)validatePath:(NSString *)path
                                                options:(nullable CPDFSignatureWorkflowValidationOptions *)options;

/// Validate the signatures of the open document.
///
/// The parsed signature objects come from the document; the bytes that integrity,
/// coverage, and timestamp checks need come from the file at `document.documentURL`.
///
/// @note Because the bytes are read from disk, this reports on what was last saved.
/// A document with unsaved edits validates as its saved form.
- (CPDFSignatureWorkflowValidationResult *)validateDocumentWithOptions:(nullable CPDFSignatureWorkflowValidationOptions *)options;

@end

NS_ASSUME_NONNULL_END
