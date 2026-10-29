//
//  CPDFTimestamp.h
//  ComPDFKit
//
//  Copyright © 2014-2026 PDF Technologies, Inc. All Rights Reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE ComPDFKit LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <ComPDFKit/CPDFTSAClient.h>

NS_ASSUME_NONNULL_BEGIN

#pragma mark - Options

/// How an RFC 3161 timestamp request should be built.
///
/// The defaults are SHA-256, no policy OID, a nonce, and a request for the TSA
/// certificate.
@interface CPDFTimestampOptions : NSObject

/// The digest algorithm used for the message imprint. Defaults to
/// `CPDFSignatureDigestAlgorithmSHA256`.
@property (nonatomic,assign) CPDFSignatureDigestAlgorithm digestAlgorithm;

/// The TSA policy OID in dotted form, or an empty string to let the TSA choose.
/// Defaults to an empty string.
@property (nonatomic,copy) NSString *policyOID;

/// Whether to include a random nonce for replay protection. Defaults to `YES`.
@property (nonatomic,assign) BOOL includeNonce;

/// Whether to ask the TSA to embed its certificate in the response (the RFC 3161
/// `certReq` field). Defaults to `YES`.
@property (nonatomic,assign) BOOL requestCertificates;

@end

#pragma mark - Service

/// Standalone RFC 3161 timestamping: digest → request → TSA exchange → token.
///
/// Use this when you need a timestamp token on its own — timestamping a detached
/// hash, pre-flighting a TSA endpoint before signing, or building an external
/// signing container yourself. Timestamping a *signature* does not need this
/// class: set `CPDFSigningIdentity.tsaClient` (or `timestampServerURL`) and the
/// signing pipeline requests the token itself. A whole-document timestamp is a
/// `CPDFSigningIdentity` created with
/// `+documentTimestampIdentityWithTSAClient:`.
///
/// @warning `-timestampData:options:` and `-timestampMessageImprint:options:`
/// perform a **synchronous** network exchange on the calling thread. Never call
/// them on the main thread.
@interface CPDFTimestampService : NSObject

/// A service with no client. Timestamp requests fail with
/// `timestamp.request.no_client` until `tsaClient` is set.
- (instancetype)init;

/// A service that routes requests through `tsaClient`.
/// @param tsaClient The transport. `CPDFURLSessionTSAClient` is the recommended
/// implementation on both macOS and iOS.
- (instancetype)initWithTSAClient:(nullable id<CPDFTSAClient>)tsaClient NS_DESIGNATED_INITIALIZER;

/// The transport used for every exchange. Setting `nil` disables timestamping
/// until a client is set again.
///
/// @note Held strongly. The core library keeps only a non-owning pointer to the
/// bridged client, so the service has to be the thing that keeps it alive.
@property (nonatomic,strong,nullable) id<CPDFTSAClient> tsaClient;

/// Digest `data`, send the imprint to the TSA, and return the response.
///
/// @param data The bytes to timestamp.
/// @param options The request options, or `nil` for the defaults.
/// @return Never `nil`. On failure `success` is `NO` and `errorCode` carries a
/// `timestamp.*` identifier.
- (CPDFTimestampResponse *)timestampData:(NSData *)data
                                 options:(nullable CPDFTimestampOptions *)options;

/// Send an already computed message imprint to the TSA.
///
/// @param messageImprint The digest. Its length must be
/// `CPDFSignatureDigestLength(options.digestAlgorithm)`, otherwise the call fails
/// with `timestamp.imprint.*`.
/// @param options The request options, or `nil` for the defaults.
/// @return Never `nil`.
- (CPDFTimestampResponse *)timestampMessageImprint:(NSData *)messageImprint
                                           options:(nullable CPDFTimestampOptions *)options;

/// Digest `data` with `algorithm`. No TSA communication.
///
/// @return The digest, or `nil` when `algorithm` is not supported.
+ (nullable NSData *)computeDigestOfData:(NSData *)data
                               algorithm:(CPDFSignatureDigestAlgorithm)algorithm;

@end

NS_ASSUME_NONNULL_END
