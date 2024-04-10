//
//  CPDFWatermark.h
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

typedef NS_ENUM(NSInteger, CPDFWatermarkType) {
    CPDFWatermarkTypeText = 0,
    CPDFWatermarkTypeImage
};

typedef NS_ENUM(NSInteger, CPDFWatermarkVerticalPosition) {
    CPDFWatermarkVerticalPositionTop = 0,
    CPDFWatermarkVerticalPositionCenter,
    CPDFWatermarkVerticalPositionBottom
};

typedef NS_ENUM(NSInteger, CPDFWatermarkHorizontalPosition) {
    CPDFWatermarkHorizontalPositionLeft = 0,
    CPDFWatermarkHorizontalPositionCenter,
    CPDFWatermarkHorizontalPositionRight
};

@class CPDFDocument,CPDFFont;

/**
 * Add and delete image and text watermarks.
 */
@interface CPDFWatermark : NSObject

#pragma mark - Initializers

/**
 * Initializes the watermark.
 *
 * @param document The document with which the watermark is associated.
 * @param type The type index of the watermark.
 * @see CPDFWatermarkType
 */
- (instancetype)initWithDocument:(CPDFDocument *)document type:(CPDFWatermarkType)type;

#pragma mark - Accessors

/**
 * Returns the type for the watermark.
 *
 * @see CPDFWatermarkType
 */
@property (nonatomic,readonly) CPDFWatermarkType type;

/**
 * Method to get / set the text for the watermark (image watermark does not work).
 */
@property (nonatomic,copy) NSString *text;

/**
 * Method to set the text font name for the watermark (image watermark does not work).
 *
 * @discussion The text font for the watermark; may return NULL if the watermark was created with image.
 */
@property (nonatomic,retain) CPDFFont *cFont;

/**
 * Method to set the text font size for the watermark (image watermark does not work).
 *
 * @discussion The text font for the watermark; may return NULL if the watermark was created with image.
 */
@property (nonatomic,assign) CGFloat fontSize;

/**
 * Method to get / set the text font for the watermark (image watermark does not work).
 *
 * @discussion The text font for the watermark; may return NULL if the watermark was created with image.
 * Default Font : Helvetica 24
 */
@property (nonatomic,retain) CPDFKitPlatformFont *textFont DEPRECATED_MSG_ATTRIBUTE("use setCFont:fontSize:");

/**
 * Method to get / set the text color for the watermark (image watermark does not work).
 */
@property (nonatomic,retain) CPDFKitPlatformColor *textColor;

/**
 * Method to get / set the image for the watermark (text watermark does not work).
 */
@property (nonatomic,retain) CPDFKitPlatformImage *image;

/**
 * Method to get / set the scale factor for the watermark.
 *
 * @discussion Default is 1.0.
 */
@property (nonatomic,assign) CGFloat scale;

/**
 * Method to get / set the rotation for the watermark.
 *
 * @discussion Range : 0~360, Default is 0.0.
 */
@property (nonatomic,assign) CGFloat rotation;

/**
 * Method to get / set the opacity for the watermark.
 *
 * @discussion Range : 0~1, Default is 1.0.
 */
@property (nonatomic,assign) CGFloat opacity;

/**
 * Method to get / set the page range for the watermark.
 *
 * @discussion If not set, default to all pages.
 */
@property (nonatomic,assign) NSRange pageRange;

/**
 * Method to get / set the page range for the watermark by string.
 *
 * @discussion A page range string, Such as "0,3,5-7".
 */
@property (nonatomic,retain) NSString *pageString;

/**
 * Method to get / set the vertical position for the watermark.
 *
 * @discussion Default is CPDFWatermarkVerticalPositionCenter.
 * @see CPDFWatermarkVerticalPosition
 */
@property (nonatomic,assign) CPDFWatermarkVerticalPosition verticalPosition;

/**
 * Method to get / set the horizontal position for the watermark.
 *
 * @discussion Default is CPDFWatermarkHorizontalPositionCenter.
 * @see CPDFWatermarkHorizontalPosition
 */
@property (nonatomic,assign) CPDFWatermarkHorizontalPosition horizontalPosition;

/**
 * Method to get / set the horizontal translation for the watermark.
 *
 * @discussion The translation relative to the horizontal position.
 */
@property (nonatomic,assign) CGFloat tx;

/**
 * Method to get / set the vertical translation for the watermark.
 *
 * @discussion The translation relative to the vertical position.
 */
@property (nonatomic,assign) CGFloat ty;

/**
 * Method to get/set watermark to locate in front of the content.
 */
@property (nonatomic,assign) BOOL isFront;

/**
 * Method to get / set tiled watermark for the page(image watermark does not work).
 */
@property (nonatomic,assign) BOOL isTilePage;

/**
 * Method to get / set the vertical spacing for the tiled watermark.
 */
@property (nonatomic,assign) CGFloat verticalSpacing;

/**
 * Method to get / set the horizontal spacing for the tiled watermark.
 */
@property (nonatomic,assign) CGFloat horizontalSpacing;

@end

