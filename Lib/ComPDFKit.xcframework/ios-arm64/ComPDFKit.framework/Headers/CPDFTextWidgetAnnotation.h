//
//  CPDFTextWidgetAnnotation.h
//  ComPDFKit
//
//  Copyright © 2014-2026 PDF Technologies, Inc. All Rights Reserved.
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
@property (nonatomic,strong) NSString *stringValue;

/**
 * Maximum text length, counted in user-perceived characters (composed character sequences).
 * A value of 0 removes the limit. Negative values are ignored. Applies only to text fields.
 * Comb fields use this value as their cell count.
 *
 * Text longer than the limit is truncated: setting a longer stringValue keeps only the first
 * maxLength characters, and lowering maxLength below the length of the current value truncates
 * that value. A value already stored in a document is left as-is until it is changed.
 */
@property (nonatomic,assign) NSInteger maxLength;

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
