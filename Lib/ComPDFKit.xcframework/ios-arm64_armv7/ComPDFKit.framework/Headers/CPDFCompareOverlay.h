//
//  CPDFCompareOverlay.h
//  ComPDFKit
//
//  Copyright © 2014-2026 PDF Technologies, Inc. All Rights Reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE ComPDFKit LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <ComPDFKit/CPDFKitPlatform.h>

typedef NS_ENUM(NSInteger, CPDFBlendMode) {
      CPDFBlendModeNormal = 0,
      CPDFBlendModeMultiply,
      CPDFBlendModeScreen,
      CPDFBlendModeOverlay,
      CPDFBlendModeDarken,
      CPDFBlendModeLighten,
      CPDFBlendModeColorDodge,
      CPDFBlendModeColorBurn,
      CPDFBlendModeHardLight,
      CPDFBlendModeSoftLight,
      CPDFBlendModeDifference,
      CPDFBlendModeExclusion,
      CPDFBlendModeHue,
      CPDFBlendModeSaturation,
      CPDFBlendModeColour,
      CPDFBlendModeLuminosity,
      CPDFBlendModeLast = CPDFBlendModeLuminosity,
};

@class CPDFDocument;

@interface CPDFCompareOverlay : NSObject

/**
 * Initialize it with the given two versions of a document.
 * By default, it will generate a comparison document according to the order of pages, starting from the first page of both versions of the document.
 *
 * @param oldDocument The old version of a document
 * @param newDocument The new version of a document.
 */
- (instancetype)initWithOldDocument:(CPDFDocument *)oldDocument
                        newDocument:(CPDFDocument *)newDocument;

/**
 * Initialize it with the given two versions of a document.
 * and indices of the pages on which the points should be selected in both versions of a document.
 * 
 * @param oldDocument The old version of a document
 * @param oldPageRange The page range of the old document, for example: 1,3,5,6-10.
 * @param newDocument The new version of a document.
 * @param newPageString The page range of the new document, for example: 1,3,5,6-10.
 */
- (instancetype)initWithOldDocument:(CPDFDocument *)oldDocument
                       oldPageRange:(NSString *)oldPageString
                        newDocument:(CPDFDocument *)newDocument
                       newPageRange:(NSString *)newPageString;

/**
 * Compares the document.
 */
- (BOOL)compare;

/**
 * Sets the color that will be used to replace all strokes in the old version of a document.
 *
 * Returns true on success, false on failure.
 * @param strokeColor RGB color value, range 0-255.
 */
- (BOOL)setOldDocumentStrokeColor:(CPDFKitPlatformColor *)strokeColor;

/**
 * Sets the color that will be used to replace all strokes in the new version of a document.
 *
 * Returns true on success, false on failure.
 * @param strokeColor RGB color value, range 0-255.
 */
- (BOOL)setNewDocumentStrokeColor:(CPDFKitPlatformColor *)strokeColor;

/**
 * Sets the opacity that will be used to replace all strokes in the old version of a document.
 *
 * Returns true on success, false on failure.
 * @param strokeAlpha Opacity value, range 0-1.
 */
- (BOOL)setOldDocumentStrokeOpacity:(CGFloat)strokeAlpha;

/**
 * Sets the opacity that will be used to replace all strokes in the new version of a document.
 *
 * Returns true on success, false on failure.
 * @param strokeAlpha Opacity value, range 0-1.
 */
- (BOOL)setNewDocumentStrokeOpacity:(CGFloat)strokeAlpha;

/**
 * Sets the fill opacity that will be used to replace all strokes in the old version of a document.
 *
 * Returns true on success, false on failure.
 * @param fillAlpha Opacity value, range 0-1.
 */
- (BOOL)setOldDocumentFillOpacity:(CGFloat)fillAlpha;

/**
 * Sets the fill opacity that will be used to replace all strokes in the new version of a document.
 *
 * Returns true on success, false on failure.
 * @param fillAlpha Opacity value, range 0-1.
 */
- (BOOL)setNewDocumentFillOpacity:(CGFloat)fillAlpha;

/**
 * Sets whether the path is filled with white.
 */
- (BOOL)setNoFill:(BOOL)noFill;

/**
 * Sets the blend mode that will be used when overlaying the new version of a document onto the old version.
 *
 * Returns true on success, false on failure.
 * @see CPDFBlendMode
 */
- (BOOL)setBlendMod:(CPDFBlendMode)blendMod;

/**
 * Gets the generated comparison document once the user compares both versions of a document.
 *
 * Returns The generated document.
 */
- (CPDFDocument *)comparisonDocument;

@end
