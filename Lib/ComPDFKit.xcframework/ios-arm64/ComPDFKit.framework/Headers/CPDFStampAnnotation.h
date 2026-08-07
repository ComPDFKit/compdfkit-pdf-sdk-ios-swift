//
//  CPDFStampAnnotation.h
//  ComPDFKit
//
//  Copyright © 2014-2026 PDF Technologies, Inc. All Rights Reserved.
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

#pragma mark - Initializers

/**
 * Creates a stamp annotation with an image.
 *
 * @param page     The page on which the annotation will reside.
 * @param document The document that owns the page.
 * @param image    The image to use as the stamp content.
 */
- (nullable instancetype)initWithPage:(CPDFPage *)page document:(CPDFDocument *)document image:(CPDFKitPlatformImage *)image;

/**
 * Creates a stamp annotation with a standard (predefined) stamp type.
 *
 * @param page     The page on which the annotation will reside.
 * @param document The document that owns the page.
 * @param type     An integer value identifying the standard stamp (1–21).
 */
- (nullable instancetype)initWithPage:(CPDFPage *)page document:(CPDFDocument *)document standardType:(NSInteger)type;

/**
 * Creates a stamp annotation with custom text.
 *
 * @param page       The page on which the annotation will reside.
 * @param document   The document that owns the page.
 * @param text       The primary text content.
 * @param detailText The secondary detail text.
 * @param style      The color style of the text stamp.
 * @param shape      The shape of the text stamp border.
 */
- (nullable instancetype)initWithPage:(CPDFPage *)page document:(CPDFDocument *)document text:(NSString *)text detailText:(NSString *)detailText style:(CPDFStampStyle)style shape:(CPDFStampShape)shape;

/**
 * Creates a stamp annotation with a digital stamp.
 *
 * @param page       The page on which the annotation will reside.
 * @param document   The document that owns the page.
 * @param text       The primary text content.
 * @param detailText The secondary detail text.
 * @param dateText   The date string displayed on the stamp.
 * @param color      The color used to render the digital stamp.
 */
- (nullable instancetype)initWithPage:(CPDFPage *)page document:(CPDFDocument *)document text:(NSString *)text detailText:(NSString *)detailText dateText:(NSString *)dateText color:(CPDFKitPlatformColor *)color;

#pragma mark - Getting Stamp Properties

/**
 * Gets the standard stamp type.
 *
 */
@property (nonatomic,assign,readonly) NSInteger standardType;

/**
 * Returns the type of this stamp annotation.
 *
 * @return A @c CPDFStampType value indicating whether this is a standard, text, image, or digital stamp.
 * Gets the stamp type.
 *
 * @see CPDFStampType
 */
- (CPDFStampType)stampType;

/**
 * Returns the rendered image of the stamp annotation's appearance stream.
 *
 * @discussion If the appearance has not been generated yet, this method triggers rendering at the current screen scale.
 *
 * @return The stamp appearance as a platform image, or @c nil if rendering fails.
 */
- (CPDFKitPlatformImage *)stampImage;

/**
 * Gets the main text of a text stamp annotation.
 *
 * @discussion Only applies when stampType is CPDFStampTypeText.
 */
@property (nonatomic, copy, readonly, nullable) NSString *text;

/**
 * Gets the detail text of a text stamp annotation.
 *
 * @discussion Only applies when stampType is CPDFStampTypeText.
 */
@property (nonatomic, copy, readonly, nullable) NSString *detailText;

/**
 * Gets the style of a text stamp annotation.
 *
 * @discussion Only applies when stampType is CPDFStampTypeText.
 */
@property (nonatomic, assign, readonly) CPDFStampStyle style;

/**
 * Gets the shape of a text stamp annotation.
 *
 * @discussion Only applies when stampType is CPDFStampTypeText.
 */
@property (nonatomic, assign, readonly) CPDFStampShape shape;

@end


@interface CPDFStampAnnotation (Deprecated)

/**
 * Deprecated. Use updateAnnotationRotation: to rotate stamp annotations.
 *
 * @discussion Swift: use updateRotation(...).
 */
- (void)setAnnotationRotation:(NSInteger)rotation DEPRECATED_MSG_ATTRIBUTE("Use updateAnnotationRotation: instead.");

/**
 * Deprecated. Do not set the saved source rect directly.
 *
 * @discussion Use updateAnnotationRotation: for rotation, moveAnnotationWithActivePage:offset: for moving,
 * and dragAnnotationWithCurrentPagePoint:draggedIndex: for resizing.
 * Swift: use updateRotation(...), move(withActivePage:offset:), and drag(withCurrentPagePoint:draggedIndex:).
 */
- (void)setSaveSourceRect:(CGRect)saveSourceRect DEPRECATED_MSG_ATTRIBUTE("Do not set saveSourceRect directly. Use updateAnnotationRotation:, moveAnnotationWithActivePage:offset:, or dragAnnotationWithCurrentPagePoint:draggedIndex: instead.");

/**
 * Deprecated. Do not set the saved rotation points directly.
 *
 * @discussion Use updateAnnotationRotation: for rotation, moveAnnotationWithActivePage:offset: for moving,
 * and dragAnnotationWithCurrentPagePoint:draggedIndex: for resizing.
 * Swift: use updateRotation(...), move(withActivePage:offset:), and drag(withCurrentPagePoint:draggedIndex:).
 */
- (void)setSaveRectRotationPoints:(NSArray<NSValue *> *) saveRectRotationPoints DEPRECATED_MSG_ATTRIBUTE("Do not set saveRectRotationPoints directly. Use updateAnnotationRotation:, moveAnnotationWithActivePage:offset:, or dragAnnotationWithCurrentPagePoint:draggedIndex: instead.");

@end
