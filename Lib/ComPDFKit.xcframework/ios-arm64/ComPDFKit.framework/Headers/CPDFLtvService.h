//
//  CPDFLtvService.h
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

NS_ASSUME_NONNULL_BEGIN

@class CPDFDocument;

#pragma mark - Validation material

/// The certificates and revocation evidence for one signature, destined for the
/// document's DSS / VRI dictionaries.
///
/// Hand these to `CPDFPadesSigner` — either `CPDFPadesCreateOptions.ltvOptions` or
/// `CPDFPadesProlongOptions.ltvOptions` — to write material the core library did not
/// collect itself.
///
/// A signature is addressed either by its VRI key or by its raw `/Contents`; set one of
/// the two. Supplying `signatureContentsDER` is the safer choice — the key is derived
/// from it, so the two cannot disagree.
///
/// An entry that sets neither is rejected, as is one whose DER arrays contain an empty
/// element: `certificatesDER` is an ordered chain, where a dropped element is a broken
/// chain rather than a smaller set, and nothing downstream would notice.
@interface CPDFLtvValidationInfo : NSObject

/// SHA-1 of the signature `/Contents`, as `+[CPDFLtvService vriKeyForSignatureContents:]`
/// computes it. Optional when `signatureContentsDER` is set.
@property (nonatomic,copy,nullable) NSString *vriKey;

/// The signature `/Contents` **in full, including the reserved-byte padding** — not the
/// parsed CMS container.
///
/// The core library derives the VRI key by hashing exactly these bytes, and its
/// validator recomputes the key the same way. Passing the trimmed DER writes the
/// entry under a key the validator never looks up, which silently downgrades
/// PAdES-LT to indeterminate.
///
/// `-[CPDFSignatureCoverageChecker rawSignatureContentsForSignature:atPath:]` returns the
/// bytes in the form this property wants. Optional when `vriKey` is set.
@property (nonatomic,copy,nullable) NSData *signatureContentsDER;

/// The signer certificate and its intermediates, DER-encoded.
@property (nonatomic,copy) NSArray<NSData *> *certificatesDER;

/// OCSP response bytes.
@property (nonatomic,copy) NSArray<NSData *> *ocspResponsesDER;

/// CRL bytes, DER-encoded.
@property (nonatomic,copy) NSArray<NSData *> *crlsDER;

@end

@interface CPDFLtvAddOptions : NSObject

/// One entry per signature to write material for. Empty writes nothing and succeeds.
@property (nonatomic,copy) NSArray<CPDFLtvValidationInfo *> *validationInfo;

@end

#pragma mark - Add result

@interface CPDFLtvAddResult : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@property (nonatomic,readonly) BOOL success;

/// Counts of what was actually written.
///
/// `vriEntriesAdded` is deduplicated: a successful call that adds no VRI entry means one
/// already existed for that key. The document-level arrays are **not** — `certificatesAdded`
/// and `crlsAdded` count appended objects, and material already present in the DSS is
/// embedded again. Repeatedly topping up the same document therefore grows it.
@property (nonatomic,readonly) NSInteger certificatesAdded;
@property (nonatomic,readonly) NSInteger ocspResponsesAdded;
@property (nonatomic,readonly) NSInteger crlsAdded;
@property (nonatomic,readonly) NSInteger vriEntriesAdded;

@property (nonatomic,readonly,copy) NSArray<CPDFValidationReportItem *> *errors;
@property (nonatomic,readonly,copy) NSArray<CPDFValidationReportItem *> *warnings;

@end

#pragma mark - DSS inspection

/// What the document's DSS dictionary currently holds.
///
/// The unprefixed counts are the document-level DSS arrays; the `vri`-prefixed ones
/// aggregate across every VRI entry.
@interface CPDFLtvDssInfo : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@property (nonatomic,readonly) BOOL hasDSS;

@property (nonatomic,readonly) NSInteger certificatesCount;
@property (nonatomic,readonly) NSInteger ocspResponsesCount;
@property (nonatomic,readonly) NSInteger crlsCount;

@property (nonatomic,readonly) NSInteger vriEntriesCount;
@property (nonatomic,readonly) NSInteger vriCertificatesCount;
@property (nonatomic,readonly) NSInteger vriOcspResponsesCount;
@property (nonatomic,readonly) NSInteger vriCrlsCount;

/// Every VRI key present, suitable for `-inspectVRIInDocument:vriKey:`.
@property (nonatomic,readonly,copy) NSArray<NSString *> *vriKeys;

@end

@interface CPDFLtvInspectResult : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/// Whether the DSS could be read. A document with no DSS at all still reads
/// successfully — `dssInfo.hasDSS` is then `NO`. Read this flag before concluding
/// anything from the counts, so "no DSS" stays distinguishable from "read failed".
@property (nonatomic,readonly) BOOL success;

@property (nonatomic,readonly,strong) CPDFLtvDssInfo *dssInfo;

@property (nonatomic,readonly,copy) NSArray<CPDFValidationReportItem *> *errors;
@property (nonatomic,readonly,copy) NSArray<CPDFValidationReportItem *> *warnings;

@end

#pragma mark - VRI inspection

@interface CPDFLtvVriInfo : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@property (nonatomic,readonly) BOOL hasDSS;

/// Whether the DSS carries a `/VRI` dictionary at all.
@property (nonatomic,readonly) BOOL hasVRI;

/// Whether that dictionary contains the key that was asked for.
@property (nonatomic,readonly) BOOL hasVRIEntry;

@property (nonatomic,readonly,copy) NSString *vriKey;

@property (nonatomic,readonly) NSInteger certificatesCount;
@property (nonatomic,readonly) NSInteger ocspResponsesCount;
@property (nonatomic,readonly) NSInteger crlsCount;

@end

@interface CPDFLtvVriInspectResult : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@property (nonatomic,readonly) BOOL success;
@property (nonatomic,readonly,strong) CPDFLtvVriInfo *vriInfo;
@property (nonatomic,readonly,copy) NSArray<CPDFValidationReportItem *> *errors;
@property (nonatomic,readonly,copy) NSArray<CPDFValidationReportItem *> *warnings;

@end

#pragma mark - VRI material

/// The bytes recovered from one VRI entry.
@interface CPDFLtvVriValidationMaterial : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@property (nonatomic,readonly,copy) NSString *vriKey;
@property (nonatomic,readonly,copy) NSArray<NSData *> *certificatesDER;
@property (nonatomic,readonly,copy) NSArray<NSData *> *ocspResponsesDER;
@property (nonatomic,readonly,copy) NSArray<NSData *> *crlsDER;

@end

@interface CPDFLtvVriMaterialResult : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@property (nonatomic,readonly) BOOL success;
@property (nonatomic,readonly,strong) CPDFLtvVriValidationMaterial *material;
@property (nonatomic,readonly,copy) NSArray<CPDFValidationReportItem *> *errors;
@property (nonatomic,readonly,copy) NSArray<CPDFValidationReportItem *> *warnings;

@end

#pragma mark - Readiness

/// Whether the document carries enough material to still verify once the signing
/// certificates have expired.
@interface CPDFLtvReadinessInfo : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@property (nonatomic,readonly) BOOL hasDSS;
@property (nonatomic,readonly) BOOL hasVRI;
@property (nonatomic,readonly) BOOL hasCertificates;

/// Whether revocation evidence is both present and validated. Present-but-unvalidated
/// evidence reports `NO`.
@property (nonatomic,readonly) BOOL hasRevocation;

/// Whether every signature in the document has complete LTV material.
@property (nonatomic,readonly) BOOL ltvReady;

/// A short human-readable classification, e.g. `PAdES-LT-candidate`. May be empty.
@property (nonatomic,readonly,copy) NSString *profileHint;

/// What is absent, in human-readable form. Surface this rather than a bare failure —
/// it is the only place that says *which* material is missing.
@property (nonatomic,readonly,copy) NSArray<NSString *> *missingMaterials;

@property (nonatomic,readonly,strong) CPDFLtvDssInfo *dssInfo;

@end

@interface CPDFLtvReadinessResult : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@property (nonatomic,readonly) BOOL success;
@property (nonatomic,readonly,strong) CPDFLtvReadinessInfo *readinessInfo;
@property (nonatomic,readonly,copy) NSArray<CPDFValidationReportItem *> *errors;
@property (nonatomic,readonly,copy) NSArray<CPDFValidationReportItem *> *warnings;

@end

#pragma mark - Service

/// Inspects the long-term validation material in a PDF's DSS / VRI dictionaries.
///
/// LTV is what lets a signature still verify after its certificate has expired: the
/// certificate chain and the revocation evidence that was valid at signing time are
/// stored in the document itself. This class provides read-only access to that
/// material.
///
/// ## Where this fits
///
/// - Writing material into a PDF → `CPDFPadesSigner`, not this class. Signing at
///   Baseline-LT or above collects and writes it for you; `-[CPDFPadesSigner
///   prolongLTVFromPath:ltvPath:ltaPath:options:]` tops up a PDF someone else signed.
///   Both append incrementally inside the core library and hand back a path, which is
///   what keeps the existing signature byte ranges intact.
/// - Auditing what a PDF already carries → `-inspectDSSInDocument:` and
///   `-assessReadinessOfDocument:`.
/// - Verifying with no network → `-extractVRIMaterialFromDocument:vriKey:`, then feed
///   the bytes to `CPDFRevocationService`. Nothing is fetched, so this is the path for
///   an offline or air-gapped verifier.
///
/// ## Threading
///
/// Every method is synchronous and reads document structure. None of them perform
/// network I/O.
///
/// @warning Use one instance from one thread at a time. The receiver owns core-library
/// state, so serializing per document is not enough — two threads sharing an instance
/// are unsafe even when they work on different documents. Instances are cheap; make one
/// per thread.
@interface CPDFLtvService : NSObject

/// The VRI dictionary key for a signature: the SHA-1 of its `/Contents`.
///
/// @warning This hashes whatever bytes it is handed, and the key the core library's
/// validator looks up is the hash of the `/Contents` **including its reserved-byte
/// padding**. Hashing the trimmed CMS container yields a different, unusable key. Use
/// `-[CPDFSignatureCoverageChecker rawSignatureContentsForSignature:atPath:]` to obtain
/// the bytes in the expected form.
///
/// @note Producers disagree on this: some write the key over the padded `/Contents`
/// (as this SDK does), others over the trimmed DER. A key computed here will not match
/// a DSS written by a producer that chose the other convention.
///
/// @param signatureContentsDER The signature `/Contents`, padding included.
/// @return The key, or nil when `signatureContentsDER` is empty or the core library
/// could not compute one.
+ (nullable NSString *)vriKeyForSignatureContents:(NSData *)signatureContentsDER;

/// Summarize the document's DSS dictionary.
- (CPDFLtvInspectResult *)inspectDSSInDocument:(CPDFDocument *)document;

/// Summarize one VRI entry.
///
/// @param vriKey A key from `CPDFLtvDssInfo.vriKeys`, or one computed by
/// `+vriKeyForSignatureContents:`.
- (CPDFLtvVriInspectResult *)inspectVRIInDocument:(CPDFDocument *)document
                                           vriKey:(NSString *)vriKey;

/// Recover the raw certificate, OCSP, and CRL bytes stored in a VRI entry.
///
/// This is the offline re-validation entry point: put the returned bytes into a
/// `CPDFRevocationCheckInput` and call `-[CPDFRevocationService validateOCSPResponse:]`
/// or `-validateCRL:`. Both validate what you hand them without a network round trip.
- (CPDFLtvVriMaterialResult *)extractVRIMaterialFromDocument:(CPDFDocument *)document
                                                      vriKey:(NSString *)vriKey;

/// Judge whether every signature in the document has complete LTV material.
///
/// @note When `readinessInfo.ltvReady` is `NO`, `readinessInfo.missingMaterials` names
/// what is absent. Report that rather than a bare failure — it is what tells a caller
/// whether to fetch fresh revocation evidence or to re-sign.
- (CPDFLtvReadinessResult *)assessReadinessOfDocument:(CPDFDocument *)document;

@end

NS_ASSUME_NONNULL_END
