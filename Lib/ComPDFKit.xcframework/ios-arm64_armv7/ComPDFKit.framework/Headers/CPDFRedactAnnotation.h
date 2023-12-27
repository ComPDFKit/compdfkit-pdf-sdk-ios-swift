//
//  CPDFRedactAnnotation.h
//  ComPDFKit
//
//  Copyright © 2014-2023 PDF Technologies, Inc. All Rights Reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE ComPDFKit LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <ComPDFKit/CPDFAnnotation.h>

/**
 * Redaction annotations are used to remove content from a document.
 */
@interface CPDFRedactAnnotation : CPDFAnnotation

@property(nonatomic,assign) BOOL drawRedactionsAsRedacted;

/**
 * Gets the areas that should be covered by the redaction annotation.
 */
- (NSArray *)quadrilateralPoints;
/**
 * Uses the quadrilateral points property to set the areas that should be covered by the redaction annotation.
 */
- (void)setQuadrilateralPoints:(NSArray *)points;

/**
 * Gets the fill color displayed in the specified area after applying the redaction. The color is drawn on the specified rect. Defaults to black.
 */
- (CPDFKitPlatformColor *)interiorColor;
/**
 * Sets the fill color displayed in the specified area after applying the redaction. The color is drawn on the specified rect. Defaults to black.
 */
- (void)setInteriorColor:(CPDFKitPlatformColor *)color;

/**
 * Gets the color used for the redaction’s border in its marked state. Defaults to red.
 */
- (CPDFKitPlatformColor *)borderColor;
/**
 * Sets the color used for the redaction’s border in its marked state. Defaults to red.
 */
- (void)setBorderColor:(CPDFKitPlatformColor *)color;

/**
 * Gets the text font displayed in the specified area after applying the redaction.
 */
- (CPDFKitPlatformFont *)font;
/**
 * Sets the text font displayed in the specified area after applying the redaction.
 */
- (void)setFont:(CPDFKitPlatformFont *)font;

/**
 * Gets the text color displayed in the specified area after applying the redaction.
 */
- (CPDFKitPlatformColor *)fontColor;
/**
 * Sets the text color displayed in the specified area after applying the redaction.
 */
- (void)setFontColor:(CPDFKitPlatformColor *)fontColor;

/**
 * Gets the text alignment displayed in the specified area after applying the redaction.
 */
- (NSTextAlignment)alignment;
/**
 * Sets the text alignment displayed in the specified area after applying the redaction.
 */
- (void)setAlignment:(NSTextAlignment)alignment;

/**
 * Gets the text displayed in the specified area after applying the redaction.
 */
- (NSString *)overlayText;
/**
 * Sets the text displayed in the specified area after applying the redaction.
 */
- (void)setOverlayText:(NSString *)text;

/**
 * Applies redaction annotation.
 */
- (void)applyRedaction;

@end
