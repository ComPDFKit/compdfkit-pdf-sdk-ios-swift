//
//  CPDFBookmark.h
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

@class CPDFDocument;

@interface CPDFBookmark : NSObject

#pragma mark - Accessors

/**
 * Returns the document with which the bookmark is associated.
 */
@property (nonatomic,readonly) CPDFDocument *document;

/**
 * Returns the page index that the bookmark refers to.
 */
@property (nonatomic,readonly) NSInteger pageIndex;

/**
 * Method to get / set the label for the bookmark.
 */
@property (nonatomic,retain) NSString *label;

/**
 * Method to get / set the date for the bookmark.
 */
@property (nonatomic,retain) NSDate *date;

@end
