//
//  CPDFTextWidgetAnnotation.h
//  ComPDFKit
//
//  Copyright © 2014-2024 PDF Technologies, Inc. All Rights Reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE ComPDFKit LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <ComPDFKit/CPDFWidgetAnnotation.h>

/**
 * A CPDFTextWidgetAnnotation object allows you to manage the appearance and content of text fields.
 *
 * @discussion CPDFTextWidgetAnnotation inherits general annotation behavior from the CPDFWidgetAnnotation class.
 */
@interface CPDFTextWidgetAnnotation : CPDFWidgetAnnotation

/**
 * String value associated with text field.
 */
@property (nonatomic,retain) NSString *stringValue;

/**
 * Alignment of text. Supported: NSLeftTextAlignment, NSRightTextAlignment and NSCenterTextAlignment.
 */
@property (nonatomic,assign) NSTextAlignment alignment;

/**
 * Configuring multiline PDF text fields.
 */
@property (nonatomic,assign) BOOL isMultiline;

@property (nonatomic,assign) BOOL isDate;

@end
