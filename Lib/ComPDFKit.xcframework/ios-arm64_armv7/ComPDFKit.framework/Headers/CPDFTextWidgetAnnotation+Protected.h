//
//  CPDFTextWidgetAnnotation+Protected.h
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

@interface CPDFTextWidgetAnnotation (Protected)

- (NSString *)defaultValue DEPRECATED_MSG_ATTRIBUTE("The api is currently in beta and Untested");
- (void)setDefaultValue:(NSString *)defaultValue DEPRECATED_MSG_ATTRIBUTE("The api is currently in beta and Untested");

- (BOOL)isScrollFlag DEPRECATED_MSG_ATTRIBUTE("The api is currently in beta and Untested");
- (void)setIsScrollFlag:(BOOL)isScrollFlag DEPRECATED_MSG_ATTRIBUTE("The api is currently in beta and Untested");

@end
