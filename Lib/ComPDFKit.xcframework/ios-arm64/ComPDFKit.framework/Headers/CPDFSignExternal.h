//
//  CPDFSignExternal.h
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

#pragma mark - Algorithms

/// The signature algorithm an external signer used to produce a signature value.
///
/// @note This must describe what the key actually did. Reporting `RSA_PKCS1_v1_5`
/// for a PSS signature produces a container that no verifier will accept.
typedef NS_ENUM(NSInteger, CPDFExternalSignatureAlgorithm) {
    CPDFExternalSignatureAlgorithmRSAPKCS1v15 = 0,
    CPDFExternalSignatureAlgorithmRSAPSS,
    CPDFExternalSignatureAlgorithmECDSA,
    CPDFExternalSignatureAlgorithmUnknown,
};

/// What the bytes handed to an external signer actually are.
typedef NS_ENUM(NSInteger, CPDFExternalSignDataKind) {
    /// The raw bytes covered by the ByteRange. The signer must digest them itself.
    CPDFExternalSignDataKindRawByteRangeDigest = 0,
    /// A precomputed digest of the ByteRange, ready to be signed.
    CPDFExternalSignDataKindDigest,
    /// The DER-encoded CMS SignedAttributes to sign. This is what a PAdES-conformant
    /// container needs, and the kind the SDK requests by default.
    CPDFExternalSignDataKindSignedAttributes,
};

#pragma mark - External sign request / result

/// The bytes the SDK needs signed, handed to your `CPDFSignExternal` implementation.
@interface CPDFExternalSignRequest : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/// How to interpret `data`.
@property (nonatomic,readonly) CPDFExternalSignDataKind dataKind;

/// The digest that produced `data`, or the digest the signer must apply to it when
/// `dataKind` is `RawByteRangeDigest`.
@property (nonatomic,readonly) CPDFSignatureDigestAlgorithm digestAlgorithm;

/// The bytes to sign.
@property (nonatomic,readonly,copy) NSData *data;

/// The signature field this request belongs to. Empty when the SDK is signing a
/// field it created itself and has not yet named.
@property (nonatomic,readonly,copy) NSString *fieldName;

@end

/// What your `CPDFSignExternal` implementation returns for one signing request.
@interface CPDFExternalSignResult : NSObject

/// A successful result. `signatureValue` is the raw signature bytes — for RSA the
/// modulus-sized block, for ECDSA the DER `SEQUENCE { r, s }`, never a container.
+ (instancetype)resultWithSignatureValue:(NSData *)signatureValue
                               algorithm:(CPDFExternalSignatureAlgorithm)algorithm;

/// A failure. `errorCode` and `errorMessage` are surfaced verbatim in the workflow
/// result's `errors`, so make them specific enough to act on.
+ (instancetype)failureResultWithErrorCode:(nullable NSString *)errorCode
                              errorMessage:(nullable NSString *)errorMessage;

@property (nonatomic,assign) BOOL success;
@property (nonatomic,copy,nullable) NSData *signatureValue;
@property (nonatomic,assign) CPDFExternalSignatureAlgorithm signatureAlgorithm;
@property (nonatomic,copy,nullable) NSString *errorCode;
@property (nonatomic,copy,nullable) NSString *errorMessage;

@end

#pragma mark - External signer

/// A signing key the SDK cannot reach directly: a smart card, an HSM, a remote
/// signing service, or anything else that holds the private key.
///
/// The SDK builds the CMS structure and asks you only to sign bytes. Use this with
/// `-[CPDFSignatureWorkflow signExternalDetachedPKCS7…]` when you want the SDK to
/// assemble the container, or with the prepare/fill pair when the signing happens
/// in another process or on another machine.
///
/// @warning The SDK calls these methods synchronously on whichever thread drives the
/// signing call. A network-backed signer will block that thread; do not drive it from
/// the main thread.
@protocol CPDFSignExternal <NSObject>

@required

/// Sign `request`. Return a failure result rather than raising; an exception thrown
/// out of this method will terminate the process.
- (CPDFExternalSignResult *)signRequest:(CPDFExternalSignRequest *)request;

/// Whether this signer can supply its signing certificate. When `NO`, the SDK expects
/// the certificate to come from elsewhere and will not call the two methods below.
- (BOOL)providesCertificate;

@optional

/// The DER-encoded signing certificate. Required when `-providesCertificate` is `YES`.
- (nullable NSData *)signerCertificateDER;

/// The DER-encoded intermediate certificates, leaf first, trust anchor last.
/// Return `nil` or an empty array when only the leaf is available — the resulting
/// container will still verify, but chain building will need the intermediates from
/// somewhere else.
- (nullable NSArray<NSData *> *)certificateChainDER;

@end

#pragma mark - Container request / result

/// The digests the SDK needs wrapped in a CMS container.
@interface CPDFExternalContainerRequest : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@property (nonatomic,readonly) CPDFSignatureDigestAlgorithm digestAlgorithm;

/// The digest of the whole signed document content.
@property (nonatomic,readonly,copy) NSData *documentDigest;

/// The digest computed over the ByteRange. Equal to `documentDigest` for the ordinary
/// single-range case; both are provided so a container builder need not recompute.
@property (nonatomic,readonly,copy) NSData *byteRangeDigest;

@property (nonatomic,readonly,copy) NSString *fieldName;

@end

/// A complete CMS container, ready to be written into `/Contents`.
@interface CPDFExternalContainerResult : NSObject

/// A successful result carrying the DER-encoded CMS `SignedData`.
+ (instancetype)resultWithContainerDER:(NSData *)containerDER;

+ (instancetype)failureResultWithErrorCode:(nullable NSString *)errorCode
                              errorMessage:(nullable NSString *)errorMessage;

@property (nonatomic,assign) BOOL success;

/// The DER-encoded CMS container. Detached: it carries no document content.
@property (nonatomic,copy,nullable) NSData *containerDER;

@property (nonatomic,copy,nullable) NSString *errorCode;
@property (nonatomic,copy,nullable) NSString *errorMessage;

@end

#pragma mark - Container provider

/// A source of complete CMS containers, for when the container itself is produced
/// outside the SDK — a signing appliance that returns finished PKCS#7, for instance.
///
/// Prefer `CPDFSignExternal` unless you genuinely need to control the container:
/// with `CPDFSignExternal` the SDK builds a PAdES-conformant structure for you.
///
/// @warning Called synchronously, like `CPDFSignExternal`. Do not drive a
/// network-backed implementation from the main thread.
@protocol CPDFSignContainer <NSObject>

@required

/// Build a detached CMS container over the digests in `request`.
- (CPDFExternalContainerResult *)signContainerWithRequest:(CPDFExternalContainerRequest *)request;

@end

#pragma mark - Detached PKCS#7 assembly

/// The material needed to assemble a detached PKCS#7 container from a signature value
/// that was produced elsewhere.
///
/// This is the seam for a two-phase flow whose second phase happens off-device: take
/// the digest from `CPDFPreparedExternalSignatureInfo`, sign it wherever the key lives,
/// then assemble the container here and hand it to
/// `-[CPDFSignatureWorkflow fillSignatureAtPath:options:]`.
@interface CPDFDetachedPKCS7ContainerOptions : NSObject

/// The digest the signature value was computed over. Defaults to `SHA256`.
@property (nonatomic,assign) CPDFSignatureDigestAlgorithm digestAlgorithm;

/// The DER-encoded signing certificate. Required.
@property (nonatomic,copy,nullable) NSData *signerCertificateDER;

/// DER-encoded intermediates to embed, leaf first.
@property (nonatomic,copy,nullable) NSArray<NSData *> *certificateChainDER;

/// The raw signature bytes. Required.
@property (nonatomic,copy,nullable) NSData *signatureValue;

/// The algorithm that produced `signatureValue`. Defaults to `RSAPKCS1v15`.
@property (nonatomic,assign) CPDFExternalSignatureAlgorithm signatureAlgorithm;

/// Assemble the container.
///
/// @param options The certificate, chain, and signature value to wrap.
/// @return A result whose `containerDER` can be written into `/Contents`, or a failure
/// result describing what was missing or malformed.
+ (CPDFExternalContainerResult *)buildDetachedPKCS7ContainerWithOptions:(CPDFDetachedPKCS7ContainerOptions *)options;

@end

NS_ASSUME_NONNULL_END
