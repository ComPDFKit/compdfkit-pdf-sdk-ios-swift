//
//  CPDFSignatureWidgetAnnotation.h
//  ComPDFKit
//
//  Copyright © 2014-2026 PDF Technologies, Inc. All Rights Reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE ComPDFKit LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <ComPDFKit/CPDFWidgetAnnotation.h>

typedef NS_ENUM(NSInteger, CPDFSignatureWidgetDraggedType) {
    CPDFSignatureWidgetDraggedTypeNone = -1,
    CPDFSignatureWidgetDraggedTypeMinXMinY = 0,
    CPDFSignatureWidgetDraggedTypeMidXMinY = 1,
    CPDFSignatureWidgetDraggedTypeMaxXMinY = 2,
    CPDFSignatureWidgetDraggedTypeMaxXMidY = 3,
    CPDFSignatureWidgetDraggedTypeMaxXMaxY = 4,
    CPDFSignatureWidgetDraggedTypeMidXMaxY = 5,
    CPDFSignatureWidgetDraggedTypeMinXMaxY = 6,
    CPDFSignatureWidgetDraggedTypeMinXMidY = 7,
};

@class CPDFSignature;

#pragma mark - CPDFSignatureConfigItem

@interface CPDFSignatureConfigItem : NSObject

@property (nonatomic,copy) NSString *key;
@property (nonatomic,copy) NSString *value;

@end

#pragma mark - CPDFSignatureConfig

@interface CPDFSignatureConfig : NSObject

@property (nonatomic,strong) NSArray<CPDFSignatureConfigItem *> *contents;

@property (nonatomic,assign) BOOL isDrawKey;
@property (nonatomic,assign) BOOL isDrawLogo;
@property (nonatomic,assign) BOOL isDrawOnlyContent;
@property (nonatomic,assign) BOOL isContentAlginLeft;

@property (nonatomic,assign) BOOL isSetSignAP;

@property (nonatomic,copy) NSString *text;
@property (nonatomic,strong) CPDFKitPlatformImage *image;
@property (nonatomic,strong) CPDFKitPlatformImage *logo;

@property (nonatomic,strong) CPDFKitPlatformColor *contentsColor;
@property (nonatomic,strong) CPDFKitPlatformColor *textColor;

@end

#pragma mark - CPDFSignatureWidgetAnnotation

@interface CPDFSignatureWidgetAnnotation : CPDFWidgetAnnotation

- (BOOL)isSigned;

- (void)signWithImage:(CPDFKitPlatformImage *)image;


#pragma mark - Digital Signature

/**
 * Get the signature of a signature widget.
 */
- (CPDFSignature *)signature;

/**
 * Remove the corresponding signature
 */
- (void)removeSignature;

/**
 * Configure the appearance of signatures.
 */
- (void)signAppearanceConfig:(CPDFSignatureConfig *)config;


#pragma mark - Dynamic Verify

/**
 * Check whether the signature has a dynamic appearance.
 */
- (BOOL)isDynamicSignAppearance;

/**
 * Configure the dynamic appearance of signatures.
 */
- (void)signDynamicAppearanceConfig:(CPDFSignatureConfig *)config;

/**
 *Getting the dynamic appearance of signatures.
 */
- (CPDFKitPlatformImage *)getDynamicSignAppearance;

@end

@interface CPDFSignatureWidgetAnnotation (Deprecated)

- (void)signWithSignatureConfig:(CPDFSignatureConfig *)config  DEPRECATED_MSG_ATTRIBUTE("Use CPDFSignatureWidgetAnnotation::signAppearanceConfig:");

@end
