//
//  CPDFInkAnnotation+Protected.h
//  ComPDFKit
//
//  Copyright © 2014-2025 PDF Technologies, Inc. All Rights Reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE ComPDFKit LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <ComPDFKit/CPDFInkAnnotation.h>

typedef NS_ENUM(NSInteger, CPDFInkType) {
    CPDFInkTypeNormal = 0,
    CPDFInkTypeSignature = 1,
    CPDFInkTypeMicpen = 2
};

@interface CPDFInkAnnotation (Protected)

- (CPDFInkType)inkType;
- (void)setInkType:(CPDFInkType)inkType;

@end
