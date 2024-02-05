//
//  CPDFButtonWidgetAnnotation.h
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

typedef NS_ENUM(NSInteger, CPDFWidgetControlType) {
    CPDFWidgetUnknownControl = -1,
    CPDFWidgetPushButtonControl = 0,
    CPDFWidgetRadioButtonControl = 1,
    CPDFWidgetCheckBoxControl = 2
};

typedef NS_ENUM(NSInteger, CPDFWidgetButtonStyle) {
    CPDFWidgetButtonStyleNone = -1,
    CPDFWidgetButtonStyleCheck = 0,
    CPDFWidgetButtonStyleCircle,
    CPDFWidgetButtonStyleCross,
    CPDFWidgetButtonStyleDiamond,
    CPDFWidgetButtonStyleSquare,
    CPDFWidgetButtonStyleStar
};

@class CPDFAction;

/**
 * A CPDFButtonWidgetAnnotation object provides user interactivity on a page of a PDF document. There are three types of buttons available: push button, radio button, and checkbox.
 *
 * @discussion CPDFButtonWidgetAnnotation inherits general annotation behavior from the CPDFWidgetAnnotation class.
 */
@interface CPDFButtonWidgetAnnotation : CPDFWidgetAnnotation

/**
 * Initializes CPDFButtonWidgetAnnotation object.
 *
 * @see CPDFWidgetControlType
 */
- (instancetype)initWithDocument:(CPDFDocument *)document controlType:(CPDFWidgetControlType)controlType;

/**
 * Returns the type of the control.
 *
 * @see CPDFWidgetControlType
 */
- (CPDFWidgetControlType)controlType;

/**
 * Returns the state of the control.
 *
 * @discussion Applies to CPDFWidgetRadioButtonControl or CPDFWidgetCheckBoxControl only.
 */
- (NSInteger)state;
/**
 * Sets the state of the control.
 *
 * @discussion Applies to CPDFWidgetRadioButtonControl or CPDFWidgetCheckBoxControl only.
 */
- (void)setState:(NSInteger)value;

/**
 * Returns the text of the label on a push button control.
 *
 * @discussion This method applies only to the label drawn on a control of type CPDFWidgetPushButtonControl.
 */
- (NSString *)caption;
/**
 * Sets the text of the label on a push button control.
 *
 * @discussion This method applies only to the label drawn on a control of type CPDFWidgetPushButtonControl.
 */
- (void)setCaption:(NSString *)name;

- (CPDFAction *)action;
- (void)setAction:(CPDFAction *)action;

- (BOOL)isTick;
- (void)setIsTick:(NSInteger)isTick;

/**
 *Get the button selected style of check boxes or radio buttons.
 *
 * @see CPDFWidgetButtonStyle
 */
- (CPDFWidgetButtonStyle)widgetCheckStyle;

/**
 * Set the button selected style of check boxes or radio buttons.
 *
 * @see CPDFWidgetButtonStyle
 */
- (void)setWidgetCheckStyle:(CPDFWidgetButtonStyle)widgetCheckStyle;


@end
