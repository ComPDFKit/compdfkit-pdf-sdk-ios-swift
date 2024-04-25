//
//  CPDFFreeTextAnnotation.h
//  ComPDFKit
//
//  Copyright © 2014-2024 PDF Technologies, Inc. All Rights Reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE ComPDFKit LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <ComPDFKit/CPDFAnnotation.h>

@class CPDFFont;

/**
 * A CPDFFreeTextAnnotation object displays text on a page.
 *
 * @discussion The CPDFAnnotation class’s contents and setContents: methods let you get and set the textual content for a CPDFFreeTextAnnotation object.
 */
@interface CPDFFreeTextAnnotation : CPDFAnnotation

/**
 * Method to get the font used for the annotation’s text field.
 */
@property (nonatomic,retain) CPDFKitPlatformFont *font DEPRECATED_MSG_ATTRIBUTE("use setCFont:fontSize: and cFontSize");

/**
 * Method to set the font name used for the annotation’s text field.
 */
@property (nonatomic,retain) CPDFFont *cFont;

/**
 * Method to get the font size used for the annotation’s text field.
 */
@property (nonatomic,assign) CGFloat fontSize;

/**
 * Method to get / set the font color used in the text field of the annotation.
 */
@property (nonatomic,retain) CPDFKitPlatformColor *fontColor;

/**
 * Method to get / set the horizontal alignment of text within the bounds of the annotation.
 *
 * @discussion Supported values are NSLeftTextAlignment, NSRightTextAlignment, and NSCenterTextAlignment.
 */
@property (nonatomic,assign) NSTextAlignment alignment;

/**
 * Method to get / set the border color used for the form field.
 */
@property (nonatomic,retain) CPDFKitPlatformColor *borderColor;

@end
