//
//  CPDFBorder.h
//  ComPDFKit
//
//  Copyright © 2014-2024 PDF Technologies, Inc. All Rights Reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE ComPDFKit LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <ComPDFKit/CPDFKitPlatform.h>

/**
 * Style in which CPDFBorder is displayed.
 */
typedef NS_ENUM(NSInteger, CPDFBorderStyle) {
    CPDFBorderStyleSolid = 0,
    CPDFBorderStyleDashed = 1,
    CPDFBorderStyleBeveled = 2,
    CPDFBorderStyleInset = 3,
    CPDFBorderStyleUnderline = 4
};

@interface CPDFBorder : NSObject

- (instancetype)initWithStyle:(CPDFBorderStyle)style lineWidth:(CGFloat)lineWidth dashPattern:(NSArray *)dashPattern;

/**
 * Whether border is drawn solid, dashed etc.
 *
 * @see CPDFBorderStyle
 */
@property (nonatomic,readonly) CPDFBorderStyle style;

/**
 * Width of line used to stroke border.
 */
@property (nonatomic,readonly) CGFloat lineWidth;

/**
 * Array of floats specifying the dash pattern.
 */
@property (nonatomic,readonly) NSArray *dashPattern;

@end
