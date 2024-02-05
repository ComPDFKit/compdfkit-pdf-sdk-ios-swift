//
//  CPDFAnnotationMarkup.h
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

typedef NS_ENUM(NSInteger, CPDFMarkupType) {
    CPDFMarkupTypeHighlight = 0,
    CPDFMarkupTypeStrikeOut = 1,
    CPDFMarkupTypeUnderline = 2,
    CPDFMarkupTypeSquiggly = 3
};

/**
 * A CPDFMarkupAnnotation object appears as highlighting, underlining, strikethrough, or a squiggly style applied to the text of a document.
 */
@interface CPDFMarkupAnnotation : CPDFAnnotation

/**
 * Initializes CPDFMarkupAnnotation object.
 *
 * @see CPDFMarkupType
 */
- (instancetype)initWithDocument:(CPDFDocument *)document markupType:(CPDFMarkupType)markupType;

/**
 * Method to get / set the array of quadrilateral points defining the bounds of the markup.
 *
 * @discussion Array of (n * 4) NSPoints defining n quadrilaterals in page space where n is the number of quad points.
 * The points for each quad are ordered in a 'Z' pattern. That is, the first point should represent the upper left point representing the start of the marked-up text,
 * the next point will be the upper right, the third point will represent the lower left of the text and the last point the lower right.
 * Page space is a coordinate system with the origin at the lower-left corner of the current page.
 */
@property (nonatomic,retain) NSArray *quadrilateralPoints;

/**
 * Gets the markup style.
 *
 * @see CPDFMarkupType
 */
- (CPDFMarkupType)markupType;

- (NSString *)markupText;
- (void)setMarkupText:(NSString *)text;

- (BOOL)popup;
- (void)createPopup;
- (void)removePopup;

@end
