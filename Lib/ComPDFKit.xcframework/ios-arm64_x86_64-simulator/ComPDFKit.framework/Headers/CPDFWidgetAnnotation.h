//
//  CPDFWidgetAnnotation.h
//  ComPDFKit
//
//  Copyright © 2014-2023 PDF Technologies, Inc. All Rights Reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE ComPDFKit LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <ComPDFKit/CPDFAnnotation.h>

/**
 * A CPDFWidgetAnnotation object is a collection of fields for gathering information interactively from the user.
 */
@interface CPDFWidgetAnnotation : CPDFAnnotation

/**
 * Method to get / set the border color used for the form field.
 */
@property (nonatomic,retain) CPDFKitPlatformColor *borderColor;

/**
 * Method to ge t/ set the background color used for the form field.
 */
@property (nonatomic,retain) CPDFKitPlatformColor *backgroundColor;

@property (nonatomic,assign) CGFloat backgroundOpacity;

/**
 * Method to get / set the font used for the form field.
 */
@property (nonatomic,retain) CPDFKitPlatformFont *font;

/**
 * Method to get / set the font color used for the form field.
 */
@property (nonatomic,retain) CPDFKitPlatformColor *fontColor;

/**
 * Internal name for the field.
 */
- (NSString *)fieldName;
- (void)setFieldName:(NSString *)name;

- (void)reset;

@end
