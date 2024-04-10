//
//  CPDFSignatureWidgetAnnotation.m
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
@class CPDFPerimeterMeasureInfo;

NS_ASSUME_NONNULL_BEGIN

/**
 * A PDFAnnotationLine object displays a polyline on a page.
 *
 * @discussion The setBorderWidth: method of the CPDFAnnotation class determines the stroke thickness.
 * The setColor: method of the CPDFAnnotation class determines the stroke color.
 */
@interface CPDFPolylineAnnotation : CPDFAnnotation

/**
 * Method to get / set the all points of the line segment.
 *
 * @discussion Page space is a coordinate system with the origin at the lower-left corner of the current page.
 */
- (void)setSavePoints:(NSArray<NSValue *> *)savePoints;
- (NSArray<NSValue *> *)savePoints;

#pragma mark -  Measure
/**
* Method to determine whether an annotation has measurement properties.
 */
@property (nonatomic,assign,readonly) BOOL isMeasure;
/**
 * Method to set the font name used for the annotation’s measure text field.
 */
@property (nonatomic,retain) CPDFFont *cFont;

/**
 * Method to get the font size used for the annotation’s measure text field.
 */
@property (nonatomic,assign) CGFloat fontSize;

/**
 * Method to get / set the font color used in the measure text field of the annotation.
 */
@property (nonatomic,retain) CPDFKitPlatformColor *fontColor;

/**
 * Method to get the measure info of the measure annotation after added to page.
 *
 * @discussion The measurement properties of a annotation cannot be cleared by setting the measurement properties of the annotation to empty
 * Set MeasureInfo: This information will not be effective until it is added to the page
 */
@property (nonatomic,retain) CPDFPerimeterMeasureInfo * _Nullable measureInfo;

@end

NS_ASSUME_NONNULL_END
