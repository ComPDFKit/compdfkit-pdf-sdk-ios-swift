//
//  CPDFSignatureWidgetAnnotation.m
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

@class CPDFFont;
@class CPDFAreaMeasureInfo;
@class CPDFBorderEffect;

NS_ASSUME_NONNULL_BEGIN

/**
 * A PDFAnnotationLine object displays a polygon on a page.
 *
 * @discussion The setBorderWidth: method of the CPDFAnnotation class determines the stroke thickness.
 * The setColor: method of the CPDFAnnotation class determines the stroke color.
 */
@interface CPDFPolygonAnnotation : CPDFAnnotation

/**
 * Method to get / set the all points of the line segment.
 *
 * @discussion Page space is a coordinate system with the origin at the lower-left corner of the current page.
 */
@property (nonatomic,assign) NSArray<NSValue *> *savePoints;
/**
 * Method to get / set the opacity used to fill the ornament at the ends of the line.
 *
 * @discussion The ornament at the end of a line is optional (for more information, see the Adobe PDF Specification 1.4).
 */
@property (nonatomic,assign) CGFloat interiorOpacity;
/**
 * Method to get / set the color used to fill the ornament at the ends of the line.
 *
 * @discussion The ornament at the end of a line is optional (for more information, see the Adobe PDF Specification 1.4).
 */
@property (nonatomic,strong) CPDFKitPlatformColor *interiorColor;

/**
 * remove interior Color(Set it to transparent, or set SetInteriorColor: to nil)
 */
- (BOOL)removeInteriorColor;

#pragma mark -  Measure
/**
* Method to determine whether an annotation has measurement properties.
 */
@property (nonatomic,assign,readonly) BOOL isMeasure;
/**
 * Method to set the font name used for the annotation’s measure text field.
 */
@property (nonatomic,strong) CPDFFont *cFont;

/**
 * Method to get the font size used for the annotation’s measure text field.
 */
@property (nonatomic,assign) CGFloat fontSize;

/**
 * Method to get / set the font color used in th measure text field of the annotation.
 */
@property (nonatomic,strong) CPDFKitPlatformColor *fontColor;

/**
 * Method to get the measure info of the annotation after added to page.
 *
 * @discussion The measurement properties of a annotation cannot be cleared by setting the measurement properties of the annotation to empty
 * Set MeasureInfo: This information will not be effective until it is added to the page
 */
@property (nonatomic,strong) CPDFAreaMeasureInfo *_Nullable measureInfo;

#pragma mark -  Border Effect

/**
 * Method to get / set the  used for border Effect drawing the annotation.
 * Cloud border effect for setting annotation
 */
@property (nonatomic,strong) CPDFBorderEffect * _Nullable borderEffect;

/**
 * Method to get / set the  used for border Effect drawing the annotation.
 * If true, the parent view handles the vertices enclosed event; if false, the polygon savePoints Spot Encirclement Area itself handles the event
 * Note: This property is for configuration purposes and will not affect the internal implementation of the SDK.
 */
@property (nonatomic,readwrite) BOOL polygonEncloseHandler;

@end

NS_ASSUME_NONNULL_END
