//
//  CPDFCircleAnnotation.h
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

@class CPDFBorderEffect;

/**
 * A CPDFCircleAnnotation object displays an ellipse on a page.
 *
 * @discussion Circle annotations are like square annotations (instances of the CPDFSquareAnnotation class) apart from the shape.
 * The setBorderWidth: method of the CPDFAnnotation class determines the stroke thickness.
 * The setColor: method of the CPDFAnnotation class determines the stroke color.
 */
@interface CPDFCircleAnnotation : CPDFAnnotation

/**
 * Method to get / set the fill opacity used for drawing the annotation.
 */
@property (nonatomic,assign) CGFloat interiorOpacity;

/**
 * Method to get / set the fill color used for drawing the annotation.
 */
@property (nonatomic,strong) CPDFKitPlatformColor *interiorColor;

/**
 * remove interior Color(Set it to transparent, or set SetInteriorColor: to nil)
 */
- (BOOL)removeInteriorColor;

#pragma mark -  Border Effect

/**
 * Method to get / set the  used for border Effect drawing the annotation.
 * Cloud border effect for setting annotation
 */
@property (nonatomic,strong) CPDFBorderEffect * _Nullable borderEffect;

@end
