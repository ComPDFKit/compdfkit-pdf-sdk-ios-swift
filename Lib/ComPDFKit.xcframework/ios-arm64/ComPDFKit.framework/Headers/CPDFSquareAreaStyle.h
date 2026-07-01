//
//  CPDFSquareAreaStyle.h
//  ComPDFKit
//
//  Copyright © 2014-2026 PDF Technologies, Inc. All Rights Reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE ComPDFKit LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <ComPDFKit/CPDFKitPlatform.h>

/// CPDFSquareAreaStyle.h
@interface CPDFSquareAreaStyle : NSObject

/// Fill color of the square area. Nil means no fill.
@property (nonatomic, strong, nullable) CPDFKitPlatformColor *fillColor;

/// Fill opacity in the range [0.0, 1.0]. Default is 1.0.
@property (nonatomic, assign) CGFloat fillOpacity;

/// Border color of the square area. Nil means no border.
@property (nonatomic, strong, nullable) CPDFKitPlatformColor *borderColor;

/// Border opacity in the range [0.0, 1.0]. Default is 1.0.
@property (nonatomic, assign) CGFloat borderOpacity;

/// Border line width. Default is 1.0.
@property (nonatomic, assign) CGFloat borderWidth;

/// Border dash pattern. An array of NSNumber representing the lengths of painted and unpainted segments, e.g. @[@5, @2].
/// Nil or an empty array means a solid line.
@property (nonatomic, copy, nullable) NSArray<NSNumber *> *borderDashPattern;

/// Creates a default style instance with predefined values:
/// - fillColor: nil
/// - fillOpacity: 1.0
/// - borderColor: nil
/// - borderOpacity: 1.0
/// - borderWidth: 1.0
/// - borderDashPattern: nil
- (instancetype _Nonnull )init NS_DESIGNATED_INITIALIZER;

/// Convenience initializer that copies values from another style.
- (instancetype _Nonnull )initWithStyle:(CPDFSquareAreaStyle *_Nonnull)style;

/// Creates a style from a dictionary, typically parsed from JSON.
/// Supported keys:
/// - "fillColor": NSString (hex color, e.g. "#80A5D6A7")
/// - "fillOpacity": NSNumber
/// - "borderColor": NSString (hex color)
/// - "borderOpacity": NSNumber
/// - "borderWidth": NSNumber
/// - "borderDashPattern": NSArray<NSNumber>
/// Unspecified keys fall back to default values.
+ (instancetype _Nonnull )styleWithDictionary:(NSDictionary *_Nullable)dictionary;

@end

