//
//  CPDFDestination.h
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

/**
 * A CPDFDestination object describes a point on a PDF page.
 *
 * @discussion In typical usage, you do not initialize CPDFDestination objects but rather get them as either attributes of CPDFLinkAnnotation or CPDFOutline objects,
 * or in response to the CPDFView method currentDestination.
 */
@interface CPDFDestination : NSObject

#pragma mark - Initializers

/**
 * Initializes the destination.
 *
 * @discussion Specify point in page space. Typically, there’s no need to initialize destinations. Instead, you get them from CPDFLinkAnnotation, CPDFOutline, or CPDFView objects.
 * @param document The document with which the destination is associated.
 * @param pageIndex The page index of the destination.
 */
- (instancetype)initWithDocument:(CPDFDocument *)document
                       pageIndex:(NSInteger)pageIndex;

/**
 * Initializes the destination.
 *
 * @discussion Specify point in page space. Typically, there’s no need to initialize destinations. Instead, you get them from CPDFLinkAnnotation, CPDFOutline, or CPDFView objects.
 * Page space is a coordinate system with the origin at the lower-left corner of the current page.
 * @param document The document with which the destination is associated.
 * @param pageIndex The page index of the destination.
 * @param point The point of the destination, in page space.
 * @param zoom The zoom of the destination.
 */
- (instancetype)initWithDocument:(CPDFDocument *)document
                       pageIndex:(NSInteger)pageIndex
                         atPoint:(CGPoint)point
                            zoom:(CGFloat)zoom;

#pragma mark - Accessors

/**
 * Returns the document with which the destination is associated.
 */
@property (nonatomic,readonly) CPDFDocument *document;

/**
 * Returns the page index that the destination refers to.
 */
@property (nonatomic,readonly) NSInteger pageIndex;

/**
 * Returns the point, in page space, that the destination refers to.
 *
 * @discussion Page space is a coordinate system with the origin at the lower-left corner of the current page.
 */
@property (nonatomic,readonly) CGPoint point;

/**
 * Returns the scale factor the PDF viewer should assume for this destination.
 */
@property (nonatomic,readonly) CGFloat zoom;

@end
