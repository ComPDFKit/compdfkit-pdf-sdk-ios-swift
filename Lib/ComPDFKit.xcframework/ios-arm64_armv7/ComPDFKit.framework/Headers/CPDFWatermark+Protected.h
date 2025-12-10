//
//  CPDFWatermark+Protected.h
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

@interface CPDFWatermark (Protected)

- (CGFloat)autoSizePercentage DEPRECATED_MSG_ATTRIBUTE("The api is currently in beta and Untested");

- (void)setAutoSizeWithPercentage:(CGFloat)percentage DEPRECATED_MSG_ATTRIBUTE("The api is currently in beta and Untested");

@end
