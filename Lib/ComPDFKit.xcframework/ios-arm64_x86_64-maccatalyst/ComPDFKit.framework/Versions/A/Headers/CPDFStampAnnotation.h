//
//  CPDFStampAnnotation.h
//  ComPDFKit
//
//  Copyright © 2014-2024 PDF Technologies, Inc. All Rights Reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE ComPDFKit LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <ComPDFKit/CPDFAnnotation.h>

typedef NS_ENUM(NSInteger, CPDFStampType) {
    CPDFStampTypeStandard = 0,
    CPDFStampTypeText = 1,
    CPDFStampTypeImage = 2,
    CPDFStampTypeDigital = 3
};

typedef NS_ENUM(NSInteger, CPDFStampStyle) {
    CPDFStampStyleWhite = 0,
    CPDFStampStyleRed = 1,
    CPDFStampStyleGreen = 2,
    CPDFStampStyleBlue = 3
};

typedef NS_ENUM(NSInteger, CPDFStampShape) {
    CPDFStampShapeRectangle = 0,
    CPDFStampShapeArrowLeft = 1,
    CPDFStampShapeArrowRight = 2,
    CPDFStampShapeNone = 3,
};

/**
 * A CPDFStampAnnotation object allows you to display a word or phrase in a PDF page.
 *
 * @discussion A CPDFStampAnnotation object should have an appearance stream associated with it; otherwise, nothing useful is rendered.
 */
@interface CPDFStampAnnotation : CPDFAnnotation

/**
 * Initializes CPDFStampAnnotation object with image.
 */
- (instancetype)initWithDocument:(CPDFDocument *)document image:(CPDFKitPlatformImage *)image;

/**
 * Initializes CPDFStampAnnotation object with standard type.
 */
- (instancetype)initWithDocument:(CPDFDocument *)document type:(NSInteger)type;

/**
 * Initializes CPDFStampAnnotation object with text.
 *
 * @see CPDFStampStyle
 * @see CPDFStampShape
 */
- (instancetype)initWithDocument:(CPDFDocument *)document text:(NSString *)text detailText:(NSString *)detailText style:(CPDFStampStyle)style shape:(CPDFStampShape)shape;

/**
 * Initializes CPDFStampAnnotation object with digital stamp type.
 */
- (instancetype)initWithDocument:(CPDFDocument *)document text:(NSString *)text detailText:(NSString *)detailText dateText:(NSString *)dateText color:(CPDFKitPlatformColor *)color;

/**
 * Gets the stamp type.
 *
 * @see CPDFStampType
 */
- (CPDFStampType)stampType;

/**
 * Gets image for the appearance stream of the stamp annotation.
 */
- (CPDFKitPlatformImage *)stampImage;

@end
