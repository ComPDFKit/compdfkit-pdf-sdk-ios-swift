//
//  CPDFPage+Protected.h
//  ComPDFKit
//
//  Copyright © 2014-2026 PDF Technologies, Inc. All Rights Reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE ComPDFKit LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <ComPDFKit/CPDFPage.h>

@interface CPDFPage (Protected)

- (NSUInteger)pageIndex;

- (NSInteger)getHierarchyIndexWithAnnotation:(CPDFAnnotation *)annotation;

- (BOOL)moveHierarchyWithAnnotation:(CPDFAnnotation *)annotation atIndex:(NSInteger)index;

- (BOOL)addStringBounds:(CGRect)rect withString:(NSString *)string withAttributes:(NSDictionary<NSAttributedStringKey, id> *)attributes DEPRECATED_MSG_ATTRIBUTE("The api is currently in beta and Untested");

- (BOOL)isImagePage;

#pragma mark - Rendering

- (void)transformContext:(CGContextRef)context forBox:(CPDFDisplayBox)box;

- (void)drawWithBox:(CPDFDisplayBox)box toContext:(CGContextRef)context;

- (void)drawEditWithBox:(CPDFDisplayBox)box toContext:(CGContextRef)context;

#pragma mark - Selections

// Given a point in page-space, returns a selection representing a whole word at that point. May return NULL if no
// character (and by extension no word) under point. If data dectors are enabled (-[PDFView enableDataDetectors]),
// this return the smart-selection for the content at the given point.
- (CPDFSelection *)selectionForWordAtPoint:(CGPoint)point;

// Given a point in page-space, returns a selection representing a whole line at that point. May return NULL if no
// character (and by extension no line) under point.
- (CPDFSelection *)selectionForLineAtPoint:(CGPoint)point;

// Returns a selection representing text between startPt and endPt. Points are sorted first top to bottom, left to right.
- (CPDFSelection *)selectionFromPoint:(CGPoint)startPoint toPoint:(CGPoint)endPoint;

// Gets the unique identifier of the page, if not returned -1
- (NSInteger)getPageObjNum;

#pragma mark - Redact

- (BOOL)erasureRedactFromRect:(CGRect)rect DEPRECATED_MSG_ATTRIBUTE("The api is currently in beta and Untested");

@end
