//
//  CPDFSquareAnnotation.h
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

@class CPDFFont;
@class CPDFAreaMeasureInfo;

/**
 * A CPDFSquareAnnotation object displays a rectangle on a page.
 *
 * @discussion Square annotations are like circle annotations (instances of the CPDFCircleAnnotation class) apart from the shape.
 * The setBorderWidth: method of the CPDFAnnotation class determines the stroke thickness.
 * The setColor: method of the CPDFAnnotation class determines the stroke color.
 */
@interface CPDFSquareAnnotation : CPDFAnnotation

/**
 * Method to get / set the fill opacity used for drawing the annotation.
 */
@property (nonatomic,assign) CGFloat interiorOpacity;

/**
 * Method to get / set the fill color used for drawing the annotation.
 */
@property (nonatomic,retain) CPDFKitPlatformColor *interiorColor;

@end
