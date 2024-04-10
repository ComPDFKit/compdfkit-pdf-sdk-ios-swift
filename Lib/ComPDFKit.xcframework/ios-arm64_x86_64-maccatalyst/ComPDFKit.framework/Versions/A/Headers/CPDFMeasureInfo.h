//
//  CPDFMeasureInfo.h
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

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, CPDFMeasureType) {
    CPDFMeasureTypeDistance = 0,
    CPDFMeasureTypePerimeter,
    CPDFMeasureTypeArea
};

typedef NS_OPTIONS(NSInteger, CPDFCaptionType) {
    CPDFCaptionTypeNone = 0,
    CPDFCaptionTypeArea,
    CPDFCaptionTypeLength
};

@interface CPDFMeasureConstants : NSObject

/**
 * The shared CPDFMeasureConstants instance.
 */
+ (instancetype)sharedInstance;

// Precision Values
@property (nonatomic, readonly) NSInteger precisionValueZero;
@property (nonatomic, readonly) NSInteger precisionValueOne;
@property (nonatomic, readonly) NSInteger precisionValueTwo;
@property (nonatomic, readonly) NSInteger precisionValueThree;
@property (nonatomic, readonly) NSInteger precisionValueFour;

// Unit Conversion Values
@property (nonatomic, readonly) double ptPt;
@property (nonatomic, readonly) double ptCm;
@property (nonatomic, readonly) double ptIn;
@property (nonatomic, readonly) double ptMm;
@property (nonatomic, readonly) double ptM;
@property (nonatomic, readonly) double ptKm;
@property (nonatomic, readonly) double ptFt;
@property (nonatomic, readonly) double ptYd;
@property (nonatomic, readonly) double ptMi;

// Unit Constants
@property (nonatomic, copy, readonly) NSString *cpdfPt;
@property (nonatomic, copy, readonly) NSString *cpdfIn;
@property (nonatomic, copy, readonly) NSString *cpdfMm;
@property (nonatomic, copy, readonly) NSString *cpdfCm;
@property (nonatomic, copy, readonly) NSString *cpdfM;
@property (nonatomic, copy, readonly) NSString *cpdfKm;
@property (nonatomic, copy, readonly) NSString *cpdfFt;
@property (nonatomic, copy, readonly) NSString *cpdfYd;
@property (nonatomic, copy, readonly) NSString *cpdfMi;

@end

@interface CPDFMeasureInfo : NSObject

/**
 *  Setting the scale factor in the measurement property value
 */
@property (nonatomic,assign) CGFloat factor;
/**
 *  Setting the unit in the measurement property value
 */
@property (nonatomic,assign) NSString *unit;
/**
 *  Setting the decimal symbol in the measurement property value
 */
@property (nonatomic,retain) NSString *decimalSymbol;
/**
 *  Setting the thousand symbol in the measurement property value
 */
@property (nonatomic,retain) NSString *thousandSymbol;
/**
 *  Setting the decimal part display mode in the measurement property value
 */
@property (nonatomic,retain) NSString *display;
/**
 *  Setting the precision in the measurement property value
 */
@property (nonatomic,assign) NSInteger precision;
/**
 *  Setting the unit prefix in the measurement property value
 */
@property (nonatomic,retain) NSString *unitPrefix;
/**
 *  Setting the unit suffix in the measurement property value
 */
@property (nonatomic,retain) NSString *unitSuffix;
/**
 *  Setting the unit position, units before/after the calculation result, before P, after S
 */
@property (nonatomic,retain) NSString *unitPosition;
/**
 *  Setting the scale in the measurement property value
 */
@property (nonatomic,assign) CGFloat rulerBase;

@property (nonatomic,retain) NSString *rulerBaseUnit;

@property (nonatomic,assign) CGFloat rulerTranslate;

@property (nonatomic,retain) NSString *rulerTranslateUnit;
/**
 *  Setting the format value in the measurement property value
 */
@property (nonatomic,retain) NSString *formatValue;
/**
 *  Setting the CPDFCaptionType in the measurement property value
 */
@property (nonatomic,assign) CPDFCaptionType captionType;

@end

NS_ASSUME_NONNULL_END
