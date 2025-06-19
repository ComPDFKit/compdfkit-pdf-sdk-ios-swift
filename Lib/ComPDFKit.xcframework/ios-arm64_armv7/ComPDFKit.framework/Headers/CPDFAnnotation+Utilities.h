//
//  CPDFAnnotation+Utilities.h
//  ComPDFKit
//
//  Copyright © 2014-2025 PDF Technologies, Inc. All Rights Reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE ComPDFKit LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <ComPDFKit/ComPDFKit.h>

typedef NS_ENUM(NSInteger, CPDFWidgetCellState)
{
    CPDFWidgetMixedState = -1,
    CPDFWidgetOffState = 0,
    CPDFWidgetOnState = 1,
};

@interface CPDFAnnotation (Utilities)

- (CPDFAction *)action;
- (void)setAction:(CPDFAction *)action;

- (NSString *)string;
- (void)setString:(NSString *)newString;

- (BOOL)hasAppearanceStream;

//- (NSString *)widgetStringValue;
//- (void)setWidgetStringValue:(NSString *)widgetStringValue;

- (NSString *)buttonWidgetStateString DEPRECATED_MSG_ATTRIBUTE("The api is currently in beta and Untested");
- (BOOL)setButtonWidgetStateString:(NSString *)buttonWidgetStateString DEPRECATED_MSG_ATTRIBUTE("The api is currently in beta and Untested");

- (NSArray<NSString *> *)choices;
- (void)setChoices:(NSArray<NSString *> *)choices;

//- (CPDFAnnotation *)popup;
//- (void)setPopup:(CPDFAnnotation *)popup;

- (CPDFAction *)mouseUpAction;
- (void)setMouseUpAction:(CPDFAction *)mouseUpAction;

- (BOOL)shouldDisplay;
- (void)setShouldDisplay:(BOOL)shouldDisplay;

- (BOOL)shouldPrint;
- (void)setShouldPrint:(BOOL)shouldPrint;

- (void)setIsReadOnly:(BOOL)isReadOnly;

- (void)setAnnotationShouldDisplay:(BOOL)annotationShouldDisplay;

- (BOOL)annotationShouldDisplay;

- (NSString *)modificationDateString;

@end
