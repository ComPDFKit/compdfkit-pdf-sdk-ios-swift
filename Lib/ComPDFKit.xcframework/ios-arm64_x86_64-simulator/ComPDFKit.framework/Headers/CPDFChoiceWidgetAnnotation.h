//
//  CPDFChoiceWidgetAnnotation.h
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

@interface CPDFChoiceWidgetItem : NSObject

@property (nonatomic,retain) NSString *value;
@property (nonatomic,retain) NSString *string;

@end

/**
 * A CPDFChoiceWidgetAnnotation object provides user interactivity on a page of a PDF document, in the form of pop-up menus and lists.
 *
 * @discussion CPDFButtonWidgetAnnotation inherits general annotation behavior from the CPDFWidgetAnnotation class.
 */
@interface CPDFChoiceWidgetAnnotation : CPDFWidgetAnnotation

/**
 * Initializes CPDFChoiceWidgetAnnotation object.
 */
- (instancetype)initWithDocument:(CPDFDocument *)document listChoice:(BOOL)isListChoice;

/**
 * Returns a Boolean value indicating whether the widget annotation is a list.
 *
 * @discussion There are two flavors of Choice widget annotations, lists and pop-up menus. These methods allow you to differentiate.
 */
@property (nonatomic,readonly) BOOL isListChoice;

/**
 * Returns an array of CPDFChoiceWidgetItem that represent the items available in the list or pop-up menu of the choice widget annotation.
 */
@property (nonatomic,retain) NSArray<CPDFChoiceWidgetItem *> *items;

@property (nonatomic,assign) NSInteger selectItemAtIndex;

@end
