//
//  CPDFBackground.h
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

typedef NS_ENUM(NSInteger, CPDFBackgroundType) {
    CPDFBackgroundTypeColor = 0,
    CPDFBackgroundTypeImage
};

/**
 * Adds and removes the background.
 */
@interface CPDFBackground : NSObject

#pragma mark - Accessors

/**
 * Method to get / set the type of the background.
 *
 * @see CPDFBackgroundType
 */
@property (nonatomic,assign) CPDFBackgroundType type;

/**
 * Method to get / set the color of the background.
 */
@property (nonatomic,retain) CPDFKitPlatformColor *color;

/**
 * Method to get / set the scale of the background.
 */
@property (nonatomic,assign) CGFloat scale;

/**
 * Method to get / set the rotation angle of the background.
 */
@property (nonatomic,assign) CGFloat rotation;

/**
 * Method to get / set the opacity of the background.
 */
@property (nonatomic,assign) CGFloat opacity;

/**
 * Method to get / set the page range of the background by string, such as "0,3,5-7".
 */
@property (nonatomic,retain) NSString *pageString;

/**
 * Method to get / set the vertical alignment of the background.
 */
@property (nonatomic,assign) NSUInteger verticalAlignment;

/**
 * Method to get / set the horizontal offset of the background.
 */
@property (nonatomic,assign) NSUInteger horizontalAlignment;

/**
 * Method to get / set the horizontal offset of the background.
 */
@property (nonatomic,assign) CGFloat xOffset;

/**
 * Method to get / set the vertical offset of the background.
 */
@property (nonatomic,assign) CGFloat yOffset;

/**
 * Method to get / set whether to support the background to be displayed.
 */
@property (nonatomic,assign) BOOL isAllowsView;

/**
 * Method to get / set whether to support the background to be printed.
 */
@property (nonatomic,assign) BOOL isAllowsPrint;

/**
 * Sets the image of the background.
 */
- (void)setImage:(CPDFKitPlatformImage *)image;

/**
 * Updates the background.
 */
- (void)update;
/**
 * Removes the background.
 */
- (void)clear;

@end
