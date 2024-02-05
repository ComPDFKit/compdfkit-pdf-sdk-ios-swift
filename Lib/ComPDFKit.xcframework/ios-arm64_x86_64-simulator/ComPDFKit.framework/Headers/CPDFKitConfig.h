//
//  CPDFKitConfig.h
//  ComPDFKit
//
//  Copyright © 2014-2024 PDF Technologies, Inc. All Rights Reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE ComPDFKit LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <Foundation/Foundation.h>
#import <ComPDFKit/CPDFKitPlatform.h>
#import <ComPDFKit/CPDFView.h>

#define CPDFKitShareConfig [CPDFKitConfig sharedInstance]

@interface CPDFKitConfig : NSObject

/**
 * The shared CPDFKitConfig configuration instance.
 */
+ (instancetype)sharedInstance;

/**
 * Get the cache size.
 */
- (unsigned long long)cacheSize;
/**
 * Clear the cache.
 */
- (void)clearCache;

/**
 * Get the default view mode of CPDFView.
 * View Mode : Horizontally, Vertically
 *
 * @see CPDFDisplayDirection
 */
- (CPDFDisplayDirection)displayDirection;
/**
 * Set the default view mode of CPDFView.
 *
 * @see CPDFDisplayDirection
 */
- (void)setDisplayDirection:(CPDFDisplayDirection)displayDirection;

/**
 * Get the default reading mode of CPDFView.
 * Reading Mode : Night, Soft, Green, Other
 *
 * @see CPDFDisplayMode
 */
- (CPDFDisplayMode)displayMode;
/**
 * Set the default reading mode of CPDFView.
 *
 * @see CPDFDisplayMode
 */
- (void)setDisplayMode:(CPDFDisplayMode)displayMode;

/**
 * Get a custom background color for the rendered mode of CPDFView.
 */
- (CPDFKitPlatformColor *)displayModeCustomColor;
/**
 * Set a custom background color for the rendered mode of CPDFView.
 */
- (void)setDisplayModeCustomColor:(CPDFKitPlatformColor *)displayModeCustomColor;

/**
 * Get whether to allow to highlight link field in the CPDFView.
 */
- (BOOL)enableLinkFieldHighlight;
/**
 * Set whether to allow to highlight link field in the CPDFView.
 */
- (void)setEnableLinkFieldHighlight:(BOOL)enableLinkFieldHighlight;
/**
 * Get whether to allow to highlight form field in the CPDFView.
 */
- (BOOL)enableFormFieldHighlight;
/**
 * Set whether to allow to highlight form field in the CPDFView.
 */
- (void)setEnableFormFieldHighlight:(BOOL)enableFormFieldHighlight;
/**
 * Get whether to allow annotation rotation.
 */
- (BOOL)enableAnnotationNoRotate;
/**
 * If set, do not rotate the annotation’s appearance to match the rotation of the page.
 * The upper-left corner of the annotation rectangle shall remain in a fixed location on the page, regardless of the page rotation.
 */
- (void)setEnableAnnotationNoRotate:(BOOL)enableAnnotationNoRotate;

/**
 * Get the default author of annotations.
 */
- (NSString *)annotationAuthor;
/**
 * Set the default author of annotations.
 */
- (void)setAnnotationAuthor:(NSString *)annotationAuthor;

/**
 * Get whether to allow to add freehand annotation by PencilKit.
 */
- (BOOL)enableFreehandPencilKit;
/**
 * Set whether to allow to add annotation by PencilKit.
 */
- (void)setEnableFreehandPencilKit:(BOOL)enableFreehandPencilKit;

/**
 * Get the default color of highlight annotations.
 */
- (CPDFKitPlatformColor *)highlightAnnotationColor;
/**
 * Set the default color of highlight annotations.
 */
- (void)setHighlightAnnotationColor:(CPDFKitPlatformColor *)highlightAnnotationColor;

/**
 * Get the default color of underline annotations.
 */
- (CPDFKitPlatformColor *)underlineAnnotationColor;
/**
 * Set the default color of underline annotations.
 */
- (void)setUnderlineAnnotationColor:(CPDFKitPlatformColor *)underlineAnnotationColor;

/**
 * Get the default color of strikeout annotations.
 */
- (CPDFKitPlatformColor *)strikeoutAnnotationColor;
/**
 * Set the default color of strikeout annotations.
 */
- (void)setStrikeoutAnnotationColor:(CPDFKitPlatformColor *)strikeoutAnnotationColor;

/**
 * Get the default color of squiggly annotations.
 */
- (CPDFKitPlatformColor *)squigglyAnnotationColor;
/**
 * Set the default color of squiggly annotations.
 */
- (void)setSquigglyAnnotationColor:(CPDFKitPlatformColor *)squigglyAnnotationColor;

/**
 * Get the default opacity of markup annotations.
 */
- (CGFloat)markupAnnotationOpacity;
/**
 * Set the default opacity of markup annotations.
 */
- (void)setMarkupAnnotationOpacity:(CGFloat)markupAnnotationOpacity;

/**
 * Get the default color of shape annotations.
 */
- (CPDFKitPlatformColor *)shapeAnnotationColor;
/**
 * Set the default color of shape annotations.
 */
- (void)setShapeAnnotationColor:(CPDFKitPlatformColor *)shapeAnnotationColor;

/**
 * Get the default interior color of shape annotations.
 */
- (CPDFKitPlatformColor *)shapeAnnotationInteriorColor;
/**
 * Set the default interior color of shape annotations.
 */
- (void)setShapeAnnotationInteriorColor:(CPDFKitPlatformColor *)shapeAnnotationInteriorColor;

/**
 * Get the default opacity of shape annotations.
 */
- (CGFloat)shapeAnnotationOpacity;
/**
 * Set the default opacity of shape annotations.
 */
- (void)setShapeAnnotationOpacity:(CGFloat)shapeAnnotationOpacity;

/**
 * Get the default interior opacity of shape annotations.
 */
- (CGFloat)shapeAnnotationInteriorOpacity;
/**
 * Set the default interior opacity of shape annotations.
 */
- (void)setShapeAnnotationInteriorOpacity:(CGFloat)shapeAnnotationInteriorOpacity;

/**
 * Get the default border width of shape annotations.
 */
- (CGFloat)shapeAnnotationBorderWidth;
/**
 * Set the default border width of shape annotations.
 */
- (void)setShapeAnnotationBorderWidth:(CGFloat)shapeAnnotationBorderWidth;

/**
 * Get the default color of freehand annotations.
 */
- (CPDFKitPlatformColor *)freehandAnnotationColor;
/**
 * Set the default color of freehand annotations.
 */
- (void)setFreehandAnnotationColor:(CPDFKitPlatformColor *)freehandAnnotationColor;

/**
 * Get the default opacity of freehand annotations.
 */
- (CGFloat)freehandAnnotationOpacity;
/**
 * Set the default opacity of freehand annotations.
 */
- (void)setFreehandAnnotationOpacity:(CGFloat)freehandAnnotationOpacity;

/**
 * Get the default border width of freehand annotations.
 */
- (CGFloat)freehandAnnotationBorderWidth;
/**
 * Set the default border width of freehand annotations.
 */
- (void)setFreehandAnnotationBorderWidth:(CGFloat)freehandAnnotationBorderWidth;

- (BOOL)isEnableContentEditNotDrawAnnotation;

- (void)setIsEnableContentEditNotDrawAnnotation:(BOOL)isEnableContentEditNotDrawAnnotation;


@end
