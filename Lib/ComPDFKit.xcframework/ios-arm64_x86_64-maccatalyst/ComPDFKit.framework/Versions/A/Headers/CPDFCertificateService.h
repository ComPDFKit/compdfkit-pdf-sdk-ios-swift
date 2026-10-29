//
//  CPDFCertificateService.h
//  ComPDFKit
//
//  Copyright © 2014-2026 PDF Technologies, Inc. All Rights Reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE ComPDFKit LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <ComPDFKit/CPDFSignatureValidation.h>

NS_ASSUME_NONNULL_BEGIN

#pragma mark - Certificate store

/// A collection of trust anchors and intermediate certificates used to build and
/// anchor a certificate chain.
@interface CPDFCertificateStore : NSObject

/// Add a trust anchor from its DER encoding.
- (void)addTrustedCertificateDER:(NSData *)certificateDER;

/// Add an intermediate certificate from its DER encoding.
- (void)addIntermediateCertificateDER:(NSData *)certificateDER;

/// Add a trust anchor from a file. PEM and DER are both accepted and detected
/// automatically.
/// @return `NO` when the file cannot be read or does not hold an X.509 certificate.
- (BOOL)addTrustedCertificateFileAtPath:(NSString *)path;

/// Add an intermediate certificate from a PEM or DER file.
/// @return `NO` when the file cannot be read or does not hold an X.509 certificate.
- (BOOL)addIntermediateCertificateFileAtPath:(NSString *)path;

/// A directory or bundle file of additional trust anchors handed to OpenSSL,
/// or an empty string for none.
@property (nonatomic,copy) NSString *trustedCertificatePath;

/// The trust anchors added so far, in the order they were added.
@property (nonatomic,readonly,copy) NSArray<NSData *> *trustedCertificatesDER;

/// The intermediate certificates added so far, in the order they were added.
@property (nonatomic,readonly,copy) NSArray<NSData *> *intermediateCertificatesDER;

/// Whether the store holds nothing at all.
@property (nonatomic,readonly,getter=isEmpty) BOOL empty;

@end

#pragma mark - Chain building

/// Everything a chain build needs, for callers that want the validation time as
/// well as the certificates.
@interface CPDFCertificateChainBuildInput : NSObject

/// The certificate whose chain should be built.
@property (nonatomic,copy,nullable) NSData *subjectCertificateDER;

/// Intermediates available to complete the chain.
@property (nonatomic,copy) NSArray<NSData *> *intermediateCertificatesDER;

/// Trust anchors the chain must terminate in.
@property (nonatomic,copy) NSArray<NSData *> *trustedCertificatesDER;

/// An extra OpenSSL trust path, or an empty string for none.
@property (nonatomic,copy) NSString *trustedCertificatePath;

/// Whether a chain that stops short of a trust anchor still counts as built.
/// Defaults to `NO`. Note that `allowPartialChain` never makes a result
/// `trusted`; it only lets `success` be `YES` for an incomplete chain.
@property (nonatomic,assign) BOOL allowPartialChain;

/// Unix epoch seconds used for the certificate validity window. `0` — the
/// default — validates against the current clock.
@property (nonatomic,assign) long long validationTimeEpochSeconds;

@end

/// The outcome of a chain build.
@interface CPDFCertificateChainBuildResult : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/// Whether a chain could be assembled at all.
@property (nonatomic,readonly) BOOL success;

/// Whether the chain terminates in one of the supplied trust anchors.
///
/// @warning A built chain is not a trusted chain. `success` only says the
/// certificates link up; `trusted` is the one that says the chain anchors in
/// your trust store. Never treat `success` alone as a trust decision.
@property (nonatomic,readonly) BOOL trusted;

/// The chain, leaf first, in DER encoding. Empty when `success` is `NO`.
@property (nonatomic,readonly,copy) NSArray<NSData *> *chainDER;

/// Diagnostics describing what happened, using `certificate.*` codes.
@property (nonatomic,readonly,copy) NSArray<CPDFValidationReportItem *> *items;

@end

/// Builds an X.509 chain from a leaf certificate and a set of intermediates and
/// trust anchors.
///
/// Purely local: no network access, no revocation checking. Pair it with
/// `CPDFRevocationService` when you need revocation status too.
@interface CPDFCertificateChainBuilder : NSObject

/// Build a chain for `subjectCertificateDER` against `store`, validating
/// against the current clock.
///
/// @param allowPartialChain Whether a chain that does not reach a trust anchor
/// still counts as successfully built.
/// @return Never `nil`.
- (CPDFCertificateChainBuildResult *)buildChainForCertificateDER:(NSData *)subjectCertificateDER
                                                           store:(CPDFCertificateStore *)store
                                               allowPartialChain:(BOOL)allowPartialChain;

/// Build a chain from a full input, which additionally carries the validation time.
///
/// @return Never `nil`.
- (CPDFCertificateChainBuildResult *)buildChainWithInput:(CPDFCertificateChainBuildInput *)input;

@end

#pragma mark - Revocation

/// Where a revocation answer came from.
typedef NS_ENUM(NSInteger, CPDFRevocationSource) {
    CPDFRevocationSourceNone = 0,
    CPDFRevocationSourceOCSP,
    CPDFRevocationSourceCRL,
};

/// A revocation answer. Note that this is five-valued, not a boolean — a
/// certificate that could not be checked is neither good nor revoked.
typedef NS_ENUM(NSInteger, CPDFRevocationStatus) {
    /// The responder or CRL says the certificate is not revoked.
    CPDFRevocationStatusGood = 0,
    /// The certificate is revoked.
    CPDFRevocationStatusRevoked,
    /// The evidence was readable but does not cover this certificate.
    CPDFRevocationStatusUnknown,
    /// The evidence itself failed verification — bad signature, wrong issuer,
    /// or outside its time window.
    CPDFRevocationStatusInvalid,
    /// No check was performed.
    CPDFRevocationStatusNotChecked,
};

/// The inputs for one revocation check.
///
/// The `validate…` methods read only the certificates, the pre-fetched evidence,
/// and the time fields. The `fetch…` methods additionally use the URL lists and
/// the transport settings.
@interface CPDFRevocationCheckInput : NSObject

/// The certificate being checked.
@property (nonatomic,copy,nullable) NSData *subjectCertificateDER;

/// Its issuer. Required — OCSP identifies a certificate by issuer name and key
/// hash, and CRL verification needs the issuer's public key.
@property (nonatomic,copy,nullable) NSData *issuerCertificateDER;

/// Extra OCSP responder URLs, merged with the ones in the certificate's AIA
/// extension. Only used by the `fetch…` methods.
@property (nonatomic,copy) NSArray<NSString *> *ocspURLs;

/// Extra CRL distribution point URLs, merged with the ones in the certificate's
/// CRLDP extension. Only used by the `fetch…` methods.
@property (nonatomic,copy) NSArray<NSString *> *crlURLs;

/// A previously obtained OCSP response, for `-validateOCSPResponse:` and
/// `-validateBestAvailable:`.
@property (nonatomic,copy,nullable) NSData *ocspResponseDER;

/// A previously obtained CRL, for `-validateCRL:` and `-validateBestAvailable:`.
@property (nonatomic,copy,nullable) NSData *crlDER;

/// Tolerance applied to the evidence's time window. Defaults to 300 seconds.
@property (nonatomic,assign) NSInteger allowedClockSkewSeconds;

/// Unix epoch seconds used for the time-window check. `0` — the default —
/// validates against the current clock.
@property (nonatomic,assign) long long validationTimeEpochSeconds;

#pragma mark Transport settings — `fetch…` only

/// Request timeout in seconds. Defaults to 20.
@property (nonatomic,assign) NSInteger networkTimeoutSeconds;

/// How many times to retry after a transport failure. Defaults to 0.
@property (nonatomic,assign) NSInteger networkRetryCount;

/// Reject responses larger than this. Defaults to 10 MB.
@property (nonatomic,assign) NSUInteger maximumResponseSize;

/// An explicit proxy URL, or an empty string for none.
@property (nonatomic,copy) NSString *proxyURLString;

/// Whether to fall back to the `HTTPS_PROXY` / `HTTP_PROXY` environment
/// variables. Defaults to `YES`, matching the core library. Note that this is
/// *not* the system proxy configuration.
@property (nonatomic,assign) BOOL usesEnvironmentProxy;

/// Extra header fields sent with the OCSP or CRL request.
@property (nonatomic,copy) NSDictionary<NSString *, NSString *> *additionalHeaderFields;

@end

/// The revocation endpoints a certificate advertises.
@interface CPDFRevocationSources : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/// OCSP responder URLs from the AIA extension.
@property (nonatomic,readonly,copy) NSArray<NSString *> *ocspURLs;

/// CRL distribution point URLs from the CRLDP extension.
@property (nonatomic,readonly,copy) NSArray<NSString *> *crlURLs;

@end

/// The outcome of validating revocation evidence.
@interface CPDFRevocationCheckResult : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/// Whether the check ran to completion. A successful check can still report
/// `CPDFRevocationStatusRevoked` — read `status` for the answer.
@property (nonatomic,readonly) BOOL success;

/// Which kind of evidence produced `status`.
@property (nonatomic,readonly) CPDFRevocationSource source;

/// The revocation answer.
@property (nonatomic,readonly) CPDFRevocationStatus status;

/// A human readable elaboration, such as the revocation reason and time.
@property (nonatomic,readonly,copy) NSString *statusDetail;

/// Diagnostics using `revocation.*` codes.
@property (nonatomic,readonly,copy) NSArray<CPDFValidationReportItem *> *items;

@end

/// The outcome of downloading and then validating revocation evidence.
@interface CPDFRevocationFetchResult : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/// Whether the download succeeded. The revocation answer itself lives in
/// `validationResult`.
@property (nonatomic,readonly) BOOL success;

/// Which kind of evidence was fetched.
@property (nonatomic,readonly) CPDFRevocationSource source;

/// The endpoint that answered, or an empty string when nothing was reached.
@property (nonatomic,readonly,copy) NSString *URLString;

/// The bytes that came back — an OCSP response or a CRL.
///
/// These are exactly the bytes an LTV DSS dictionary wants, so a fetch result
/// can be written straight back into the document as long-term validation
/// material rather than being fetched again at verification time.
@property (nonatomic,readonly,copy) NSData *responseDER;

/// The result of validating `responseDER`.
@property (nonatomic,readonly) CPDFRevocationCheckResult *validationResult;

/// Diagnostics for the fetch itself, using `revocation.*` codes.
@property (nonatomic,readonly,copy) NSArray<CPDFValidationReportItem *> *items;

@end

/// OCSP and CRL revocation checking.
///
/// Two families of methods:
///
/// - `validate…` verify evidence you already have. No network access at all.
/// - `fetch…` perform the HTTP round-trip inside the core library and then
///   validate what came back.
///
/// @warning The `fetch…` methods block the calling thread and go through
/// OpenSSL's HTTP and TLS stack rather than `NSURLSession`, so App Transport
/// Security, the system proxy configuration, and any certificate pinning the
/// app installs do not apply. On iOS, prefer downloading the evidence yourself
/// and calling the `validate…` methods with it. Never call a `fetch…` method on
/// the main thread.
@interface CPDFRevocationService : NSObject

/// Read the OCSP (AIA) and CRL distribution point extensions out of a
/// certificate. No network access.
///
/// @return Never `nil`; both lists are empty when the certificate carries no
/// such extensions.
- (CPDFRevocationSources *)discoverSourcesInCertificateDER:(NSData *)certificateDER;

#pragma mark Validate pre-fetched evidence — no network

/// Validate `input.ocspResponseDER`: response signature, that it covers this
/// certificate, its status, and its time window.
- (CPDFRevocationCheckResult *)validateOCSPResponse:(CPDFRevocationCheckInput *)input;

/// Validate `input.crlDER`: CRL signature, issuer match, `lastUpdate` /
/// `nextUpdate` window, and whether the subject's serial is listed.
- (CPDFRevocationCheckResult *)validateCRL:(CPDFRevocationCheckInput *)input;

/// Validate whichever evidence was supplied — OCSP first, then CRL.
- (CPDFRevocationCheckResult *)validateBestAvailable:(CPDFRevocationCheckInput *)input;

#pragma mark Fetch and validate — synchronous network access

/// POST an OCSP request to the first reachable responder and validate the reply.
- (CPDFRevocationFetchResult *)fetchOCSPResponse:(CPDFRevocationCheckInput *)input;

/// Download a CRL from the first reachable distribution point and validate it.
- (CPDFRevocationFetchResult *)fetchCRL:(CPDFRevocationCheckInput *)input;

/// Try OCSP, then fall back to CRL when no responder is available or the OCSP
/// exchange fails.
- (CPDFRevocationFetchResult *)fetchAndValidateBestAvailable:(CPDFRevocationCheckInput *)input;

@end

NS_ASSUME_NONNULL_END
