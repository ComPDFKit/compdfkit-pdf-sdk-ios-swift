//
//  CPDFWidgetAnnotation.h
//  ComPDFKit
//
//  Copyright © 2014-2025 PDF Technologies, Inc. All Rights Reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE ComPDFKit LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <ComPDFKit/CPDFAnnotation.h>

@class CPDFFont;

/**
 * A CPDFWidgetAnnotation object is a collection of fields for gathering information interactively from the user.
 */
@interface CPDFWidgetAnnotation : CPDFAnnotation

/**
 * Method to get / set the border color used for the form field.
 */
@property (nonatomic,strong) CPDFKitPlatformColor *borderColor;

/**
 * Method to ge t/ set the background color used for the form field.
 */
@property (nonatomic,strong) CPDFKitPlatformColor *backgroundColor;

/**
 * remove backgroundColor(Set it to transparent, or set SetBackgroundColor: to nil)
 */

- (BOOL)removeBackgroundColor;

@property (nonatomic,assign) CGFloat backgroundOpacity;

/**
 * Method to set the font name used for the annotation’s form field.
 */
@property (nonatomic,strong) CPDFFont *cFont;

/**
 * Method to get the font size used for the annotation’s form field.
 */
@property (nonatomic,assign) CGFloat fontSize;

/**
 * Method to get / set the font used for the form field.
 */
@property (nonatomic,strong) CPDFKitPlatformFont *font DEPRECATED_MSG_ATTRIBUTE("use setCFont:fontSize:");


/**
 * Method to get / set the font color used for the form field.
 */
@property (nonatomic,strong) CPDFKitPlatformColor *fontColor;

/**
 * Returns the type of the form. Examples include: "ComboBox", "TextField", etc.
 */
@property (nonatomic,readonly) NSString *widgetType;

/**
 * Internal name for the field.
 */
- (NSString *)fieldName;
- (void)setFieldName:(NSString *)name;

- (void)reset;

@end
