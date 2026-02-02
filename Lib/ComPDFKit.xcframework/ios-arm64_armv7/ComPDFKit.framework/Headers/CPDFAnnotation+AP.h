//
//  CPDFAnnotation+AP.h
//  ComPDFKit
//
//  Copyright © 2014-2026 PDF Technologies, Inc. All Rights Reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE ComPDFKit LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <ComPDFKit/CPDFAnnotation.h>

@interface CPDFAnnotation (AP)

- (void)updateAppearanceStreamWithImage:(CPDFKitPlatformImage *)image;

- (void)updateAppearanceStreamWithImage:(CPDFKitPlatformImage *)image rotation:(NSInteger)rotation;

- (void)updateAppearanceStreamWithPaths:(NSArray<NSArray *> *)paths
                                  border:(CGFloat)border
                                  color:(CPDFKitPlatformColor *)color;

- (void)updateAppearanceStreamWithRect:(CGRect)rect
                                border:(CGFloat)border
                                 color:(CPDFKitPlatformColor *)color
                             fillColor:(CPDFKitPlatformColor *)fillColor;

- (void)updateAppearanceStreamWithArc:(CGRect)rect
                               border:(CGFloat)border
                                color:(CPDFKitPlatformColor *)color
                            fillColor:(CPDFKitPlatformColor *)fillColor;

- (void)updateAppearanceStream:(NSInteger)rotation;

- (NSInteger)appearanceStreamRotation;

@end
