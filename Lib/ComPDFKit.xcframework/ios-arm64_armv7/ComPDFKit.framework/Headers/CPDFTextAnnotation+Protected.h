//
//  CPDFTextAnnotation+Protected.h
//  ComPDFKit
//
//  Copyright © 2014-2025 PDF Technologies, Inc. All Rights Reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE ComPDFKit LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <ComPDFKit/CPDFTextAnnotation.h>

typedef NS_ENUM(NSInteger, CPDFTextAnnotationIconType) {
    CPDFTextAnnotationIconComment = 0,
    CPDFTextAnnotationIconKey = 1,
    CPDFTextAnnotationIconNote = 2,
    CPDFTextAnnotationIconHelp = 3,
    CPDFTextAnnotationIconNewParagraph = 4,
    CPDFTextAnnotationIconParagraph = 5,
    CPDFTextAnnotationIconInsert = 6
};

@interface CPDFTextAnnotation (Protected)

- (CPDFTextAnnotationIconType)iconType;
- (void)setIconType:(CPDFTextAnnotationIconType)type;

@end
