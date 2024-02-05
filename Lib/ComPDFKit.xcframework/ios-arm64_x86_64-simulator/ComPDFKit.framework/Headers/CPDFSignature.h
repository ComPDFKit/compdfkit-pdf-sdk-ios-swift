//
//  CPDFSignature.h
//  ComPDFKit
//
//  Copyright © 2014-2024 PDF Technologies, Inc. All Rights Reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE ComPDFKit LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <ComPDFKit/CPDFKitPlatform.h>

@class CPDFDocument;
@class CPDFSignatureWidgetAnnotation;

typedef NS_ENUM(NSInteger, CPDFSignatureOCSPStatus) {
    CPDFSignatureOCSPStatusNone = -2,
    CPDFSignatureOCSPStatusFail = -1,
    CPDFSignatureOCSPStatusGood = 0,
    CPDFSignatureOCSPStatusRevoked = 1
};

typedef NS_ENUM(NSInteger, CPDFSignatureAlgorithmType) {
    CPDFSignatureAlgorithmTypeRSA_RSA = 0, /*RSA_RSA*/
    CPDFSignatureAlgorithmTypeMD2RSA, /*MD2RSA*/
    CPDFSignatureAlgorithmTypeMD4RSA, /*MD4RSA*/
    CPDFSignatureAlgorithmTypeMD5RSA, /*MD5RSA*/
    CPDFSignatureAlgorithmTypeSHA1RSA, /*SHA1RSA*/
    CPDFSignatureAlgorithmTypeSHA256RSA, /*SHA256RSA*/
    CPDFSignatureAlgorithmTypeSM3SM2, /*SM3SM2*/
};

typedef NS_OPTIONS(NSInteger, CPDFSignatureKeyUsageType) {
    CPDFSignatureKeyUsageTypeEncipherOnly = (1),            /*Encipher Only*/
    CPDFSignatureKeyUsageTypeCRLSignature = (1UL << 1),            /*CRL Signature*/
    CPDFSignatureKeyUsageTypeCertificateSignature = (1UL << 2),    /*Certificate Signature*/
    CPDFSignatureKeyUsageTypeKeyAgreement= (1UL << 3),             /*Key Agreement*/
    CPDFSignatureKeyUsageTypeDataEncipherment = (1UL << 4),        /*Data Encipherment*/
    CPDFSignatureKeyUsageTypeKeyEncipherment = (1UL << 5),         /*Key Encipherment*/
    CPDFSignatureKeyUsageTypeNonRepudiation = (1UL << 6),          /*Non-Repudiation*/
    CPDFSignatureKeyUsageTypeDigitalSignature = (1UL << 7),        /*Digital Signature*/
    CPDFSignatureKeyUsageTypeDDecipherOnly = (1UL << 15),           /*Decipher Only*/
};

typedef NS_ENUM(NSInteger, CPDFModifyType) {
    CPDFModifyNone = 0,
    CPDFModifyAddPage,
    CPDFModifyDeletePage,
    CPDFModifyPage,
    CPDFModifyAddAnnotation,
    CPDFModifyDeleteAnnotation,
    CPDFModifyAnnotation,
    CPDFModifyFillForm,
    CPDFModifyRootIncrease,
    CPDFModifyDocument
};

typedef NS_ENUM(NSInteger, CPDFCertUsage) {
    CPDFCertUsageDigSig = 1,
    CPDFCertUsageDataEnc = 2,
    CPDFCertUsageAll = 3,
};

@interface CPDFModifyInfo : NSObject

/**
 * Modify types.
 */
@property (nonatomic,readonly) CPDFModifyType type;

/**
 * Change the page number of the document.
 */
@property (nonatomic,readonly) NSInteger pageIndex;

/**
 * Annotation types. When the annotation type is CPDFModifyAddAnnotation, CPDFModifyDeleteAnnotation, or CPDFModifyAnnotation, there would be a value.
 */
@property (nonatomic,readonly) NSInteger annotationType;

/**
 * Form field types. When the form field type is CPDFModifyFillForm, there would be a value.
 */
@property (nonatomic,readonly) NSInteger formType;

/**
 * The differences after modifying.
 */
@property (nonatomic,readonly) NSString *info;

@end

@interface CPDFSignatureCertificate : NSObject

/**
 * Certificate version.
 */
@property (nonatomic,readonly) NSString *version;

/**
 * Get the signature algorithm.
 */
@property (nonatomic,readonly) NSString *signatureAlgorithmOID;

/**
 * Get the type of signature algorithm.
 */
@property (nonatomic,readonly) CPDFSignatureAlgorithmType signatureAlgorithmType;

/**
 * Get the subject of the certificate.
 */
@property (nonatomic,readonly) NSString *subject;

/**
 * C (Country), ST (Province), L (Locality)；O (Organization), OU (Organizational Unit), CN (Common Name)
 */
@property (nonatomic,readonly) NSDictionary *subjectDict;

/**
 * Get the issuer of the certificate.
 */
@property (nonatomic,readonly) NSString *issuer;

/**
 * C (Country), ST (Province), L (Locality)；O (Organization), OU (Organizational Unit), CN (Common Name)
 */
@property (nonatomic,readonly) NSDictionary *issuerDict;

/**
 * Get the serial number of the certificate.
 */
@property (nonatomic,readonly) NSString *serialNumber;

/**
 * Get the validity start date.
 */
@property (nonatomic,readonly) NSDate *validityStarts;

/**
 * Get the validity end date.
 */
@property (nonatomic,readonly) NSDate *validityEnds;

@property (nonatomic,readonly) NSString *dats;

/**
 * Get the access of the issuer information.
 */
@property (nonatomic,readonly) NSArray<NSDictionary *> *authorityInfoAccess;

/**
 * Get the subject's key identifier.
 */
@property (nonatomic,readonly) NSString *subjectKeyIdentifier;

/**
 * Get the types of key usage.
 */
@property (nonatomic,readonly) CPDFSignatureKeyUsageType keyUsage;

/**
 * Get the certificate policies.
 */
@property (nonatomic,readonly) NSString *certificatePolicies;

/**
 * Get the issuer‘s key identifier.
 */
@property (nonatomic,readonly) NSString *authorityKeyIdentifier;

/**
 * Get the CRL Distribution Points.
 */
@property (nonatomic,readonly) NSArray<NSString *> *CRLDistributionPoints;

/**
 * Basic Constraints.
 */
@property (nonatomic,readonly) NSString *basicConstraints;

/**
 * Public Key.
 */
@property (nonatomic,readonly) NSString *publicKey;

/**
 * Get X.509 data.
 */
@property (nonatomic,readonly) NSString *X509Data;

/**
 * SHA1 digest.
 */
@property (nonatomic,readonly) NSString *SHA1Digest;

/**
 * MD5 digest.
 */
@property (nonatomic,readonly) NSString *MD5Digest;

/**
 * OCSP url.
 */
@property (nonatomic,readonly) NSString *ocspURL;

/**
 * OCSP authentication status.
 */
@property (nonatomic,readonly) CPDFSignatureOCSPStatus ocspStatus;

/**
 * Be trusted or not.
 */
@property (nonatomic,readonly) BOOL isTrusted;

/**
 * OCSP authentication.
 */
- (void)verifyOCSPWithCompletionHandler:(void (^)(BOOL result, CPDFSignatureOCSPStatus ocspStatus))handler;

/**
 * Export the certificate to a file.
 * @param path Certificate save path.
 * @return Return true: Export successfully. Return false: Export failed.
 */
- (BOOL)exportToFilePath:(NSString *)filePath;

/**
 * Set up a certificate trust folder, default sandbox path.
 */
- (void)setSignCertTrustedFolder:(NSString *)signCertTrustedFolder;

/**
 * Add certificate to the trusted list.
 */
- (BOOL)addToTrustedCertificates;

/**
     * Check whether the password of the certificate file is correct.
     * @param path The certificate file path.
     * @param password The password of the certificate file.

     * @return If the return value is not null, the password is correct.
*/
+ (CPDFSignatureCertificate *)certificateWithPKCS12Path:(NSString *)path password:(NSString *)password;

/**
 * The certificate is trusted or not.
 */
- (void)checkCertificateIsTrusted;

@end

@class CPDFSignature;

@interface CPDFSigner : NSObject

/**
 * Whether authorized by the signer.
 */
@property (nonatomic,readonly) BOOL isSignVerified;

/**
 * Whether the certificate is in the trusted list.
 */
@property (nonatomic,readonly) BOOL isCertTrusted;

/**
 * Get the certificate.
 */
@property (nonatomic,readonly) NSArray<CPDFSignatureCertificate*> *certificates;

/**
 * Get the timestamp signature.
 */
@property (nonatomic,readonly) CPDFSignature *timestampSignature;

/**
 * Get the time on the timestamps signature.
 */
@property (nonatomic,readonly) NSDate *authenDate;

@end

@interface CPDFSignature : NSObject
/**
 * Get signer of who signed the document.
 */
@property (nonatomic,readonly) NSArray<CPDFSigner *> *signers;

/**
 * Get all changes to the document.
 */
@property (nonatomic,readonly) NSArray<CPDFModifyInfo *> *modifyInfos;

/**
 * Get the field name of signature form field.
 */
@property (nonatomic,readonly) NSString *fieldName;

/**
 * Get the location where the signature form field is located.
 */
@property (nonatomic,readonly) CGRect bounds;

/**
 * The name of the signer or issuer who signed the document.
 */
@property (nonatomic,readonly) NSString *name;

/**
 * Get the signing time of the document.
 */
@property (nonatomic,readonly) NSDate *date;

/**
 * Get the filter of the signature.
 */
@property (nonatomic,readonly) NSString *filter;

/**
 * Get the sub filter of the signature.
 */
@property (nonatomic,readonly) NSString *subFilter;
/**
 * Get the signing reason.
 */
@property (nonatomic,readonly) NSString *reason;

/**
 * The hostname or physical location of the CPU which was used to sign the document.
 */
@property (nonatomic,readonly) NSString *location;

/**
 Signature Permission
  * The access permissions granted for this document.
  *
  * @discussion Valid values shall be:
  *     1: No changes to the document shall be permitted. Any change to the document shall invalidate the signature.
  *     2: Permitted changes shall be filling in forms, instantiating page templates, and signing. Other changes shall invalidate the signature.
  *     3: Permitted changes shall be filling in forms, instantiating page templates, signing, and annotation creation, deletion, and modification. Other changes shall invalidate the signature.
*/
@property (nonatomic,readonly) NSInteger permissions;

/**
 * Get the page index of the signature.
 * @param document CPDFDocument object.
 * @return Return the page index of the signature.
*/
- (NSUInteger)pageIndexWithDocument:(CPDFDocument *)document;

/**
 * Verify the permissions.
 * @param document The CPDFDocument object that needs to be verified.
*/
- (void)verifySignatureWithDocument:(CPDFDocument *)document;

/**
 * Sign the corresponding signature field.
 * @param document Signed file object CPDFDocument.
 * @return Sign forms.
*/
- (CPDFSignatureWidgetAnnotation *)signatureWidgetAnnotationWithDocument:(CPDFDocument *)document;

/**
 * Create a PKCS12 certificate.
 * C (Country), ST (Province), L (Locality)；O (Organization), OU (Organizational Unit), CN (Common Name), emailAddress (Email Address).
 * info: "/C=cn/ST=bj/L=bj/O=hd/OU=dev/CN=hello/emailAddress=hello@world.com"
 * @param info  object.
 * @param password  Certificate file password.
 * @param save_path Certificate file save path.
 * @param certUsage The usage of this certificate.
 * @return Return true: Succeed. Return false: Fail.
*/
+ (BOOL)generatePKCS12CertWithInfo:(NSDictionary *)info password:(NSString *)password toPath:(NSString *)path certUsage:(CPDFCertUsage)certUsage;

@end
