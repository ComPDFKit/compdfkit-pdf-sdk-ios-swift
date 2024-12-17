//
//  CPDFSignatureAnnotation.h
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

@interface CPDFSignatureAnnotation : CPDFAnnotation

- (void)setImage:(CPDFKitPlatformImage *)image;

- (void)signature;

/**
 * Method to get / set the all rect vertex points after rotation.
 *
 * @discussion Vertex points of the current page.
 */
- (void)setSaveRectRotationPoints:(NSArray<NSValue *> *)saveRectRotationPoints;
- (NSArray<NSValue *> *)saveRectRotationPoints;

/**
 * Method to get / set the  rect befer rotation.
 *
 * @discussion rect of the current page.
 */
- (void)setSaveSourceRect:(CGRect)saveSourceRect;
- (CGRect)saveSourceRect;

/**
 * Sets the rotation angle for the annotation in degrees.
 *
 * @discussion Rotation on a annotation. Must be -180 ~ 180.
 */
@property (nonatomic,assign) NSInteger annotationRotation;

@end
