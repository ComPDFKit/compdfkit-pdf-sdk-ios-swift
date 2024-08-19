//
//  CPDFView+Display.h
//  ComPDFKit
//
//  Copyright © 2014-2024 PDF Technologies, Inc. All Rights Reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE ComPDFKit LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <ComPDFKit/CPDFView.h>
#import <ComPDFKit/CPDFTextWidgetAnnotation.h>

@interface CPDFView (Display)

#pragma mark - Display

- (void)setNeedsDisplayPageViewForPage:(CPDFPage *)page;

- (void)setNeedsDisplayAnnotationViewForPage:(CPDFPage *)page;

#pragma mark - Widget

- (void)editAnnotationTextWidget:(CPDFTextWidgetAnnotation *)textWidget;

#pragma mark - Rendering

- (void)drawAnnotation:(CPDFAnnotation *)annotation toContext:(CGContextRef)context;

#pragma mark - Interaction

- (NSArray<UIDragItem *> *)itemsForSelectionDragInteraction:(CPDFSelection *)selection API_AVAILABLE(ios(11.0));

#pragma mark - Gesture

- (void)longPressGestureEndAtPoint:(CGPoint)point forPage:(CPDFPage *)page;

@end
