//
//  CPDFPerimeterMeasureInfo.h
//  ComPDFKit
//
//  Copyright © 2014-2024 PDF Technologies, Inc. All Rights Reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE ComPDFKit LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <ComPDFKit/CPDFMeasureInfo.h>

NS_ASSUME_NONNULL_BEGIN

@interface CPDFPerimeterMeasureInfo : CPDFMeasureInfo

/**
 *  Getting the measure type in the measurement property value
 */
@property (nonatomic,assign,readonly) CPDFMeasureType mesureType;

@end

NS_ASSUME_NONNULL_END
