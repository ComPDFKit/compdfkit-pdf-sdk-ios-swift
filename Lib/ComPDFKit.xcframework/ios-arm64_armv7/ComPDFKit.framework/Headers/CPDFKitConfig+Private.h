//
//  CPDFKitConfig+Private.h
//  ComPDFKit
//
//  Copyright © 2014-2024 PDF Technologies, Inc. All Rights Reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE ComPDFKit LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import "CPDFKitConfig.h"

typedef NS_ENUM(NSInteger, FreeHandPenStyle) {
    PEN_STYLE_PENCIL,
    PEN_STYLE_MIC,
};

@interface CPDFKitConfig () {
    dispatch_queue_t _queue;
    dispatch_queue_t _searchQueue;
}

@property (nonatomic,assign) CGFloat textmarkOpcity;

@property (nonatomic,assign) CGFloat  shapeOpcity;
@property (nonatomic,assign) CGFloat  shapeFillOpcity;
@property (nonatomic,assign) CGFloat  shapeThickness;
@property (nonatomic,assign) BOOL     drawFillColor;
@property (nonatomic,assign) BOOL     drawBorderColor;

@property (nonatomic,assign) FreeHandPenStyle freehandPenType;
@property (nonatomic,assign) CGFloat pencilOpcity;
@property (nonatomic,assign) CGFloat micPenOpcity;
@property (nonatomic,assign) CGFloat pencilSize;
@property (nonatomic,assign) CGFloat micPenSize;

@property (nonatomic,retain) CPDFKitPlatformColor  *typeWriteColor;
@property (nonatomic,retain) NSString *typeWriteFontName;
@property (nonatomic,assign) CGFloat   typeWriteFontSize;
@property (nonatomic,assign) CGFloat   typeWriteOpacity;

@property (nonatomic,assign) BOOL  isShowFormRequiredFlagColor DEPRECATED_MSG_ATTRIBUTE("The api is currently in beta and Untested");
@property (nonatomic,retain) CPDFKitPlatformColor  *formRequiredFlagColor DEPRECATED_MSG_ATTRIBUTE("The api is currently in beta and Untested");
@property (nonatomic,retain) CPDFKitPlatformColor  *enableFormFieldHighlightColor DEPRECATED_MSG_ATTRIBUTE("The api is currently in beta and Untested");
@property (nonatomic,retain) CPDFKitPlatformColor  *enableLinkFieldHighlightColor DEPRECATED_MSG_ATTRIBUTE("The api is currently in beta and Untested");
@property (nonatomic,assign) BOOL isShowReadOnlySignatureAnnotation DEPRECATED_MSG_ATTRIBUTE("The api is currently in beta and Untested");

- (dispatch_queue_t)queue;

- (dispatch_queue_t)searchQueue;

@end
