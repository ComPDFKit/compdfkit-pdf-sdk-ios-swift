//
//  CPDFSignatureValidation.h
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

NS_ASSUME_NONNULL_BEGIN

@class CPDFDocument;
@class CPDFSignature;

#pragma mark - Status

/// The outcome of one validation check, or of a whole signature.
///
/// @note `CPDFValidationStatusNotChecked` is not a failure. A check that could not run —
/// most often revocation or chain building with no network and no local material —
/// reports `NotChecked` rather than `Invalid`, so an offline verdict is never
/// misread as a rejection.
typedef NS_ENUM(NSInteger, CPDFValidationStatus) {
    CPDFValidationStatusValid = 0,
    CPDFValidationStatusInvalid,
    /// The check ran but could not reach a verdict, e.g. a chain with an unknown anchor.
    CPDFValidationStatusIndeterminate,
    /// The check did not run: disabled by options, or its input was unavailable.
    CPDFValidationStatusNotChecked,
};

/// Which aspect of a signature a report item is about.
typedef NS_ENUM(NSInteger, CPDFValidationCategory) {
    CPDFValidationCategorySignatureIntegrity = 0,
    CPDFValidationCategoryByteRangeCoverage,
    CPDFValidationCategoryDocumentRevision,
    CPDFValidationCategoryDocumentPermissions,
    CPDFValidationCategoryCertificateChain,
    CPDFValidationCategoryRevocation,
    CPDFValidationCategoryTimestamp,
    CPDFValidationCategoryAlgorithmPolicy,
    CPDFValidationCategoryPadesProfile,
    CPDFValidationCategorySignatureAppearance,
    CPDFValidationCategoryInput,
};

typedef NS_ENUM(NSInteger, CPDFValidationSeverity) {
    CPDFValidationSeverityInfo = 0,
    CPDFValidationSeverityWarning,
    CPDFValidationSeverityError,
};

#pragma mark - Report item

/// One line of a validation report.
@interface CPDFValidationReportItem : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@property (nonatomic,readonly) CPDFValidationStatus status;
@property (nonatomic,readonly) CPDFValidationCategory category;
@property (nonatomic,readonly) CPDFValidationSeverity severity;

/// A stable, category-scoped identifier such as `timestamp.embedded.imprint.mismatch`.
/// Match on this rather than on `message`, which is not part of the contract.
@property (nonatomic,readonly,copy) NSString *code;

/// A human readable description. Not localized.
@property (nonatomic,readonly,copy) NSString *message;

/// The SHA-1 fingerprint of the certificate this item is about, or an empty string.
@property (nonatomic,readonly,copy) NSString *relatedCertificateFingerprint;

@end

#pragma mark - Report

/// The structured verification report for a single signature.
@interface CPDFSignatureValidationReport : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/// The aggregate verdict over `items`.
@property (nonatomic,readonly) CPDFValidationStatus overallStatus;

@property (nonatomic,readonly,copy) NSString *fieldName;

/// The `/SubFilter` value, e.g. `adbe.pkcs7.detached` or `ETSI.CAdES.detached`.
@property (nonatomic,readonly,copy) NSString *subFilter;

@property (nonatomic,readonly,copy) NSString *digestAlgorithm;
@property (nonatomic,readonly,copy) NSString *signatureAlgorithm;

/// Index of the incremental-update revision this signature signs, or -1 when unknown.
///
/// @note The shipping core library never fills this in — it is -1 for every signature,
/// including documents with several revisions. Do not branch on it.
@property (nonatomic,readonly) NSInteger revisionIndex;

/// Whether the coverage check accepted the revision this signature covers.
///
/// @warning This is **not** "the ByteRange reaches the end of the file". A signature
/// followed by a later incremental update — which is exactly what adding LTV material or
/// a document timestamp produces — still reports `YES`; the accompanying
/// `byterange.prior_revision` item is the only thing in the report that says later bytes
/// exist. It reports `NO` when the trailing bytes do not form a plausible incremental
/// revision at all.
///
/// To decide whether anything was appended after signing, compare the end of the last
/// segment of `CPDFSignatureCoverageResult.signedRanges` against its `fileSize`. To decide
/// whether an append changed the document's content, read the
/// `CPDFValidationCategoryDocumentPermissions` items — a DocMDP violation reports
/// `permissions.failed`.
@property (nonatomic,readonly) BOOL coversWholeDocument;

/// Every check that ran, in the order the core library produced them.
@property (nonatomic,readonly,copy) NSArray<CPDFValidationReportItem *> *items;

/// The subset of `items` at the given severity. Convenience over filtering by hand.
- (NSArray<CPDFValidationReportItem *> *)itemsWithSeverity:(CPDFValidationSeverity)severity;

@end

#pragma mark - Algorithm policy

/// What validation does when it meets a weak algorithm.
typedef NS_ENUM(NSInteger, CPDFWeakAlgorithmAction) {
    CPDFWeakAlgorithmActionAllow = 0,
    CPDFWeakAlgorithmActionWarn,
    CPDFWeakAlgorithmActionReject,
};

/// The allow / warn / reject rules applied to digests, key sizes, and algorithm OIDs.
///
/// @warning A policy set on `CPDFSignatureCreateOptions.algorithmPolicy` is **not**
/// propagated into `postSignValidationOptions` by the core library.
/// `CPDFSignatureWorkflow` copies it across for you, overwriting whatever
/// `postSignValidationOptions` carried.
/// A policy assigned to a `CPDFSignatureValidationOptions` you build yourself governs
/// a standalone `-validatePath:options:` call and nothing else.
@interface CPDFSignatureAlgorithmPolicy : NSObject <NSCopying>

/// The digest requested from external signers and used when the SDK assembles a
/// detached PKCS#7 container. Defaults to `SHA256`.
@property (nonatomic,assign) CPDFSignatureDigestAlgorithm digestAlgorithm;

/// Action for a signature that uses SHA-1. Defaults to `Warn`.
@property (nonatomic,assign) CPDFWeakAlgorithmAction sha1Action;

/// Action for a signature that uses MD5. Defaults to `Reject`.
@property (nonatomic,assign) CPDFWeakAlgorithmAction md5Action;

/// Smallest accepted RSA signer key. Defaults to 2048.
@property (nonatomic,assign) NSInteger minimumRSAKeyBits;

/// Whether a self-signed leaf certificate satisfies policy. Defaults to `NO`.
/// Chain validation may still demand a trust anchor; this is policy intent only.
@property (nonatomic,assign) BOOL allowsSelfSignedLeaf;

/// Whether an expired signing certificate is acceptable when no trusted timestamp
/// is available. Defaults to `NO`.
@property (nonatomic,assign) BOOL allowsExpiredWithoutTrustedTimestamp;

/// Dotted OIDs of the only signature algorithms accepted. When non-empty, anything
/// outside the list is rejected. `nil` or empty imposes no allow-list.
@property (nonatomic,copy,nullable) NSArray<NSString *> *allowedSignatureAlgorithmOIDs;

/// Dotted OIDs that are always rejected.
@property (nonatomic,copy,nullable) NSArray<NSString *> *rejectedSignatureAlgorithmOIDs;

@end

#pragma mark - Coverage options

/// Tolerances applied when checking that a ByteRange really covers the file.
@interface CPDFSignatureCoverageOptions : NSObject <NSCopying>

/// Whether trailing end-of-line bytes after the last signed byte are tolerated.
/// Defaults to `YES` — some producers append a newline after `%%EOF`.
@property (nonatomic,assign) BOOL allowsTrailingEOL;

/// How many trailing bytes `allowsTrailingEOL` forgives. Defaults to 4.
@property (nonatomic,assign) NSUInteger maximumTrailingEOLBytes;

/// Whether the ByteRange gap must line up exactly with the `/Contents` string.
/// Defaults to `YES`. Turning this off accepts documents whose gap is padded.
@property (nonatomic,assign) BOOL requiresContentsGapMatch;

/// Whether a document with more than one plausible `/Contents` is rejected outright.
/// Defaults to `YES`.
@property (nonatomic,assign) BOOL rejectsAmbiguousContents;

@end

#pragma mark - Coverage result

/// Where one signature's bytes actually are, and what the coverage check made of them.
@interface CPDFSignatureCoverageResult : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/// The coverage verdict. `Valid` also covers "the ByteRange ends before EOF but the
/// remaining bytes form a later incremental revision" — see `items` for which case it was.
@property (nonatomic,readonly) CPDFValidationStatus status;

/// The signed segments, as alternating offset and length values — the same flat layout as
/// `CPDFPreparedExternalSignatureInfo.byteRange`. A standard signature yields four numbers.
///
/// The end of the last segment compared against `fileSize` is what tells you whether
/// anything was appended after signing;
/// `CPDFSignatureValidationReport.coversWholeDocument` does not.
@property (nonatomic,readonly,copy) NSArray<NSNumber *> *signedRanges;

/// Where the `/Contents` hex string sits in the file, **brackets included** — so the
/// length is `2 * contentsBytes + 2`.
@property (nonatomic,readonly) unsigned long contentsGapOffset;
@property (nonatomic,readonly) unsigned long contentsGapLength;

/// The size of the file that was checked.
@property (nonatomic,readonly) unsigned long fileSize;

/// Diagnostics using `input.*`, `signature.*`, `byterange.*`, `contents.*`, and
/// `coverage.*` codes.
@property (nonatomic,readonly,copy) NSArray<CPDFValidationReportItem *> *items;

@end

#pragma mark - Coverage checker

/// Locates a signature's signed byte ranges and `/Contents`, and judges whether the
/// ByteRange covers what it claims.
///
/// `CPDFSignatureWorkflow` runs this check as part of validation and folds the outcome
/// into the report. Use this class directly when you need the numbers rather than the
/// verdict: the byte ranges, the `/Contents` location, or the `/Contents` bytes that LTV
/// material has to be keyed against.
///
/// ## Threading
///
/// Synchronous, reads the file at the given path, performs no network I/O. Use one
/// instance from one thread at a time.
@interface CPDFSignatureCoverageChecker : NSObject

/// Check `signature` against the PDF at `path`.
///
/// @param path The file the signature lives in. The check reads bytes from disk, so this
/// must be the saved form — not a document with unsaved edits.
/// @param options Tolerances, or nil for the defaults.
/// @return Never nil. Unusable input comes back as a result carrying an `input.*` item.
- (CPDFSignatureCoverageResult *)checkSignature:(CPDFSignature *)signature
                                         atPath:(NSString *)path
                                        options:(nullable CPDFSignatureCoverageOptions *)options;

/// Check `signature` against the file backing `document`, taken from
/// `document.documentURL`.
- (CPDFSignatureCoverageResult *)checkSignature:(CPDFSignature *)signature
                                     inDocument:(CPDFDocument *)document
                                        options:(nullable CPDFSignatureCoverageOptions *)options;

/// The signature's `/Contents` bytes, **in full, including the reserved-byte padding**.
///
/// This is the form `+[CPDFLtvService vriKeyForSignatureContents:]` and
/// `CPDFLtvValidationInfo.signatureContentsDER` require: the core library keys VRI
/// entries on the hash of the padded string, so the trimmed CMS container produces a key
/// its own validator will not find. There is no other way to obtain these bytes through
/// the public API.
///
/// @return The bytes, or nil when the coverage check failed, the gap is not a direct hex
/// string, or the hex could not be decoded.
- (nullable NSData *)rawSignatureContentsForSignature:(CPDFSignature *)signature
                                                atPath:(NSString *)path;

@end

#pragma mark - Validation options

/// Which checks to run, and the material to run them against.
@interface CPDFSignatureValidationOptions : NSObject <NSCopying>

/// Verify the PKCS#7 / CMS cryptographic integrity. Defaults to `YES`.
@property (nonatomic,assign) BOOL checksIntegrity;

/// Verify that the ByteRange covers what it claims. Defaults to `YES`.
@property (nonatomic,assign) BOOL checksCoverage;

/// Verify the DocMDP / permissions state of the signed revision. Defaults to `YES`.
@property (nonatomic,assign) BOOL checksDocumentPermissions;

/// Build and verify the certificate chain. Defaults to `YES`.
/// Needs `trustedCertificatePath` to reach `Valid` rather than `Indeterminate`.
@property (nonatomic,assign) BOOL checksCertificateChain;

/// Verify embedded and document timestamps. Defaults to `YES`.
@property (nonatomic,assign) BOOL checksTimestamp;

/// Verify revocation status through OCSP / CRL.
///
/// @warning Defaults to **`NO`**, matching the core library. Enabling it may make the
/// core library open network connections from inside the validation call — see
/// `CPDFSignatureWorkflow` for the threading and App Transport Security consequences.
@property (nonatomic,assign) BOOL checksRevocation;

@property (nonatomic,copy) CPDFSignatureCoverageOptions *coverageOptions;

@property (nonatomic,copy) CPDFSignatureAlgorithmPolicy *algorithmPolicy;

/// Trust anchors for chain validation, including TSA tokens. Either a PEM bundle file
/// or an OpenSSL-style hashed certificate directory.
///
/// @note The framework ships no bundle of its own. Supply one from your app, or leave
/// this `nil` and read chain results as `Indeterminate` rather than `Valid`.
@property (nonatomic,copy,nullable) NSString *trustedCertificatePath;

/// Unix epoch seconds to evaluate certificate validity and revocation at.
///
/// 0 — the default — lets the validator derive a PAdES validation time: a trusted
/// RFC 3161 timestamp first, then the PKCS#7 / PDF signing time, then now.
@property (nonatomic,assign) long long validationTimeEpochSeconds;

@end

NS_ASSUME_NONNULL_END
