//
//  CPDFHeaderFooter.h
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

/**
 * Adds and removes the header & footer.
 */
@interface CPDFHeaderFooter : NSObject

#pragma mark - Accessors

/**
 * Method to get / set the page range of the header & footer by string, such as "0,3,5-7".
 */
@property (nonatomic,retain) NSString *pageString;

/**
 * Method to get / set the margins of the header & footer.
 */
@property (nonatomic,assign) CPDFKitPlatformEdgeInsets margin;

/**
 * Gets the text of the header & footer at the specified index.
 */
- (NSString *)textAtIndex:(NSUInteger)index;
/**
 * Sets the text of the header & footer at the specified index.
 */
- (void)setText:(NSString *)text atIndex:(NSUInteger)index;

/**
 * Gets the font color of the header & footer at the specified index.
 */
- (CPDFKitPlatformColor *)textColorAtIndex:(NSUInteger)index;
/**
 * Sets the font color of the header & footer at the specified index.
 */
- (void)setTextColor:(CPDFKitPlatformColor *)color atIndex:(NSUInteger)index;

/**
 * Gets the font size of the header & footer at the specified index.
 */
- (CGFloat)fontSizeAtIndex:(NSUInteger)index;
/**
 * Sets the font size of the header & footer at the specified index.
 */
- (void)setFontSize:(CGFloat)fontSize atIndex:(NSUInteger)index;

/**
 * Gets the font name of the header & footer at the specified index.
 */
- (NSString *)fontNameAtIndex:(NSUInteger)index;
/**
 * Sets the font name of the header & footer at the specified index.
 */
- (void)setFontName:(NSString *)fontName atIndex:(NSUInteger)index;

/**
 * Updates the header & footer.
 */
- (void)update;
/**
 * Removes the header & footer.
 */
- (void)clear;

@end
