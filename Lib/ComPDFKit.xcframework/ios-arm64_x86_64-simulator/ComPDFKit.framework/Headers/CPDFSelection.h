//
//  CPDFSelection.h
//  ComPDFKit
//
//  Copyright © 2014-2024 PDF Technologies, Inc. All Rights Reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE ComPDFKit LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <ComPDFKit/CPDFKitPlatform.h>

@class CPDFPage;

/**
 * A CPDFSelection object identifies a contiguous or noncontiguous selection of text in a PDF document.
 */
@interface CPDFSelection : NSObject

- (instancetype)initWithPage:(CPDFPage *)page rect:(CGRect)rect;

#pragma mark - Accessors

/**
 * Returns the page where the selection is located.
 */
@property (nonatomic,readonly) CPDFPage *page;

/**
 * Returns the bounds of the selection on the page.
 *
 * @discussion The selection rectangle is given in page space. Page space is a coordinate system with the origin at the lower-left corner of the current page.
 */
@property (nonatomic,readonly) CGRect bounds;

/**
 * Returns a range of contiguous text on the page.
 */
@property (nonatomic,readonly) NSRange range;

/**
 * Returns an array of selections, one for each line of text covered by the receiver.
 *
 * @discussion If you call this method on a CPDFSelection object that represents a paragraph, for example,
 * selectionsByLine returns an array that contains one CPDFSelection object for each line of text in the paragraph.
 */
@property (nonatomic,readonly) NSArray<CPDFSelection *> *selectionsByLine;

/**
 * Returns an NSString object representing the text contained in the selection (may contain linefeed characters).
 */
- (NSString *)string;

@end
