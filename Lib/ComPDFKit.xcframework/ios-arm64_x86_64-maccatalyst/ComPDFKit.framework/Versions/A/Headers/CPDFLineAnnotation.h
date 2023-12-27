//
//  CPDFLineAnnotation.h
//  ComPDFKit
//
//  Copyright © 2014-2023 PDF Technologies, Inc. All Rights Reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE ComPDFKit LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <ComPDFKit/CPDFAnnotation.h>

/**
 * The following constants specify the available line ending styles.
 */
typedef NS_ENUM(NSInteger, CPDFLineStyle) {
    /** No line ending. */
    CPDFLineStyleNone = 0,
    /** An open arrowhead line ending, composed from two short lines meeting in an acute angle at the line end. */
    CPDFLineStyleOpenArrow = 1,
    /** A closed arrowhead line ending, consisting of a triangle with the acute vertex at the line end and filled with the annotation’s interior color, if any. */
    CPDFLineStyleClosedArrow = 2,
    /** A square line ending filled with the annotation’s interior color, if any. */
    CPDFLineStyleSquare = 3,
    /** A circular line ending filled with the annotation’s interior color, if any. */
    CPDFLineStyleCircle = 4,
    /** A diamond-shaped line ending filled with the annotation’s interior color, if any. */
    CPDFLineStyleDiamond = 5
};

/**
 * A PDFAnnotationLine object displays a single line on a page.
 *
 * @discussion The setBorderWidth: method of the CPDFAnnotation class determines the stroke thickness.
 * The setColor: method of the CPDFAnnotation class determines the stroke color.
 */
@interface CPDFLineAnnotation : CPDFAnnotation

/**
 * Method to get / set the starting point for the line, in page space.
 *
 * @discussion Page space is a coordinate system with the origin at the lower-left corner of the current page.
 */
@property (nonatomic,assign) CGPoint startPoint;
/**
 * Method to get / set the ending point for the line in page space.
 *
 * @discussion Page space is a coordinate system with the origin at the lower-left corner of the current page.
 */
@property (nonatomic,assign) CGPoint endPoint;

/**
 * Method to get / set the line ending style for the starting point of the line.
 *
 * @see CPDFLineStyle
 */
@property (nonatomic,assign) CPDFLineStyle startLineStyle;
/**
 * Method to get / set the line ending style for the ending point of the line.
 *
 * @see CPDFLineStyle
 */
@property (nonatomic,assign) CPDFLineStyle endLineStyle;

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
@property (nonatomic,retain) CPDFKitPlatformColor *interiorColor;

@end
