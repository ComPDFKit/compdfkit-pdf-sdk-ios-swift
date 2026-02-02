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

typedef NS_ENUM(NSInteger, CPDFStampDraggedType) {
    CPDFStampDraggedTypeNone = -1,
    CPDFStampDraggedTypeMinXMinY = 0,
    CPDFStampDraggedTypeMidXMinY = 1,
    CPDFStampDraggedTypeMaxXMinY = 2,
    CPDFStampDraggedTypeMaxXMidY = 3,
    CPDFStampDraggedTypeMaxXMaxY = 4,
    CPDFStampDraggedTypeMidXMaxY = 5,
    CPDFStampDraggedTypeMinXMaxY = 6,
    CPDFStampDraggedTypeMinXMidY = 7,
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
 * Gets the standard stamp type.
 *
 */
@property (nonatomic,assign,readonly) NSInteger standardType;

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

/**
 * Method to get / set the all rect vertex points after rotation.
 *
 * @discussion Vertex points of the current page.
 */
@property (nonatomic, strong) NSArray<NSValue *> *saveRectRotationPoints;

/**
 * Method to get / set the  rect befer rotation.based on the rect when the rotation angle is 0 degrees.
 *
 * @discussion rect of the current page.
 */
@property (nonatomic, assign) CGRect saveSourceRect;

/**
 * Sets the rotation angle for the annotation in degrees.
 *
 * @discussion Rotation on a annotation. Must be -180 ~ 180.
 */
@property (nonatomic,assign) NSInteger annotationRotation;

/**
 * Method to Quickly set the annotation rotation angle, and simultaneously update the saveRectRotationPoints and annotationRotation property.
 *
 * @discussion Rotation on a annotation. The annotationRotation based on when the rotation angle is 0 degrees. Must be -180 ~ 180.
 */
- (void)updateAnnotationRotation:(NSInteger)annotationRotation;

/**
 * Method to move stampAnnotation
 *
 * @discussion offset
 */
- (void)moveStampAnnotationWithActivePage:(CPDFPage *)newActivePage offset:(CPDFKitPlatformPoint)offset;

/**
 * Method to drag stampAnnotation
 *
 * @discussion draggedIndex
 */
- (void)dragStampAnnotationWithCurrentPagePoint:(CGPoint)currentPagePoint draggedIndex:(CPDFStampDraggedType)draggedIndex;

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
