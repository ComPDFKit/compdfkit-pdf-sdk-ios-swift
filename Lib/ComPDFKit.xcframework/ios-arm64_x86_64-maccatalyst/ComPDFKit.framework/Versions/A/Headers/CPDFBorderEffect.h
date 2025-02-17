//
//  CPDFBorderEffect.h
//  ComPDFKit
//
//  Copyright © 2014-2025 PDF Technologies, Inc. All Rights Reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE ComPDFKit LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 *  The effect intensity ranges from 0 to 2
 *  Strength is 0 The style is not a cloud
 */
typedef NS_ENUM(NSInteger, CPDFIntensityType) {
    CPDFIntensityTypeZero = 0,
    CPDFIntensityTypeOne,
    CPDFIntensityTypeTwo
};

typedef NS_ENUM(NSInteger, CPDFBorderEffectType) {
    CPDFBorderEffectTypeSolid,  // Corresponding 'S'
    CPDFBorderEffectTypeCloudy  // Corresponding 'C'
};

@interface CPDFBorderEffect : NSObject

/**
 *  Setting the border effect strength
 */
@property (nonatomic, assign) CPDFIntensityType intensityType;

/**
 *  Setting boundary type
 *  S is the boundary effect defined by BS, and C is cloudy
 */
@property (nonatomic, assign) CPDFBorderEffectType borderEffectType;

@end

NS_ASSUME_NONNULL_END
