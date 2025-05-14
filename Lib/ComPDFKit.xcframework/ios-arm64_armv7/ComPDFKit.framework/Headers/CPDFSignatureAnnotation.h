//
//  CPDFSignatureAnnotation.h
//  ComPDFKit
//
//  Copyright © 2014-2025 PDF Technologies, Inc. All Rights Reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE ComPDFKit LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <ComPDFKit/CPDFAnnotation.h>


typedef NS_ENUM(NSInteger, CPDFSignatureDraggedType) {
    CPDFSignatureDraggedTypeNone = -1,
    CPDFSignatureDraggedTypeMinXMinY = 0,
    CPDFSignatureDraggedTypeMidXMinY = 1,
    CPDFSignatureDraggedTypeMaxXMinY = 2,
    CPDFSignatureDraggedTypeMaxXMidY = 3,
    CPDFSignatureDraggedTypeMaxXMaxY = 4,
    CPDFSignatureDraggedTypeMidXMaxY = 5,
    CPDFSignatureDraggedTypeMinXMaxY = 6,
    CPDFSignatureDraggedTypeMinXMidY = 7,
};

@interface CPDFSignatureAnnotation : CPDFAnnotation

- (void)setImage:(CPDFKitPlatformImage *)image;

- (void)signature;

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
 * Method to move signatureAnnotation
 *
 * @discussion offset
 */
- (void)moveSignatureAnnotationWithActivePage:(CPDFPage *)newActivePage offset:(CPDFKitPlatformPoint)offset;

/**
 * Method to drag signatureAnnotation
 *
 * @discussion draggedIndex
 */
- (void)dragSignatureAnnotationWithCurrentPagePoint:(CGPoint)currentPagePoint draggedIndex:(CPDFSignatureDraggedType)draggedIndex;

@end
