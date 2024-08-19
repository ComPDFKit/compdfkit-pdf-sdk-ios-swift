//
//  CPDFDocument+Protected.h
//  ComPDFKit
//
//  Copyright © 2014-2024 PDF Technologies, Inc. All Rights Reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE ComPDFKit LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <ComPDFKit/CPDFDocument.h>

typedef NSString *CPDFDocumentOptimizeOption NS_STRING_ENUM;

extern CPDFDocumentOptimizeOption const CPDFDocumentImageQualityOption; // NSNumber for the image quality.

@class CPDFSignature, CPDFSignatureWidgetAnnotation;

@interface CPDFDocument (Protected)

- (void)setPasswordOptions:(NSDictionary<CPDFDocumentWriteOption, id> *)options DEPRECATED_MSG_ATTRIBUTE("The api is currently in beta and Untested");

- (BOOL)isImageDocument;

#pragma mark - Accessors

- (Class)pageClass;

#pragma mark - Pages

/**
 * Insert the page number to the specified location
 *
 * @discussion page can only be used in the current document, if it is recommended from the page of another document "Use -importPages:fromDocument:atIndex:"
 */
- (BOOL)insertPageObject:(CPDFPage *)page atIndex:(NSUInteger)index;

#pragma mark - XFDF

- (BOOL)exportCustomWidget:(NSArray *)fieldNames toXFDFPath:(NSString *)xfdfPath;
- (BOOL)importCustomWidgetFromXFDFPath:(NSString *)xfdfPath;

#pragma mark - Form Data

- (BOOL)exportWidgetDataXFDFPath:(NSString *)xfdfPath DEPRECATED_MSG_ATTRIBUTE("The api is currently in beta and Untested");
- (BOOL)importWidgetDataWithXFDFPath:(NSString *)xfdfPath DEPRECATED_MSG_ATTRIBUTE("The api is currently in beta and Untested");

#pragma mark - Optimize

- (BOOL)writeOptimizeToURL:(NSURL *)url withOptions:(NSDictionary<CPDFDocumentOptimizeOption, id> *)options;

#pragma mark - Extract

- (NSUInteger)extractImageFromPages:(NSIndexSet *)indexSet toPath:(NSString *)path progress:(NSString* (^)(NSInteger pageIndex, NSInteger imageIndex, NSInteger index))progress;

- (CPDFKitPlatformImage *)extractImageFromPage:(CPDFPage *)page imageSelection:(CPDFSelection *)imageSelection;


@end
