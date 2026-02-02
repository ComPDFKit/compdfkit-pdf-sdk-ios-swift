//
//  CPDFCompareContent.h
//  ComPDFKit
//
//  Copyright © 2014-2026 PDF Technologies, Inc. All Rights Reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE ComPDFKit LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <ComPDFKit/CPDFKitPlatform.h>
#import "CPDFCompareResults.h"

typedef NS_ENUM(NSInteger, CPDFCompareType) {
    CPDFCompareTypeText = 0,
    CPDFCompareTypeImage,
    CPDFCompareTypeAll
};

@class CPDFDocument;

@interface CPDFCompareContent : NSObject

/**
 * Initialize it with the given two versions of a document.
 * By default, it will generate a comparison document according to the order of pages, starting from the first page of both versions of the document.
 *
 * @param oldDocument The old version of a document
 * @param newDocument The new version of a document.
 */
- (instancetype)initWithOldDocument:(CPDFDocument *)oldDocument
                        newDocument:(CPDFDocument *)newDocument;

/**
 * Specifies pages and types to compare.
*/
- (CPDFCompareResults *)compareOldPageIndex:(NSInteger)oldPageIndex
                               newPageIndex:(NSInteger)newPageIndex
                                       type:(CPDFCompareType)type
                            isDrawHighlight:(BOOL)isDrawHighlight;

/**
 * Sets to replace the highlight color.
 */
- (void)setReplaceColor:(CPDFKitPlatformColor *)color;

/**
 * Sets the opacity of the replace highlighted color
 */
- (void)setReplaceOpacity:(CGFloat)opacity;

/**
* Sets to insert the highlight color.
*/
- (void)setInsertColor:(CPDFKitPlatformColor *)color;

/**
 * Sets the opacity of the insert highlighted color
 */
- (void)setInsertOpacity:(CGFloat)opacity;

/**
 * Sets to remove the highlight color.
 */
- (void)setDeleteColor:(CPDFKitPlatformColor *)color;

/**
 * Sets the opacity of the remove highlighted color
 */
- (void)setDeleteOpacity:(CGFloat)opacity;

/**
 * Saves the comparison document.
 */
- (BOOL)saveAsComparisonDocumentWithFilePath:(NSString *)filePath;

@end
