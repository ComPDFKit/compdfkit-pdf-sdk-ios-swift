//
//  CPDFKit.h
//  ComPDFKit
//
//  Copyright © 2014-2024 PDF Technologies, Inc. All Rights Reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE ComPDFKit LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <Foundation/Foundation.h>

typedef NS_ENUM(NSInteger, CPDFKitFeatureType) {
    CPDFKitFeatureViewerOutline,
    CPDFKitFeatureViewerBookmark,
    CPDFKitFeatureViewerRender,
    CPDFKitFeatureViewerSearch,
    CPDFKitFeatureAnnotationNote,
    CPDFKitFeatureAnnotationLink,
    CPDFKitFeatureAnnotationFreeText,
    CPDFKitFeatureAnnotationShape,
    CPDFKitFeatureAnnotationMarkup,
    CPDFKitFeatureAnnotationStandardStamp,
    CPDFKitFeatureAnnotationCustomizedStamp,
    CPDFKitFeatureAnnotationInk,
    CPDFKitFeatureAnnotationSound,
    CPDFKitFeatureAnnotationDelete,
    CPDFKitFeatureAnnotationFlatten,
    CPDFKitFeatureAnnotationXFDF,
    CPDFKitFeatureForm,
    CPDFKitFeatureFormFill,
    CPDFKitFeatureEditorPage,
    CPDFKitFeatureEditorExtract,
    CPDFKitFeatureEditorInfo,
    CPDFKitFeatureEditorConvert,
    CPDFKitFeatureSecurityEncrypt,
    CPDFKitFeatureSecurityDecrypt,
    CPDFKitFeatureSecurityWatermark,
    CPDFKitFeatureConversionPDFA,
    CPDFKitFeatureConversionCompareFile,
    CPDFKitFeatureConversionDigitalSignature,
    CPDFKitFeatureConversionAllowsEditText,
    CPDFKitFeatureConversionAllowsEditImage,

};

typedef NS_ENUM(NSInteger, CPDFKitLicenseCode) {
    CPDFKitLicenseCodeSuccess,
    CPDFKitLicenseCodeInvalid,
    CPDFKitLicenseCodeExpire,
    CPDFKitLicenseCodeUnsupportedPlatform,
    CPDFKitLicenseCodeUnsupportedID,
    CPDFKitLicenseCodeUnsupportedDevice,
    CPDFKitLicenseCodePermissionDeny,
    CPDFKitLicenseCodeUninitialized,
    CPDFKitLicenseCodeIllegalAccess,
    CPDFKitLicenseCodeReadFailed,
};

typedef NS_ENUM(NSInteger, CPDFKitOnlineLicenseCode) {
    CPDFKitOnlineLicenseCodeSuccess = 200,
    CPDFKitOnlineLicenseCodeInvalid = 1001,
    CPDFKitOnlineLicenseCodeExpire = 1002,
    CPDFKitOnlineLicenseCodeUnsupportedPlatform = 1003,
    CPDFKitOnlineLicenseCodeUnsupportedID = 1004,
    CPDFKitOnlineLicenseCodeUnsupportedDevice = 1005,
    CPDFKitOnlineLicenseCodePermissionDeny = 1006,
    CPDFKitOnlineLicenseCodeUninitialized = 1007,
    CPDFKitOnlineLicenseCodeIllegalAccess = 1008,
    CPDFKitOnlineLicenseCodeReadFailed = 1009,
    CPDFKitOnlineLicenseCodeNetworkError = 2001,
    CPDFKitOnlineLicenseCodeNetworkTimeout = 2002,
    CPDFKitOnlineLicenseCodeLicenseRequired = 2003,
    CPDFKitOnlineLicenseCodeSignatureVerificationFailed = 2004,
    CPDFKitOnlineLicenseCodeVerifyFailed = 2005
};

typedef void (^CPDFLicenseCompletionHandler)(CPDFKitOnlineLicenseCode code, NSString *message);

@interface CPDFKit : NSObject

/**
 * The shared ComPDFKit instance.
 */
+ (instancetype)sharedInstance;

/**
 * Activate ComPDFKit with your license key.
 */
+ (CPDFKitLicenseCode)verifyWithKey:(NSString *)key;

/**
 * Activate ComPDFKit with your online license.
 */
+ (void)verifyWithOnlineLicense:(NSString *)license completionHandler:(CPDFLicenseCompletionHandler)handler;

/**
 * Returns the full ComPDFKit product version string. (e.g. "ComPDFKit 1.0.1 for iOS (101)")
 */
@property(atomic,readonly) NSString *versionString;

/**
 * Returns just the framework version. (e.g. 1.0.1)
 */
@property(atomic,readonly) NSString *versionNumber;

/**
 * The internal build number. Increments with every version.
 */
@property(atomic,readonly) NSUInteger buildNumber;

/**
 * Whether to allow to use specified features.
 *
 * @see CPDFKitFeatureType
 */
- (BOOL)allowsFeature:(CPDFKitFeatureType)type;

/**
 * Convert files (doc, docx, xls, xlsx, ppt, pptx, txt, jpeg, and png) to PDF.
 */
- (void)convertFilePath:(NSString *)filePath toPath:(NSString *)pdfFilePath completion:(void (^)(BOOL result))completion;

@end
