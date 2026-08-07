//
//  CPDFButtonWidgetAnnotation.h
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
 *
 * @note Migration from previous versions:
 *       Use @c -initWithPage:document:controlType: to create button widget annotations,
 *       then call @c -[CPDFPage updateAndAddAnnotation:] to attach them.
 */
@interface CPDFButtonWidgetAnnotation : CPDFWidgetAnnotation

/**
 * Initializes a button widget annotation with page, document and control type.
 *
 * @param page        The page on which the annotation will reside.
 * @param document    The document that owns the page.
 * @param controlType The button type (checkbox, radio button, push button).
 *
 * @discussion Creates the engine object and binds it to the page.
 *             Call @c -[CPDFPage updateAndAddAnnotation:] to finish registration.
 */
- (nullable instancetype)initWithPage:(CPDFPage *)page document:(CPDFDocument *)document controlType:(CPDFWidgetControlType)controlType;

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

@property (nonatomic, strong) CPDFAction *action;

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
