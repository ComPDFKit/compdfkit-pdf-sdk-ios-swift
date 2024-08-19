//
//  CPDFSelection+Protected.h
//  ComPDFKit
//
//  Copyright © 2014-2024 PDF Technologies, Inc. All Rights Reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE ComPDFKit LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <ComPDFKit/CPDFSelection.h>

typedef NS_ENUM(NSInteger, CPDFSelectionType) {
    CPDFSelectionTypeText = 0,
    CPDFSelectionTypeImage ,
};

@interface CPDFSelection (Protected)

- (NSArray<CPDFPage *> *)pages;

- (CPDFKitPlatformColor *)color;
- (void)setColor:(CPDFKitPlatformColor *)color;

- (NSAttributedString *)attributedString;

- (CGRect)boundsForPage:(CPDFPage *)page;

- (NSUInteger)numberOfTextRangesOnPage:(CPDFPage *)page;
- (NSRange)rangeAtIndex:(NSUInteger)index onPage:(CPDFPage *)page;

- (void)addSelection:(CPDFSelection *)selection;
- (void)addSelections:(NSArray<CPDFSelection *> *)selections;

- (void)extendSelectionAtEnd:(NSInteger)succeed;
- (void)extendSelectionAtStart:(NSInteger)precede;

- (CPDFSelectionType)selectionType;

- (void)setSelectionType:(CPDFSelectionType)selectionType;

@end
