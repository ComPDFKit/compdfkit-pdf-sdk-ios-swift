//
//  CPDFPadesSigner.h
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
#import <ComPDFKit/CPDFSignatureValidation.h>
#import <ComPDFKit/CPDFSignatureWorkflow.h>
#import <ComPDFKit/CPDFTSAClient.h>

NS_ASSUME_NONNULL_BEGIN

@class CPDFDocument;
@class CPDFLtvAddOptions;
@class CPDFLtvAddResult;

#pragma mark - Baseline profile

/// The PAdES baseline level to produce. Each level contains the one before it.
typedef NS_ENUM(NSInteger, CPDFPadesBaselineProfile) {
    /// Detached PKCS#7 carrying a `signingCertificateV2` attribute. No timestamp.
    CPDFPadesBaselineProfileB = 0,
    /// Baseline-B plus an embedded RFC 3161 signature timestamp. Needs a TSA.
    CPDFPadesBaselineProfileT,
    /// Baseline-T plus the certificate chain and OCSP / CRL evidence, written to
    /// DSS / VRI. This is the level at which the signature becomes long-term
    /// verifiable — LTV.
    CPDFPadesBaselineProfileLT,
    /// Baseline-LT plus a document timestamp covering the LTV material, so the
    /// evidence itself can be shown to predate the expiry of what signed it.
    CPDFPadesBaselineProfileLTA,
};

#pragma mark - Create options

/// Everything one PAdES signing call needs.
@interface CPDFPadesCreateOptions : NSObject

/// The level to produce. Defaults to `B`.
@property (nonatomic,assign) CPDFPadesBaselineProfile profile;

/// The inner signature: field, appearance, signer, digest policy.
///
/// Its own `profile` is set for you from the baseline level, so leave it alone —
/// whatever you put there is overwritten. `B` maps to PAdES Baseline-B; `T`, `LT`, and
/// `LTA` all map to Baseline-T, since each of those levels builds on a timestamped
/// signature.
///
/// @warning That overwrite includes `CPDFSignatureProfileDocumentTimestamp`. A bare
/// document timestamp is not a PAdES baseline level and cannot be produced here — use
/// `-[CPDFSignatureWorkflow signToPath:options:]` for that.
///
/// @note For Baseline-T and above the signature timestamp comes from this object's
/// `tsaClient` (or its `signer.tsaClient`, or the timestamp URL the identity was built
/// with). The wrapper cannot see the last of those, so it does not pre-check that a
/// timestamp source exists — a missing one surfaces as a core-library error rather than
/// an `input.pades.*` one. `ltaTSAClient` below is a different thing: it stamps the
/// document, not the signature.
@property (nonatomic,strong) CPDFSignatureCreateOptions *signatureOptions;

/// LTV material you already hold.
///
/// When this carries any entries, automatic collection is skipped entirely — nothing
/// is fetched. That makes this the offline path: gather the evidence once on a machine
/// with network access, then sign anywhere.
@property (nonatomic,strong,nullable) CPDFLtvAddOptions *ltvOptions;

/// Whether the SDK builds the chain and fetches revocation evidence itself.
/// Defaults to `YES`, matching the core library.
///
/// @warning The fetch is synchronous HTTP performed by the core library's own client,
/// which does not use `NSURLSession` and so ignores App Transport Security, proxies,
/// and any timeout you would otherwise set. On iOS prefer `ltvOptions`.
@property (nonatomic,assign) BOOL autoCollectLTVValidationInfo;

/// OCSP responder URLs to use when the signer certificate carries no AIA extension.
/// Leave empty for certificates that do.
@property (nonatomic,copy,nullable) NSArray<NSString *> *ocspURLs;

/// CRL distribution point URLs, for certificates that carry no CRL DP extension.
@property (nonatomic,copy,nullable) NSArray<NSString *> *crlURLs;

/// The TSA for the Baseline-LTA document timestamp. Required for `LTA`.
///
/// @note Distinct from `signatureOptions.tsaClient`, which timestamps the signature
/// for Baseline-T. An LTA signature needs both; they may be the same authority.
@property (nonatomic,strong,nullable) id<CPDFTSAClient> ltaTSAClient;

/// A PEM bundle, or an OpenSSL hashed directory, of trusted root CAs.
///
/// Used for chain verification and for trusting the TSA. Nothing is bundled with the
/// SDK — supply your own. Without it, `LT` and `LTA` still write whatever evidence
/// they can gather, but the chain comes back `Indeterminate` rather than `Valid`.
@property (nonatomic,copy,nullable) NSString *trustedCertPath;

/// Bytes reserved for the LTA document timestamp `/Contents`. Defaults to 65536.
@property (nonatomic,assign) NSInteger ltaEstimatedContentsSize;

/// Field name for the LTA document timestamp signature.
/// Defaults to `PAdES-LTA-DocumentTimestamp`.
@property (nonatomic,copy) NSString *ltaFieldName;

@end

#pragma mark - Create result

/// The outcome of a PAdES signing call, stage by stage.
///
/// ## Reading the level that was reached
///
/// There is no single "attained profile" field, by design — the per-stage results say
/// more than one enum could. Read them in order:
///
/// - `signatureResult.success` — Baseline-B was produced. Read
///   `signatureResult.subFilter` to see what was actually written: `ETSI.CAdES.detached`
///   for a PAdES signature. Do not infer from `success` alone that a `T`-or-above
///   request got its signature timestamp; the `subFilter` and the timestamp entries of
///   `validationResult` are the evidence.
/// - `ltvResult.success` together with a non-empty `ltvPath` — Baseline-LT.
/// - `ltaTimestampResult.success` together with a non-empty `ltaPath` — Baseline-LTA.
///
/// When a stage fails, its own `errors` say why, and `warnings` collects what was
/// degraded rather than fatal — an unreachable OCSP responder, for instance. For the
/// complementary "what material is still missing" view, run
/// `-[CPDFLtvService assessReadinessOfDocument:]` over the output.
@interface CPDFPadesCreateResult : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/// Whether the requested level was reached in full. A `NO` here with a successful
/// `signatureResult` means the document was signed but did not reach `LT` or `LTA`.
@property (nonatomic,readonly) BOOL success;

/// The signed PDF. Written for every profile.
@property (nonatomic,readonly,copy) NSString *signedPath;

/// The PDF carrying DSS / VRI. Written for `LT` and `LTA`; empty otherwise.
@property (nonatomic,readonly,copy) NSString *ltvPath;

/// The PDF carrying the document timestamp. Written for `LTA`; empty otherwise.
@property (nonatomic,readonly,copy) NSString *ltaPath;

/// The inner signing stage.
@property (nonatomic,readonly,strong) CPDFSignatureCreateResult *signatureResult;

/// The DSS / VRI writing stage. Meaningful for `LT` and `LTA`.
@property (nonatomic,readonly,strong) CPDFLtvAddResult *ltvResult;

/// The document-timestamp stage. Meaningful for `LTA`.
@property (nonatomic,readonly,strong) CPDFSignatureCreateResult *ltaTimestampResult;

/// Verification of the final output.
@property (nonatomic,readonly,strong) CPDFSignatureWorkflowValidationResult *validationResult;

@property (nonatomic,readonly,copy) NSArray<CPDFValidationReportItem *> *errors;
@property (nonatomic,readonly,copy) NSArray<CPDFValidationReportItem *> *warnings;

@end

#pragma mark - Prolong options

/// Options for refreshing the LTV material of a PDF that is already signed.
@interface CPDFPadesProlongOptions : NSObject

/// Pre-collected material. As with signing, any entries here skip auto-collection.
@property (nonatomic,strong,nullable) CPDFLtvAddOptions *ltvOptions;

/// Defaults to `YES`. Carries the same synchronous-HTTP caveat as on
/// `CPDFPadesCreateOptions`.
@property (nonatomic,assign) BOOL autoCollectLTVValidationInfo;

/// Whether to append a document timestamp once the DSS / VRI has been written.
/// Defaults to `YES`.
///
/// Turn it off to write evidence only — useful when you are topping up material and
/// intend to stamp later, or in a batch where one stamp covers the final state.
/// When `YES`, `ltaPath` and `ltaTSAClient` are both required.
@property (nonatomic,assign) BOOL appendDocumentTimestamp;

@property (nonatomic,copy,nullable) NSArray<NSString *> *ocspURLs;
@property (nonatomic,copy,nullable) NSArray<NSString *> *crlURLs;

/// The TSA for the appended document timestamp. Required when
/// `appendDocumentTimestamp` is `YES`.
@property (nonatomic,strong,nullable) id<CPDFTSAClient> ltaTSAClient;

@property (nonatomic,copy,nullable) NSString *trustedCertPath;

/// Defaults to 65536.
@property (nonatomic,assign) NSInteger ltaEstimatedContentsSize;

/// Defaults to `PAdES-LTA-Prolong-DocumentTimestamp`.
@property (nonatomic,copy) NSString *ltaFieldName;

@end

#pragma mark - Prolong result

@interface CPDFPadesProlongResult : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@property (nonatomic,readonly) BOOL success;

@property (nonatomic,readonly,copy) NSString *inputPath;
@property (nonatomic,readonly,copy) NSString *ltvPath;

/// Empty when `appendDocumentTimestamp` was `NO`.
@property (nonatomic,readonly,copy) NSString *ltaPath;

@property (nonatomic,readonly,strong) CPDFLtvAddResult *ltvResult;
@property (nonatomic,readonly,strong) CPDFSignatureCreateResult *ltaTimestampResult;
@property (nonatomic,readonly,strong) CPDFSignatureWorkflowValidationResult *validationResult;

@property (nonatomic,readonly,copy) NSArray<CPDFValidationReportItem *> *errors;
@property (nonatomic,readonly,copy) NSArray<CPDFValidationReportItem *> *warnings;

@end

#pragma mark - Signer

/// One-call PAdES signing at Baseline-B, T, LT, or LTA.
///
/// `CPDFSignatureWorkflow` stops at Baseline-T: producing `LT` or `LTA` takes more
/// than one signing pass, because the validation evidence has to be gathered after the
/// signature exists and then written back — and, for `LTA`, timestamped again. This
/// class orchestrates those passes and hands back the result of each one.
///
/// ## Output files
///
/// Each level writes its own file, and none of them may share a path:
///
/// | Profile | signedPath | ltvPath  | ltaPath  |
/// |---------|------------|----------|----------|
/// | B, T    | required   | ignored  | ignored  |
/// | LT      | required   | required | ignored  |
/// | LTA     | required   | required | required |
///
/// The final document is the last one written — `ltaPath` for `LTA`, `ltvPath` for
/// `LT`, `signedPath` otherwise. The earlier files are the intermediate states; keep
/// them if you want an audit trail, delete them if you do not.
///
/// ## Threading
///
/// Every method is synchronous and blocking, and at `LT` and above performs network
/// I/O inline — TSA requests, and OCSP / CRL fetches when auto-collection is on.
///
/// @warning Never call these from the main thread. Use one instance from one thread at
/// a time: the receiver owns core-library state, so two threads sharing an instance are
/// unsafe even on different documents. Supply a `CPDFTSAClient` rather than relying on
/// the core library's built-in HTTP client, which bypasses `NSURLSession` and App
/// Transport Security. For revocation evidence there is no such hook — the only way to
/// keep that off the core library's socket code is to collect it yourself and pass it in
/// through `ltvOptions`.
@interface CPDFPadesSigner : NSObject

/// A signer with no document. Only `-prolongLTVFromPath:ltvPath:ltaPath:options:`
/// works; signing reports an input error.
- (instancetype)init NS_DESIGNATED_INITIALIZER;

/// A signer bound to an open document.
///
/// @param document The document to sign. It must be backed by a file on disk: the
/// source bytes are read from `document.documentURL`, not from the in-memory object,
/// so unsaved edits are not included. Save first.
- (instancetype)initWithDocument:(CPDFDocument *)document NS_DESIGNATED_INITIALIZER;

@property (nonatomic,readonly,weak,nullable) CPDFDocument *document;

/// Sign the document, building up to the requested baseline level.
///
/// @param signedPath Where the signed PDF goes. Always required.
/// @param ltvPath Where the DSS / VRI revision goes. Required for `LT` and `LTA`.
/// @param ltaPath Where the document-timestamped revision goes. Required for `LTA`.
/// @param options The level, the inner signature, and the evidence sources.
/// @return The per-stage outcome. Read `signedPath` / `ltvPath` / `ltaPath` on the
/// result rather than on your own inputs — they report what was actually written.
- (CPDFPadesCreateResult *)signToPath:(NSString *)signedPath
                              ltvPath:(nullable NSString *)ltvPath
                              ltaPath:(nullable NSString *)ltaPath
                              options:(CPDFPadesCreateOptions *)options;

/// Add or refresh the LTV material of a PDF that is already signed.
///
/// This is how an archived signature stays verifiable: before the existing evidence
/// ages out, fetch current evidence and append it, optionally under a fresh document
/// timestamp. Needs no open document — the input file supplies everything — so a
/// signer created with `-init` can do it.
///
/// @param inputPath The signed PDF to extend.
/// @param ltvPath Where the revision carrying the new DSS / VRI goes. Required, and
/// must differ from `inputPath`.
/// @param ltaPath Where the document-timestamped revision goes. Required when
/// `options.appendDocumentTimestamp` is `YES`.
- (CPDFPadesProlongResult *)prolongLTVFromPath:(NSString *)inputPath
                                       ltvPath:(NSString *)ltvPath
                                       ltaPath:(nullable NSString *)ltaPath
                                       options:(CPDFPadesProlongOptions *)options;

@end

NS_ASSUME_NONNULL_END
