//
//  CPDFDocumentMemoryDistribution.h
//  ComPDFKit
//
//  Copyright © 2014-2025 PDF Technologies, Inc. All Rights Reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE ComPDFKit LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <Foundation/Foundation.h>

/**
 * An enumeration of memory distribution categories for PDF document elements.
 *
 * @discussion Each category corresponds to a type of element within a PDF document,
 * such as images, fonts, annotations, etc. Use these values with CPDFDocumentMemoryDistribution
 * to query the size of specific element categories.
 */
typedef NS_ENUM(NSUInteger, CPDFMemoryDistributionCategory) {
    /** Image elements. */
    CPDFMemoryDistributionCategoryImage = 0,
    /** Content stream data. */
    CPDFMemoryDistributionCategoryContentStream,
    /** Font data. */
    CPDFMemoryDistributionCategoryFont,
    /** Colorspace definitions. */
    CPDFMemoryDistributionCategoryColorSpace,
    /** Outlines (bookmarks). */
    CPDFMemoryDistributionCategoryOutlines,
    /** Annotation data (excluding links). */
    CPDFMemoryDistributionCategoryAnnots,
    /** Extended graphics state. */
    CPDFMemoryDistributionCategoryExtGState,
    /** AcroForm (interactive form) data. */
    CPDFMemoryDistributionCategoryAcroForm,
    /** Link annotations. */
    CPDFMemoryDistributionCategoryLink,
    /** Embedded file data. */
    CPDFMemoryDistributionCategoryEmbeddedFile,
    /** Cross-reference table. */
    CPDFMemoryDistributionCategoryXRef,
    /**Other**/
    CPDFMemoryDistributionCategoryOther,
    /** Total document size (sum of all categories). */
    CPDFMemoryDistributionCategoryTotal,
};

/**
 * A structure that holds the memory size distribution of various PDF document elements.
 *
 * @discussion All size values are in bytes (uint32_t).
 */
typedef struct _CPDFDocumentElementSize {
    /** Size of image elements in bytes. */
    uint32_t imageSize;
    /** Size of content stream data in bytes. */
    uint32_t contentSize;
    /** Size of font data in bytes. */
    uint32_t fontSize;
    /** Size of colorspace definitions in bytes. */
    uint32_t colorspaceSize;
    /** Size of outlines (bookmarks) in bytes. */
    uint32_t outlinesSize;
    /** Size of annotation data in bytes. */
    uint32_t annotsSize;
    /** Size of extended graphics state in bytes. */
    uint32_t extGStateSize;
    /** Size of AcroForm data in bytes. */
    uint32_t acroFormSize;
    /** Size of link annotation data in bytes. */
    uint32_t linkSize;
    /** Size of embedded file data in bytes. */
    uint32_t embeddedFileSize;
    /** Size of cross-reference table in bytes. */
    uint32_t xrefSize;
    /** Total document size in bytes. */
    uint32_t totalSize;
} CPDFDocumentElementSize;

/**
 * CPDFDocumentMemoryDistribution provides statistics on the memory/space distribution
 * of different element categories within a PDF document.
 *
 * @discussion Use this class to analyze how much space each type of element (images, fonts,
 * annotations, etc.) occupies in a PDF file. This is particularly useful for understanding
 * document composition before performing optimization/compression operations.
 *
 * @code
 * CPDFDocumentMemoryDistribution *distribution = [[CPDFDocumentMemoryDistribution alloc] initWithFilePath:@"/path/to/file.pdf" password:nil];
 * if (distribution) {
 *     uint32_t totalSize = [distribution totalSize];
 *     uint32_t imageSize = [distribution sizeForCategory:CPDFMemoryDistributionCategoryImage];
 *     CPDFDocumentElementSize elementSize = [distribution elementSize];
 *     // Use elementSize.imageSize, elementSize.fontSize, etc.
 * }
 * @endcode
 */
@interface CPDFDocumentMemoryDistribution : NSObject

#pragma mark - Initializers

/**
 * Initializes a memory distribution analysis for the PDF file at the given path.
 *
 * @param filePath The file path to the PDF document.
 * @param password The password for opening encrypted documents; pass nil if not needed.
 * @return An initialized CPDFDocumentMemoryDistribution instance, or nil if initialization fails.
 */
- (nullable instancetype)initWithFilePath:(nonnull NSString *)filePath
                                 password:(nullable NSString *)password;

/**
 * Initializes a memory distribution analysis for the PDF document at the given URL.
 *
 * @param url The file URL to the PDF document.
 * @param password The password for opening encrypted documents; pass nil if not needed.
 * @return An initialized CPDFDocumentMemoryDistribution instance, or nil if initialization fails.
 */
- (nullable instancetype)initWithURL:(nonnull NSURL *)url
                            password:(nullable NSString *)password;

#pragma mark - Query

/**
 * Returns the complete element size distribution as a structure.
 *
 * @return A CPDFDocumentElementSize structure containing the sizes of all element categories.
 */
- (CPDFDocumentElementSize)elementSize;

/**
 * Returns the total document size in bytes.
 *
 * @return The total size of the document in bytes.
 */
- (uint32_t)totalSize;

/**
 * Returns the size (in bytes) for the specified element category.
 *
 * @param category The category to query.
 * @return The size in bytes for the given category.
 */
- (uint32_t)sizeForCategory:(CPDFMemoryDistributionCategory)category;

@end
