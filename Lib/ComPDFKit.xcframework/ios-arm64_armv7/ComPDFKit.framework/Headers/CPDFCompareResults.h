//
//  CPDFCompareResults.h
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

typedef NS_ENUM(NSInteger, CPDFCompareResultType) {
      CPDFCompareResultTypeNone = 0,
      CPDFCompareResultTypeDelete,
      CPDFCompareResultTypeInsert,
      CPDFCompareResultTypeReplace,
      CPDFCompareResultTypeChange,
};

@interface CPDFCompareResult : NSObject

/**
* Gets the type of a result of comparing content.
*/
- (CPDFCompareResultType)type;

/**
 * Gets a page index that compares the contents of the old document.
 */
- (NSInteger)oldPageIndex;

/**
 * Gets a page index that compares the contents of the new document.
 */
- (NSInteger)newPageIndex;

/**
 * Gets the page range of the old document content comparison results.
 */
- (CGRect)oldBounds;

/**
 * Gets the page range of the new document content comparison results.
 */
- (CGRect)newBounds;

@end

@interface CPDFCompareResults : NSObject

/**
 * Gets an array of results for all text compared in the document version.
 */
- (NSArray <CPDFCompareResult *>*)textResults;

/**
 * Gets an array of results for all image compared in the document version.
 */
- (NSArray <CPDFCompareResult *>*)imageResults;

/**
* Gets the count of removal.
*/
- (NSInteger)deleteCount;

/**
* Gets the count of insert.
*/
- (NSInteger)insertCount;

/**
* Gets the count of replacement.
*/
- (NSInteger)replaceCount;

@end
