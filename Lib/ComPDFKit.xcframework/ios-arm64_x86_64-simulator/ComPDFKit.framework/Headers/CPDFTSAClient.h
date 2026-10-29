//
//  CPDFTSAClient.h
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
#import <ComPDFKit/CPDFDeferredSignSession.h>

NS_ASSUME_NONNULL_BEGIN

/// The number of bytes a message imprint produced by `algorithm` must have,
/// or 0 when the algorithm is unknown.
FOUNDATION_EXPORT NSUInteger CPDFSignatureDigestLength(CPDFSignatureDigestAlgorithm algorithm);

#pragma mark - Request

/// A timestamp request handed to a `CPDFTSAClient` by the signing pipeline.
///
/// Instances are created by the framework. The digest has already been computed;
/// a client is only responsible for building the RFC 3161 `TimeStampReq`,
/// transporting it to the TSA, and returning the token from the response.
@interface CPDFTimestampRequest : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/// The algorithm `messageImprint` was produced with.
@property (nonatomic,readonly) CPDFSignatureDigestAlgorithm digestAlgorithm;

/// The precomputed digest of the data being timestamped.
/// Its length always matches `CPDFSignatureDigestLength(digestAlgorithm)`.
@property (nonatomic,readonly,copy) NSData *messageImprint;

/// The requested TSA policy OID in dotted form, or an empty string when the caller
/// did not request a specific policy.
@property (nonatomic,readonly,copy) NSString *policyOID;

/// Whether the request should carry a random nonce for replay protection.
@property (nonatomic,readonly) BOOL includeNonce;

/// Whether the TSA should be asked to embed its certificate in the response
/// (the RFC 3161 `certReq` field).
@property (nonatomic,readonly) BOOL requestCertificates;

@end

#pragma mark - Response

/// The result a `CPDFTSAClient` returns for a `CPDFTimestampRequest`.
@interface CPDFTimestampResponse : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/// A successful response carrying the RFC 3161 timestamp token.
/// @param tokenDER The DER encoding of the `TimeStampToken` (a CMS `ContentInfo`)
/// taken from the TSA response. Must not be empty.
/// @param genTime The TSA generation time, or `nil` when the client did not parse it out.
/// This value is informational; the core library does not require it.
+ (instancetype)responseWithTokenDER:(NSData *)tokenDER genTime:(nullable NSString *)genTime;

/// A failed response.
/// @param errorCode A stable identifier. Use the groups the core library documents so
/// diagnostics stay uniform: `timestamp.digest.*`, `timestamp.imprint.*`,
/// `timestamp.request.*`, `timestamp.transport.*`, `timestamp.response.*`.
/// @param errorMessage A human readable description, or `nil`.
+ (instancetype)failureWithErrorCode:(NSString *)errorCode errorMessage:(nullable NSString *)errorMessage;

/// Whether the TSA returned a usable timestamp token.
@property (nonatomic,readonly,getter=isSuccess) BOOL success;

/// The DER encoded `TimeStampToken`, or `nil` on failure.
@property (nonatomic,readonly,copy,nullable) NSData *tokenDER;

/// The TSA generation time, or `nil` when unavailable.
@property (nonatomic,readonly,copy,nullable) NSString *genTime;

/// A stable error identifier, or `nil` on success.
@property (nonatomic,readonly,copy,nullable) NSString *errorCode;

/// A human readable error description, or `nil`.
@property (nonatomic,readonly,copy,nullable) NSString *errorMessage;

@end

#pragma mark - Client

/// Transport for RFC 3161 timestamp requests.
///
/// Adopt this protocol to route timestamping through your own networking stack —
/// `NSURLSession` with App Transport Security, the system proxy configuration,
/// certificate pinning, client certificates, or an offline / air-gapped service.
/// `CPDFURLSessionTSAClient` is a ready-made implementation of exactly that.
///
/// @warning `-requestTimestamp:` is invoked **synchronously** from inside the signing
/// call, on the framework's serialized task queue — not on the main thread. Block
/// until the answer is available and never dispatch synchronously to the main queue
/// from it, or the signing call will deadlock.
@protocol CPDFTSAClient <NSObject>

@required

/// Perform one timestamp exchange.
///
/// @param request The request to satisfy.
/// @return A response. Never return `nil`; use `+[CPDFTimestampResponse failureWithErrorCode:errorMessage:]`
/// to report a failure.
- (CPDFTimestampResponse *)requestTimestamp:(CPDFTimestampRequest *)request;

@end

#pragma mark - NSURLSession client

/// A `CPDFTSAClient` that talks to an RFC 3161 TSA over `NSURLSession`.
///
/// This is the recommended client on both macOS and iOS: the request travels through
/// the system networking stack, so App Transport Security, the system proxy
/// configuration, VPN routing, and any `NSURLSessionDelegate` based certificate
/// pinning or client certificate handling all apply. It builds the `TimeStampReq`
/// and parses the `TimeStampResp` itself and has no OpenSSL dependency.
///
/// @note The response token is returned verbatim; this client does not verify the
/// TSA signature or match the nonce back. The core library verifies the token
/// against the signature when it embeds it.
@interface CPDFURLSessionTSAClient : NSObject <CPDFTSAClient>

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/// Create a client for a TSA endpoint.
/// @param URL The TSA endpoint. `http` and `https` are supported.
- (instancetype)initWithURL:(NSURL *)URL NS_DESIGNATED_INITIALIZER;

/// The TSA endpoint.
@property (nonatomic,readonly,copy) NSURL *URL;

/// The session used for the exchange. Defaults to a session with the ephemeral
/// configuration. Replace it to install a delegate for pinning or client certificates.
@property (nonatomic,strong) NSURLSession *session;

/// Request timeout in seconds. Defaults to 20, matching the core library's HTTP client.
@property (nonatomic,assign) NSTimeInterval timeoutInterval;

/// The `Content-Type` sent with the request. Defaults to `application/timestamp-query`.
@property (nonatomic,copy) NSString *contentType;

/// Extra header fields merged into the request.
@property (nonatomic,copy) NSDictionary<NSString *, NSString *> *additionalHeaderFields;

/// Reject responses larger than this. Defaults to 10 MB, matching the core library.
@property (nonatomic,assign) NSUInteger maximumResponseSize;

/// How many times to retry after a transport failure. Defaults to 0.
@property (nonatomic,assign) NSUInteger retryCount;

@end

#pragma mark - Built-in HTTP client

/// A `CPDFTSAClient` backed by the core library's own HTTP client.
///
/// @warning This client performs a **synchronous, blocking HTTP request inside the
/// core library**, using its own TLS stack and default trust store. It
/// bypasses `NSURLSession` entirely, and with it App Transport Security, the system
/// proxy and VPN configuration, and any certificate pinning the app installs. Prefer
/// `CPDFURLSessionTSAClient`. This class exists for desktop tooling and for parity
/// with the core library's own behaviour; it is not recommended for shipping
/// applications.
@interface CPDFHttpTSAClient : NSObject <CPDFTSAClient>

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/// Create a client for a TSA endpoint.
/// @param URLString The TSA endpoint. `http://` and `https://` are supported.
- (instancetype)initWithURLString:(NSString *)URLString NS_DESIGNATED_INITIALIZER;

/// The TSA endpoint.
@property (nonatomic,readonly,copy) NSString *URLString;

/// Request timeout in seconds. Defaults to 20.
@property (nonatomic,assign) NSInteger timeoutSeconds;

/// Reject responses larger than this. Defaults to 10 MB.
@property (nonatomic,assign) NSUInteger maximumResponseSize;

/// The `Content-Type` sent with the request. Defaults to `application/timestamp-query`.
@property (nonatomic,copy) NSString *contentType;

/// An explicit proxy URL. When empty the core library falls back to the
/// `HTTPS_PROXY` / `HTTP_PROXY` environment variables — note that this is *not*
/// the system proxy configuration.
@property (nonatomic,copy) NSString *proxyURLString;

/// How many times to retry after a transport failure. Defaults to 0.
@property (nonatomic,assign) NSInteger retryCount;

/// Extra header fields sent with the request.
@property (nonatomic,copy) NSDictionary<NSString *, NSString *> *additionalHeaderFields;

@end

NS_ASSUME_NONNULL_END
