//
//  CPDFFont.h
//  ComPDFKit
//
//  Copyright © 2014-2023 PDF Technologies, Inc. All Rights Reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE ComPDFKit LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface CPDFFont : NSObject

/**
 * Returns an array of font family names for all installed fonts.
 */
@property(class, nonatomic, readonly) NSArray<NSString *> *familyNames;

/**
 * The font family name of the font.
 */
@property(readonly, nonatomic) NSString * _Nonnull familyName;

/**
 * The style name of the font.
 */
@property(readonly, nonatomic) NSString * _Nullable styleName;

 /**
 * Initialize a font name object.
 *
 * Directly on objects using font names, adjusting initWithFamilyName: creates an illegal NULL type.
 * @param familyName The font family name of the font
 * @param fontStyle The style name of the font
 */
- (instancetype)initWithFamilyName:(NSString *)familyName fontStyle:(NSString *)fontStyle;

/**
 * Returns an array of font names for the specified family name
 */
+ (NSArray<NSString *> *)fontNamesForFamilyName:(NSString *)familyName;

/**
* Mapped font
* Default CPDFFont : Helvetica
*/
+ (CPDFFont *_Nullable)mappingFontWithFontString:(NSString *_Nullable)fontName;

/**
* Convert to the corresponding font name
* Default : Helvetica
*/
+ (NSString *_Nullable)convertAppleFont:(CPDFFont *_Nonnull)cPDFFont;

@end

NS_ASSUME_NONNULL_END
