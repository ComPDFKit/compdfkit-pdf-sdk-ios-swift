//
//  CPDFView+Editing.h
//  ComPDFKit
//
//  Copyright © 2014-2024 PDF Technologies, Inc. All Rights Reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE ComPDFKit LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <ComPDFKit/ComPDFKit.h>

#pragma mark - CPDFView+Editing

@interface CPDFView (Editing)

- (BOOL)isEditable;

- (void)discardEditingForPage:(CPDFPage *)page;

- (void)updeteEditTypingAttributes:(NSMutableDictionary <NSAttributedStringKey, id>*)editTypingAttributes;

- (void)updateEditingArea:(CPDFEditArea *)editingArea;

- (void)moveEditArea:(CPDFEditArea *)editArea point:(CGPoint)point;

- (void)removeWithEditArea:(CPDFEditArea *)editArea;

#pragma mark - Edit Text

- (NSString *)editingSelectionString;

- (BOOL)createEmptyStringBounds:(CGRect)rect page:(CPDFPage *)page DEPRECATED_MSG_ATTRIBUTE("use createStringBounds:withAttributes:page:");

- (BOOL)isSelecteditAreaNotEdit;

- (BOOL)isSelectEditCharRange;

- (void)cutEditAreaAction;

- (void)pasteEditAreaMatchStyleActionWithPoint:(CGPoint)point;

- (void)pasteEditAreaActionWithPoint:(CGPoint)point;

- (void)copyEditAreaAction;

- (void)selectAllActionWithEditArea:(CPDFEditArea *)editArea;

- (BOOL)isSupportPast;

- (BOOL)isSupportPastMatchStyle;

#pragma mark - Edit Image

- (void)scaleWithEditImageArea:(CPDFEditImageArea *)editArea scaleX:(CGFloat)scaleX scaleY:(CGFloat)scaleY;

- (BOOL)saveImageToPhotoWithEditImageArea:(CPDFEditImageArea *)editArea;

@end
