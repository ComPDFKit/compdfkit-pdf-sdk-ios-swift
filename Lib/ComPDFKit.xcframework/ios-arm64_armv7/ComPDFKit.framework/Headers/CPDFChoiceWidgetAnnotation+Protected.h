//
//  CPDFChoiceWidgetAnnotation+Protected.h
//  ComPDFKit
//
//  Copyright © 2014-2024 PDF Technologies, Inc. All Rights Reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE ComPDFKit LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <ComPDFKit/ComPDFKit.h>

@interface CPDFChoiceWidgetAnnotation (Protected)

- (BOOL)multiSelcetFlag DEPRECATED_MSG_ATTRIBUTE("The api is currently in beta and Untested");
- (BOOL)setMultiSelcetFlag:(BOOL)multiSelcetFlag DEPRECATED_MSG_ATTRIBUTE("The api is currently in beta and Untested");

- (BOOL)isEditable DEPRECATED_MSG_ATTRIBUTE("The api is currently in beta and Untested");
- (BOOL)setIsEditable:(BOOL)isEditable DEPRECATED_MSG_ATTRIBUTE("The api is currently in beta and Untested");

- (BOOL)commitFlag DEPRECATED_MSG_ATTRIBUTE("The api is currently in beta and Untested");
- (BOOL)setCommitFlag:(BOOL)commitFlag DEPRECATED_MSG_ATTRIBUTE("The api is currently in beta and Untested");

- (BOOL)setComBoxValueUTF:(NSString *)stringValue DEPRECATED_MSG_ATTRIBUTE("The api is currently in beta and Untested");

- (NSIndexSet *)selectItemAtIndexs DEPRECATED_MSG_ATTRIBUTE("The api is currently in beta and Untested");
- (BOOL)setSelectItemAtIndexs:(NSIndexSet *)selectItemAtIndexs DEPRECATED_MSG_ATTRIBUTE("The api is currently in beta and Untested");

@end
