//
//  CPDFDocument.h
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
#import "CPDFOptimizeOption.h"
#import "CPDFDocumentMemoryDistribution.h"
#import "CPDFDeferredSignSession.h"
#import "CPDFTSAClient.h"

extern NSNotificationName const CPDFDocumentDidUnlockNotification;

extern NSNotificationName const CPDFDocumentPageCountChangedNotification;

extern NSNotificationName const CPDFDocumentPageDataDidChangeNotification;

extern NSNotificationName const CPDFDocumentWatermarkDidChangeNotification;

extern NSErrorDomain const CPDFDocumentErrorDomain;

NS_ERROR_ENUM(CPDFDocumentErrorDomain) {
    CPDFDocumentUnknownError  = 1,  // Unknown error.
    CPDFDocumentFileError     = 2,  // File not found or could not be opened.
    CPDFDocumentFormatError   = 3,  // File not in PDF format or corrupted.
    CPDFDocumentPasswordError = 4,  // Password required or incorrect password.
    CPDFDocumentSecurityError = 5,  // Unsupported security scheme.
    CPDFDocumentPageError     = 6   // Page not found or content error.
};

/**
 * An enumeration that specifies document permissions status.
 */
typedef NS_ENUM(NSInteger, CPDFDocumentPermissions) {
    /** The status that indicates no document permissions. */
    CPDFDocumentPermissionsNone = 0,
    /** The status that indicates user document permissions. */
    CPDFDocumentPermissionsUser,
    /** The status that indicates owner document permissions. */
    CPDFDocumentPermissionsOwner
};

typedef NS_OPTIONS(NSInteger, CPDFSearchOptions) {
    CPDFSearchCaseInsensitive = 0,
    /** If not set, it will not match case by default. */
    CPDFSearchCaseSensitive = 1,
    /** If not set, it will not match the whole word by default. */
    CPDFSearchMatchWholeWord = 2,
    /** If not set, it will skip past the current match to look for the next match. */
    CPDFSearchConsecutive = 4
};

/**
 * PDF/A conformance levels.
 */
typedef NS_ENUM(NSInteger, CPDFType) {
    CPDFTypePDF = 0,
    /** PDF/A-1a */
    CPDFTypePDFA1a,
    /** PDF/A-1b */
    CPDFTypePDFA1b,
    /** PDF/A-2a */
    CPDFTypePDFA2a,
    /** PDF/A-2u */
    CPDFTypePDFA2u,
    /** PDF/A-2b */
    CPDFTypePDFA2b,
    /** PDF/A-3a */
    CPDFTypePDFA3a,
    /** PDF/A-3u */
    CPDFTypePDFA3u,
    /** PDF/A-3b */
    CPDFTypePDFA3b
};

typedef NS_ENUM(NSInteger, CPDFStandardType) {
    CPDFStandardTypePDF = 0,
    /** PDF/A-1a */
    CPDFStandardTypePDFA1a,
    /** PDF/A-1b */
    CPDFStandardTypePDFA1b,
    /** PDF/A-2a */
    CPDFStandardTypePDFA2a,
    /** PDF/A-2u */
    CPDFStandardTypePDFA2u,
    /** PDF/A-2b */
    CPDFStandardTypePDFA2b,
    /** PDF/A-3a */
    CPDFStandardTypePDFA3a,
    /** PDF/A-3u */
    CPDFStandardTypePDFA3u,
    /** PDF/A-3b */
    CPDFStandardTypePDFA3b
};

typedef NS_ENUM(NSInteger, CPDFConvertLauguage) {
    CPDFConvertLauguageUnspecified = 0, // Czech Republic
    CPDFConvertLauguageCS_CZ, // Czech Republic
    CPDFConvertLauguageDE_DE, // Germany
    CPDFConvertLauguageEN_GB, // United Kingdom
    CPDFConvertLauguageEN_US, // United States
    CPDFConvertLauguageES_ES, // Spain
    CPDFConvertLauguageFI_FI, // Finland
    CPDFConvertLauguageFR_FR, // France
    CPDFConvertLauguageHU_HU, // Hungary
    CPDFConvertLauguageIT_IT, // Italy
    CPDFConvertLauguageJP_JP, // Japan
    CPDFConvertLauguageKO_KR, // South Korea
    CPDFConvertLauguageNL_BE, // Belgium
    CPDFConvertLauguageNL_NL, // Netherlands
    CPDFConvertLauguageNO_NO, // Norway
    CPDFConvertLauguagePL_PL, // Poland
    CPDFConvertLauguagePT_BR, // Brazil
    CPDFConvertLauguagePT_PT, // Portugal
    CPDFConvertLauguageRU_RU, // Russia
    CPDFConvertLauguageSK_SK, // Slovakia
    CPDFConvertLauguageSV_SE, // Sweden
    CPDFConvertLauguageTR_TR, // Turkey
    CPDFConvertLauguageZH_CN, // China
    CPDFConvertLauguageZH_TW, // Taiwan
    CPDFConvertLauguageZH_HK, // Hong Kong
    CPDFConvertLauguageZH_MO  // Macau
};

/**
 * Conformance part of a PDF standard.
 *
 * The ordering is stable and safe to persist.
 */
typedef NS_ENUM(NSInteger, CPDFPartType) {
    CPDFPartTypeNone,
    CPDFPartTypePDF_a,
    CPDFPartTypePDF_b,
    CPDFPartTypePDF_u,
};

/**
 * Family of a PDF standard.
 *
 * The ordering is stable and safe to persist.
 */
typedef NS_ENUM(NSInteger, CPDFStandardFormat) {
    CPDFStandardFormatPDF,
    CPDFStandardFormatPDFA,
    CPDFStandardFormatPDFX,
    CPDFStandardFormatPDFE,
    CPDFStandardFormatPDFUA,
    CPDFStandardFormatPDFVT
};

/**
 * Severity of a standard validation issue.
 */
typedef NS_ENUM(NSInteger, CPDFStandardValidationSeverity) {
    CPDFStandardValidationSeverityError = 0,
    CPDFStandardValidationSeverityWarning,
    CPDFStandardValidationSeverityInfo
};

/**
 * Kind of content a successful standard conversion removed or altered.
 */
typedef NS_ENUM(NSInteger, CPDFStandardConversionWarningType) {
    /** Annotations removed from a page (markup, stamps, links, ...). */
    CPDFStandardConversionWarningTypeAnnotationRemoved = 0,
    /** Interactive form fields or their widgets removed. */
    CPDFStandardConversionWarningTypeFormFieldRemoved,
    /** Page content removed (shadings, images, reference XObjects, ...). */
    CPDFStandardConversionWarningTypePageContentRemoved,
    /** Text made invisible because its font could not be embedded. */
    CPDFStandardConversionWarningTypeTextHidden,
    /** Transparency (soft masks, constant alpha, blend modes) removed. */
    CPDFStandardConversionWarningTypeTransparencyRemoved
};

typedef NS_ENUM(NSInteger, CPDFDocumentEncryptionLevel) {
    CPDFDocumentEncryptionLevelRC4 = 0,
    CPDFDocumentEncryptionLevelAES128,
    CPDFDocumentEncryptionLevelAES256,
    //If the encryption level is set to CPDFDocumentEncryptionLevelNoEncryptAlgo, it is equivalent to encrypting with the RC4 algorithm; if the document encryption level obtained is CPDFDocumentNoEncryptAlgo, it means that the document is not encrypted.
    CPDFDocumentEncryptionLevelNoEncryptAlgo
};

typedef NS_ENUM(NSInteger, CPDFSignaturePermissions) {
    CPDFSignaturePermissionsNone = 0,
    CPDFSignaturePermissionsForbidChange,
    CPDFSignaturePermissionsFillSign,
    CPDFSignaturePermissionsAnnotationFillSign,
};


#pragma mark - Standard conversion errors

/**
 * Error domain for PDF standard conversion failures.
 */
extern NSErrorDomain _Nonnull const CPDFStandardConversionErrorDomain;

/**
 * Why a standard conversion failed.
 *
 * `None` is not represented here because it never surfaces as an NSError.
 */
typedef NS_ERROR_ENUM(CPDFStandardConversionErrorDomain, CPDFStandardConversionError) {
    CPDFStandardConversionErrorInvalidInput = 1,
    CPDFStandardConversionErrorIccProfileMissing = 2,
    CPDFStandardConversionErrorUnsupportedFormat = 3,
    CPDFStandardConversionErrorFontOrUnicodeMapping = 4,
    CPDFStandardConversionErrorColorConversionUnsupported = 5,
    CPDFStandardConversionErrorStructureGenerationFailed = 6,
    CPDFStandardConversionErrorConversionFailed = 7,
    /** The conversion failed outside the core call (temporary copy, reload, or final save), so no core
        failure code exists. NSLocalizedFailureReasonErrorKey describes the failing step. */
    CPDFStandardConversionErrorUnknown = 100,
};

typedef NSString *CPDFDocumentOptimizeOption NS_STRING_ENUM;

extern CPDFDocumentOptimizeOption const CPDFDocumentImageQualityOption; // NSNumber for the image quality.

typedef NSString *CPDFDocumentAttribute NS_STRING_ENUM;

extern CPDFDocumentAttribute const CPDFDocumentTitleAttribute;             // NSString containing document title.
extern CPDFDocumentAttribute const CPDFDocumentAuthorAttribute;            // NSString containing document author.
extern CPDFDocumentAttribute const CPDFDocumentSubjectAttribute;           // NSString containing document title.
extern CPDFDocumentAttribute const CPDFDocumentCreatorAttribute;           // NSString containing name of app that created document.
extern CPDFDocumentAttribute const CPDFDocumentProducerAttribute;          // NSString containing name of app that produced PDF data.
extern CPDFDocumentAttribute const CPDFDocumentKeywordsAttribute;          // NSString containing document keywords.
extern CPDFDocumentAttribute const CPDFDocumentCreationDateAttribute;      // NSString representing document creation date.
extern CPDFDocumentAttribute const CPDFDocumentModificationDateAttribute;  // NSString representing last document modification date.

typedef NSString *CPDFDocumentWriteOption NS_STRING_ENUM;

extern CPDFDocumentWriteOption const CPDFDocumentOwnerPasswordOption;      // NSString for the owner's password.
extern CPDFDocumentWriteOption const CPDFDocumentUserPasswordOption;       // NSString for the user's password.
extern CPDFDocumentWriteOption const CPDFDocumentEncryptionLevelOption;

extern CPDFDocumentWriteOption const CPDFDocumentAllowsPrintingOption;
extern CPDFDocumentWriteOption const CPDFDocumentAllowsHighQualityPrintingOption;
extern CPDFDocumentWriteOption const CPDFDocumentAllowsCopyingOption;
extern CPDFDocumentWriteOption const CPDFDocumentAllowsDocumentChangesOption;
extern CPDFDocumentWriteOption const CPDFDocumentAllowsDocumentAssemblyOption;
extern CPDFDocumentWriteOption const CPDFDocumentAllowsCommentingOption;
extern CPDFDocumentWriteOption const CPDFDocumentAllowsFormFieldEntryOption;

@class CPDFPage, CPDFOutline, CPDFBookmark, CPDFWatermark, CPDFHeaderFooter, CPDFBates, CPDFBackground, CPDFSelection,CPDFSignature,CPDFSignatureWidgetAnnotation;

@protocol CPDFDocumentDelegate;

#pragma mark - CPDFStandardMode

/**
 * A PDF standard target, used both to report the standard a document already
 * conforms to and to request a conversion.
 *
 * The conformance level is expressed as the triple (format, typenum, partType) —
 * e.g. PDF/A-2b is (CPDFStandardFormatPDFA, 2, CPDFPartTypePDF_b).
 *
 * Supported conversion targets (format / typenum / partType):
 *
 *  - PDF/A-1a, 1b                 CPDFStandardFormatPDFA   1       a, b
 *  - PDF/A-2a, 2u, 2b             CPDFStandardFormatPDFA   2       a, u, b
 *  - PDF/A-3a, 3u, 3b             CPDFStandardFormatPDFA   3       a, u, b
 *  - PDF/X-1a, X-3, X-4           CPDFStandardFormatPDFX   1, 3, 4 None
 *  - PDF/E-1                      CPDFStandardFormatPDFE   1       None
 *  - PDF/UA-1                     CPDFStandardFormatPDFUA  1       None
 *  - PDF/VT-1, VT-2               CPDFStandardFormatPDFVT  1, 2    None
 *
 * Any other combination is rejected with CPDFStandardConversionErrorUnsupportedFormat.
 */
@interface CPDFStandardMode : NSObject

@property (nonatomic,assign) CPDFStandardFormat format;

@property (nonatomic,assign) NSInteger typenum;

@property (nonatomic,assign) CPDFPartType partType;

@end

#pragma mark - CPDFFontSubsetInfo

@interface CPDFFontSubsetInfo : NSObject

/**
 Font name
 */
@property (nonatomic,strong) NSString * _Nullable fontName;

/**
 Whether the font is embedded
 */
@property (nonatomic,assign) BOOL isEmmbeded;

/**
 Font Type
 */
@property (nonatomic,strong) NSString * _Nullable fontType;

/**
 Font encoding
 */
@property (nonatomic,strong) NSString * _Nullable fontEncoding;

/**
 Actual Font used
 */
@property (nonatomic,strong) NSString * _Nullable fontTrueName;

@end

#pragma mark - CPDFUAConfig

@interface CPDFUAConfig : NSObject

@property (nonatomic,assign) CPDFConvertLauguage lauguage;

@property (nonatomic,strong) NSString* title;

@end

#pragma mark - CPDFStandardConversionWarning

/**
 * Content a successful standard conversion removed or altered because the target standard does not allow it.
 */
@interface CPDFStandardConversionWarning : NSObject

@property (nonatomic,readonly) CPDFStandardConversionWarningType type;

/** Page the warning belongs to, or -1 when it is not tied to one page. */
@property (nonatomic,readonly) NSInteger pageIndex;

/** How many items this warning stands for; identical warnings are merged. */
@property (nonatomic,readonly) NSInteger count;

/** Human-readable description from the core library. May be empty. */
@property (nonatomic,readonly) NSString * _Nonnull message;

@end

#pragma mark - CPDFStandardValidationIssue

/**
 * A single rule violation (or note) reported by a standard validation.
 */
@interface CPDFStandardValidationIssue : NSObject

/** Numeric issue code reported by the core library. */
@property (nonatomic,readonly) NSInteger code;

/** Identifier of the violated rule, e.g. a clause of the standard. May be empty. */
@property (nonatomic,readonly) NSString * _Nonnull ruleId;

/** Human-readable description of the issue. */
@property (nonatomic,readonly) NSString * _Nonnull message;

/** Page the issue belongs to, or -1 when the issue applies to the whole document. */
@property (nonatomic,readonly) NSInteger pageIndex;

/** Name of the standard the rule belongs to. May be empty. */
@property (nonatomic,readonly) NSString * _Nonnull standardName;

@property (nonatomic,readonly) CPDFStandardValidationSeverity severity;

@end

#pragma mark - CPDFStandardValidationResult

/**
 * Result of validating a document against a PDF standard.
 */
@interface CPDFStandardValidationResult : NSObject

/** Whether the document conforms to the requested standard. */
@property (nonatomic,readonly) BOOL passed;

/**
 * The standard level the document declares, or nil when the document declares no level
 * or the validation does not report one (PDF/E, PDF/UA, PDF/VT).
 */
@property (nonatomic,readonly) CPDFStandardMode * _Nullable detectedType;

@property (nonatomic,readonly) NSArray<CPDFStandardValidationIssue *> * _Nonnull issues;

@end

/**
 * An object that represents a PDF file and defines methods for writing, searching, and selecting PDF data.
 *
 * @discussion The other utility classes are either instantiated from methods in CPDFDocument, as are CPDFPage and CPDFOutline; or support it, as do CPDFWatermark and CPDFDestination.
 * You initialize a CPDFDocument object with a URL to a PDF file. You can then ask for the page count, add or delete pages, perform a find, or parse selected content into an NSString object.
 */


@class CPDFPageDrawRectOptions;

@interface CPDFDocument : NSObject

#pragma mark - Initializers

/**
 * Initializes a CPDFDocument object with new PDF.
 */
- (instancetype)init;

/**
 * Initializes a CPDFDocument object with the contents at the specified URL.
 */
- (instancetype)initWithURL:(NSURL *)url;

#pragma mark - Accessors

/**
 * The object acting as the delegate for the CPDFDocument object.
 *
 * @see CPDFDocumentDelegate
 */
@property (nonatomic,weak) id<CPDFDocumentDelegate> delegate;

/**
 * The URL for the document.
 *
 * @discussion May return NULL if the document was created from an new object.
 */
@property (nonatomic,readonly) NSURL *documentURL;

/**
 * The password for the document.
 *
 * @discussion May return NULL if the document is not an encrypted document.
 */
@property (nonatomic,readonly) NSString *password;

/**
 * Error message for the document loading.
 *
 * @discussion To determine the error type, use the code to obtain error of type CPDFDocumentErrorDomain.
 * Except for the CPDFDocumentPasswordError error, other errors cannot open the document.
 * If CPDFDocumentPasswordError, reading the document requires a password.
 */
@property (nonatomic,readonly) NSError *error;

/**
 * A Boolean value specifying whether the document is encrypted.
 *
 * @discussion Whether the PDF is encrypted. With the right password, a PDF can be unlocked - nonetheless, the PDF still indicates that it is encrypted - just no longer locked.
 * Some PDF's may be encrypted but can be unlocked with the empty string. These are unlocked automatically.
 */
@property (nonatomic,readonly) BOOL isEncrypted;

/**
 * A Boolean value indicating whether the document is locked.
 *
 * @discussion Only encrypted documents can be locked. Use the unlockWithPassword: method to unlock a document using a password.
 */
@property (nonatomic,readonly) BOOL isLocked;

/**
 * A Boolean value indicating whether the document is image.
 */
- (BOOL)isImageDocument;

/**
 * Attempts to unlock an encrypted document.
 *
 * @discussion If the password is correct, this method returns YES, and a CPDFDocumentDidUnlockNotification notification is sent.
 * Once unlocked, you cannot use this function to relock the document.
 * @param password The password to unlock an encrypted document (you cannot lock an unlocked PDF document by using an incorrect password).
 */
- (BOOL)unlockWithPassword:(NSString *)password;

/**
 * Whether the owner password is correct.
 * @param password Owner password.
 * @return Whether the password is correct.
 *
 **/
- (BOOL)checkOwnerPassword:(NSString *)password;

/**
 * Whether the secured PDF document is unlocked.
 * @return Return the result of whether the secured PDF document is unlocked.
 */
- (BOOL)isCheckOwnerUnlocked;

/**
 * The major version of the document.
 *
 * @discussion PDF version of the PDF file (example: major version = 1; PDF v1.4).
 */
@property (nonatomic,readonly) NSInteger majorVersion;
/**
 * The minor version of the document.
 *
 * @discussion PDF version of the PDF file (example: minor version = 4; PDF v1.4).
 */
@property (nonatomic,readonly) NSInteger minorVersion;

/**
 * The permissions status of the PDF document.
 *
 * @discussion Returns the permissions status of the PDF document. You have CPDFDocumentPermissionsNone status for an encrypted
 * document that you have not supplied either a valid user or owner password. For a document with no encryption, you automatically have CPDFDocumentPermissionsUser status.
 * @see CPDFDocumentPermissions
 */
@property (nonatomic,readonly) CPDFDocumentPermissions permissionsStatus;

/**
 * A Boolean value indicating whether the document allows printing.
 */
@property (nonatomic,readonly) BOOL allowsPrinting;
/**
 * A Boolean value indicating whether the document allows printing in high fidelity.
 */
@property (nonatomic,readonly) BOOL allowsHighQualityPrinting;
/**
 * A Boolean value indicating whether the document allows copying of content to the Pasteboard.
 */
@property (nonatomic,readonly) BOOL allowsCopying;
/**
 * A Boolean value indicating whether you can modify the document contents except for document attributes.
 */
@property (nonatomic,readonly) BOOL allowsDocumentChanges;
/**
 * A Boolean value indicating whether you can manage a document by inserting, deleting, and rotating pages.
 */
@property (nonatomic,readonly) BOOL allowsDocumentAssembly;
/**
 * A Boolean value indicating whether you can create or modify document annotations, including form field entries.
 */
@property (nonatomic,readonly) BOOL allowsCommenting;
/**
 * A Boolean value indicating whether you can modify form field entries even if you can't edit document annotations.
 */
@property (nonatomic,readonly) BOOL allowsFormFieldEntry;


@property (nonatomic,readonly) CPDFDocumentEncryptionLevel encryptionLevel;

- (NSArray <CPDFFontSubsetInfo *>* _Nullable)getSubsetFontInfos;

#pragma mark - Save

/**
 * A Boolean value indicating whether the document has been modified.
 */
- (BOOL)isModified;

/**
 * Writes the document to a location specified by the passed-in URL.
 *
 * @discussion If the document contains a completed digital signature, it is saved incrementally:
 * the bytes it was opened from are kept unchanged and only the modifications are appended, so
 * existing signatures (including certification signatures) stay valid. An unmodified signed
 * document is written byte for byte. In that case `isSaveFontSubset` is ignored, because
 * subsetting fonts would require rewriting the whole file.
 */
- (BOOL)writeToURL:(NSURL *)url isSaveFontSubset:(BOOL)isSaveFontSubset;

/**
 * Writes the document to the specified URL with the specified options.
 *
 * @discussion Set the password to the document by setting options.
 * @param options CPDFDocumentOwnerPasswordOption, CPDFDocumentUserPasswordOption.
 */
- (BOOL)writeToURL:(NSURL *)url withOptions:(NSDictionary<CPDFDocumentWriteOption, id> *)options isSaveFontSubset:(BOOL)isSaveFontSubset;

/**
 * Writes the document to the specified URL after flattening.
 */
- (BOOL)writeFlattenToURL:(NSURL *)url isSaveFontSubset:(BOOL)isSaveFontSubset;

/**
 * Writes the document to the specified URL after removing annotions and form field entries.
 */
- (BOOL)writeContentToURL:(NSURL *)url isSaveFontSubset:(BOOL)isSaveFontSubset;

/**
 * Writes the document to the specified URL after removing permissions.
 */
- (BOOL)writeDecryptToURL:(NSURL *)url isSaveFontSubset:(BOOL)isSaveFontSubset;

#pragma mark - Compress

/// Compress File
///@discussion
/// @param
///     url
///         file to save url
///
/// @param
///     options
///         key1 : CPDFOptimizeCOLImageOptionKey
///         value1 : CPDFOptimizeImageOption (NSValue )
///         [NSValue valueWithBytes:&imageOption objCType:@encode(CPDFOptimizeImageOption)];
///         see CPDFOptimizeOption.h
///
///         key2 : CPDFOptimizeFlagKey
///         value2 : CPDF_OPTIMIZE_FLAG (NSNumber )
///         [NSNumber numberWithInt:CPDF_OPTIMIZE_FLAG]
///         see CPDFOptimizeOption.h
///
/// @param
///     progressHandler
///         progressHandler
///
/// @param
///     cancelHandler
///         cancelHandler
///
/// @param
///     completionHandler
///         completionHandler
///
/// ```
/// sample code :
///
///CPDF_OPTIMIZE_FLAG optimize_flag;
///CPDFOptimizeImageOption imageOption;
///
///optimize_flag = 0xFF | CPDFOPTIMIZE_FLAG_RMHIDERLAYER | CPDFOPTIMIZE_FLAG_RMUNUSEDTARGET | CPDFOPTIMIZE_FLAG_USEFLATE | CPDFOPTIMIZE_FLAG_FLAT_REPLACELZW | CPDFOPTIMIZE_FLAG_RMJSACTION | CPDFOPTIMIZE_FLAG_RMREPLACEIMAGE | CPDFOPTIMIZE_FLAG_OPTIMIZEPAGECONTENT;
///
///imageOption.uperPpi = 225;
///imageOption.targetPpi = 150;
///imageOption.compAlg = CPDFCOMP_ALG_JPEG2000;
///imageOption.quality = 40;
///imageOption.blockSize = 256;
///
///[self.pdfDocument writeOptimizeToURL:[NSURL fileURLWithPath:targetPath]
///                         withOptions:@{CPDFOptimizeCOLImageOptionKey:[NSValue valueWithBytes:&imageOption objCType:@encode(CPDFOptimizeImageOption)],
///                                       CPDFOptimizeFlagKey:[NSNumber numberWithInt:optimize_flag]}
///                     progressHandler:^(float cPageIndex, float totalPageIndex) {
///    if (self.cPageIndex != cPageIndex) {
///        self.cPageIndex = cPageIndex;
///        if (progressHandle) {
///            progressHandle(cPageIndex/totalPageIndex);
///        }
///    }
///}
///                       cancelHandler:^BOOL{
///    return self.hasCanceled;
///}
///                   completionHandler:^(BOOL finished) {
///    if (progressHandle) {
///        progressHandle(1.0);
///        sleep(0.01);
///    }
///    if (completeHandle) {
///        completeHandle(finished);
///    }
///}];
///```
- (void)writeOptimizeToURL:(NSURL *)url
       withOptimizeOptions:(NSDictionary *)options
           progressHandler:(void (^_Nullable)(float cPageIndex, float totalPageIndex))progressHandler
             cancelHandler:(BOOL (^_Nullable)(void))cancelHandler
         completionHandler:(void (^_Nullable)(BOOL finished))completionHandler;

#pragma mark - Memory Distribution

/**
 * Returns a memory distribution analysis for the current document.
 *
 * @discussion This method analyzes the space occupied by different element categories
 * (images, fonts, annotations, etc.) in this PDF document. Use the returned
 * CPDFDocumentMemoryDistribution object to query individual category sizes or the total size.
 * This is useful for understanding document composition before performing optimization.
 *
 * @return A CPDFDocumentMemoryDistribution instance, or nil if the analysis fails.
 *
 * @code
 * CPDFDocumentMemoryDistribution *distribution = [document memoryDistribution];
 * if (distribution) {
 *     uint32_t total = [distribution totalSize];
 *     uint32_t imageSize = [distribution sizeForCategory:CPDFMemoryDistributionCategoryImage];
 * }
 * @endcode
 */
- (nullable CPDFDocumentMemoryDistribution *)memoryDistribution;

#pragma mark - Attributes

/**
 * A dictionary of document metadata.
 *
 * @discussion Metadata is optional for PDF documents. The dictionary may be empty, or only some of the keys may have associated values.
 */
- (NSDictionary<CPDFDocumentAttribute, id> *)documentAttributes;
- (void)setDocumentAttributes:(NSDictionary<CPDFDocumentAttribute, id> *)documentAttributes;

#pragma mark - Outline

/**
 * The document’s root outline to a PDF outline object.
 *
 * @discussion When a PDF document is saved, the outline tree structure is written out to the destination PDF file.
 */
- (CPDFOutline *)outlineRoot;

/**
 * Create a root outline for the document.
 */
- (CPDFOutline *)setNewOutlineRoot;

#pragma mark - Bookmark

/**
 * A array of document’s bookmarks.
 */
- (NSArray<CPDFBookmark *> *)bookmarks;

- (void)bookmarksBlock:(void(^)(NSArray<CPDFBookmark *> *))block;
/**
 * Add a bookmark at the specified index number.
 *
 * @discussion Indexes are zero based. This method raises an exception if index is out of bounds.
 */
- (BOOL)addBookmark:(NSString *)label forPageIndex:(NSUInteger)pageIndex;
/**
 * Remove the bookmark at the specified index number.
 *
 * @discussion Indexes are zero based. This method raises an exception if index is out of bounds.
 */
- (BOOL)removeBookmarkForPageIndex:(NSUInteger)pageIndex;
/**
 * Returns the bookmark at the specified index number.
 *
 * @discussion Indexes are zero based. This method raises an exception if index is out of bounds.
 */
- (CPDFBookmark *)bookmarkForPageIndex:(NSUInteger)pageIndex;

- (void)bookmarkForPageIndex:(NSUInteger)pageIndex block:(void (^)(CPDFBookmark *bookmark))block;
#pragma mark - Watermark

/**
 * A array of document’s watermarks.
 */
- (NSArray<CPDFWatermark *> *)watermarks;
/**
 * Add a watermark.
 *
 * @param watermark A PDF watermark object.
 */
- (BOOL)addWatermark:(CPDFWatermark *)watermark;
/**
 * Remove the watermark.
 *
 * @param watermark The PDF watermark object from document’s watermarks.
 */
- (BOOL)removeWatermark:(CPDFWatermark *)watermark;
/**
 * Update the watermark.
 *
 * @param watermark The PDF watermark object from document’s watermarks.
 */
- (BOOL)updateWatermark:(CPDFWatermark *)watermark;

#pragma mark - HeaderFooter

/**
 * Gets the header & footer of the document.
 */
- (CPDFHeaderFooter *)headerFooter;

#pragma mark - Bates

/**
 * Gets the bates numbers of the document.
 */
- (CPDFBates *)bates;

#pragma mark - Background

/**
 * Gets the background of the document.
 */
- (CPDFBackground *)background;

#pragma mark - Signature

/**
 * Get the current signature list.
 */
- (NSArray<CPDFSignature *> *)signatures;

/**
 * Delete the corresponding signature
 */
- (void)removeSignature:(CPDFSignature *)signature;

/**
 * Two-phase ("deferred") signing, phase 1, against a signature field this document already
 * has — a template or form-designer PDF where the field is already placed and signing must
 * fill *that* field. No private key is involved: the returned hash goes to an HSM, UKey,
 * cloud KMS or signing service, and phase 2 writes what comes back.
 *
 * `+[CPDFDeferredSignSession prepareWithDocument:sourceData:options:]` covers the other
 * case: it creates the field itself, and refuses a name that is already taken. Both paths
 * converge after phase 1 — the result carries the same `session` string, and both
 * `+[CPDFDeferredSignSession fillSession:…]` methods work on it unchanged. See
 * CPDFDeferredSignSession.h for the rest of the flow.
 *
 * The two settings that apply are parameters rather than a `CPDFDeferredSignPrepareOptions`
 * object, because the field already exists: its name, page and rectangle are fixed, and the
 * CMS attributes of `SignedAttributes` mode are built only when the field is created. An
 * options object here would be eight properties that quietly do nothing.
 *
 * @warning The receiver must be the document loaded from exactly these `sourceData` bytes,
 * and `signatureWidget` must belong to it.
 *
 * @warning The call modifies the receiver in memory. Do not save it afterwards.
 *
 * Requires the digital-signature license. Phase 2 does not re-check it.
 *
 * @param signatureWidget An unsigned signature field of this document. One that already
 * carries a signature is rejected with `sdk.field_already_signed`.
 * @param sourceData The bytes this document was loaded from.
 * @param digestAlgorithm Digest applied to the `/ByteRange` bytes. The external signer must
 * use this same one; it is reported back in the result's `digestAlgorithm`.
 * @param estimatedContentsSize `/Contents` placeholder capacity in container bytes; 0
 * selects the default of 16384. Frozen once this returns — a container that does not fit
 * cannot be filled in, and the only remedy is to prepare again with a larger value.
 *
 * @return Never nil; failure is reported through `errorCode` / `errorMessage`. On success,
 * `preparedData` and `session` must both be kept — phase 2 needs them.
 */
- (CPDFDeferredSignPrepareResult *)prepareDeferredSignForSignatureWidget:(CPDFSignatureWidgetAnnotation *)signatureWidget
                                                              sourceData:(NSData *)sourceData
                                                         digestAlgorithm:(CPDFSignatureDigestAlgorithm)digestAlgorithm
                                                   estimatedContentsSize:(NSInteger)estimatedContentsSize;


/**
     * Add a signature to a document.
     * @param url Save path for the signature file.
     * @param widget Signature widget.
     * @param path Certificate file path.
     * @param password Certificate file password
     * @param location The hostname or physical location of the CPU which was used to sign the document.
     * @param reason Signature reason.
     * @param Whether to set dynamic appearance
     * @param type Modify permission type. See more types by CPDFSignaturePermissions
     * @return Return true: Write signature successfully. Return false: Write signature failed.
*/
- (BOOL)writeSignatureToURL:(NSURL *_Nonnull)url
                 withWidget:(CPDFSignatureWidgetAnnotation *_Nonnull)widget
                 PKCS12Cert:(NSString *_Nonnull)path
                   password:(NSString *_Nonnull)password
                   location:(NSString *_Nullable)location
                     reason:(NSString *_Nullable)reason
                isSetSignAp:(BOOL)isSetSignAp
                permissions:(CPDFSignaturePermissions)permissions;

/**
     * Add a signature to a document, optionally timestamping it through an RFC 3161 TSA.
     *
     * @param url Save path for the signature file.
     * @param widget Signature widget.
     * @param path Certificate file path.
     * @param password Certificate file password
     * @param location The hostname or physical location of the CPU which was used to sign the document.
     * @param reason Signature reason.
     * @param isSetSignAp Whether to set dynamic appearance
     * @param permissions Modify permission type. See more types by CPDFSignaturePermissions
     * @param tsaClient The timestamp transport. Pass `nil` to sign without a timestamp,
     *        which is what the variant without this parameter does. Use
     *        `CPDFURLSessionTSAClient` unless you have a reason not to — it keeps the
     *        request inside `NSURLSession` and therefore inside App Transport Security
     *        and the system proxy configuration.
     * @return Return true: Write signature successfully. Return false: Write signature failed.
     *
     * @warning `tsaClient` is called back **synchronously, on the framework's task queue**
     * while the signature is being built. See `CPDFTSAClient`.
*/
- (BOOL)writeSignatureToURL:(NSURL *_Nonnull)url
                 withWidget:(CPDFSignatureWidgetAnnotation *_Nonnull)widget
                 PKCS12Cert:(NSString *_Nonnull)path
                   password:(NSString *_Nonnull)password
                   location:(NSString *_Nullable)location
                     reason:(NSString *_Nullable)reason
                isSetSignAp:(BOOL)isSetSignAp
                permissions:(CPDFSignaturePermissions)permissions
                  tsaClient:(nullable id<CPDFTSAClient>)tsaClient;

#pragma mark - Pages

/**
 * The number of pages in the document.
 */
@property (nonatomic,readonly) NSUInteger pageCount;

/**
 * Returns the page size at the specified index number.
 *
 * @discussion Indexes are zero based. This method raises an exception if index is out of bounds.
 */
- (CGSize)pageSizeAtIndex:(NSUInteger)index;

/**
 * Returns a CPDFPage object representing the page at index.
 *
 * @discussion Indexes are zero based. This method raises an exception if index is out of bounds.
 */
- (CPDFPage *)pageAtIndex:(NSUInteger)index;

/**
 * Gets the index number for the specified page.
 *
 * @discussion Given a CPDFPage, returns the pages index within the document. Indices are zero-based.
 */
- (NSUInteger)indexForPage:(CPDFPage *)page;

/**
 * Inserts a blank page at the specified index point.
 *
 * @discussion Indexes are zero based. The index must lie within bounds, or be equal to the length of bounds.
 */
- (BOOL)insertPage:(CGSize)pageSize atIndex:(NSUInteger)index;
/**
 * Inserts a blank page with image at the specified index point.
 *
 * @discussion Indexes are zero based. The index must lie within bounds, or be equal to the length of bounds.
 */
- (BOOL)insertPage:(CGSize)pageSize withImage:(NSString *)imagePath atIndex:(NSUInteger)index;
/**
 * Removes page(s) at the specified index set.
 */
- (BOOL)removePageAtIndexSet:(NSIndexSet *)indexSet;
/**
 * Move one page to another.
 *
 * @discussion This method raises an exception if either index value is out of bounds.
 */
- (BOOL)movePageAtIndex:(NSUInteger)indexA withPageAtIndex:(NSUInteger)indexB;
/**
 * Exchanges one page with another.
 *
 * @discussion This method raises an exception if either index value is out of bounds.
 */
- (BOOL)exchangePageAtIndex:(NSUInteger)indexA withPageAtIndex:(NSUInteger)indexB;
/**
 * Import page(s) from another document at the specified index point.
 *
 * @discussion This method raises an exception if either index value is out of bounds.
 */
- (BOOL)importPages:(NSIndexSet *)indexSet fromDocument:(CPDFDocument *)document atIndex:(NSUInteger)index;

/**
 * Adds a page from another document at the specified index.
 *
 * @param page The source page to add (must be from a different document).
 * @param index The zero-based index at which to insert the page.
 * @return YES if the page was added successfully, NO otherwise.
 *
 * @discussion This method uses the underlying Document::AddPage API to insert
 *             a page from another document without requiring PDFPage copying.
 *             The index must be within bounds (0 to pageCount).
 */
- (BOOL)addPage:(CPDFPage *)page atIndex:(NSUInteger)index;

- (CPDFKitPlatformImage *_Nullable)exportImageWithPages:(NSIndexSet *_Nonnull)indexSet maxImageSize:(NSUInteger)maxImageSize pageDrawRectOptions:(CPDFPageDrawRectOptions *)pageDrawRectOptions;

/**
 * Retrieve the page data
 */
- (void)refreshPageData;
#pragma mark - Annotations

/**
 * Export annotation to XFDF document.
 */
- (BOOL)exportAnnotationToXFDFPath:(NSString *)xfdfPath;
/**
 * Import annotations from XFDF document.
 */
- (BOOL)importAnnotationFromXFDFPath:(NSString *)xfdfPath;

/**
 * Remove all signatures.
 */
- (BOOL)removeAllSignature;

/**
 * A Boolean value indicating whether the document contains annotations.
 */
- (BOOL)hasAnnotations;

#pragma mark - Form

/**
 * Export form to XFDF document.
 */
- (BOOL)exportToXFDFPath:(NSString *)xfdfPath;
/**
 * Import form from XFDF document.
 */
- (BOOL)importFormFromXFDFPath:(NSString *)xfdfPath;

/**
 * Reset all forms in PDF document.
 */
- (void)resetForm;

#pragma mark - Extract

/**
 * Extract image at the specified index set.
 */
- (NSUInteger)extractImageFromPages:(NSIndexSet *)indexSet toPath:(NSString *)path;

/**
 * Cancels a extract initiated with extractImageFromPages:toPath:.
 */
- (void)cancelExtractImage;

#pragma mark - Summary

- (NSString *)summaryHTML;

#pragma mark - PDF/Convert

- (CPDFConvertLauguage)convertLauguage;

- (CPDFStandardMode *_Nonnull)standardType;

- (BOOL)writeStandardPDFToFilePath:(NSString * _Nonnull)saveFilePath
                          withType:(CPDFStandardMode *_Nonnull)type
                       iccFilePath:(NSString * _Nullable)iccFilePath
                      withUAConfig:(CPDFUAConfig* _Nullable)pdfUAConfig
                  isSaveFontSubset:(BOOL)isSaveFontSubset;

/**
 * Converts the document to a PDF standard, reporting why the conversion failed.
 *
 * @discussion Behaves exactly like writeStandardPDFToFilePath:withType:iccFilePath:withUAConfig:isSaveFontSubset:
 * but, on failure, populates `error` with a CPDFStandardConversionErrorDomain error
 * instead of returning a bare NO. The reason is carried in NSLocalizedFailureReasonErrorKey:
 * it comes from the core library for conversion failures, and from the wrapper for invalid
 * input (empty path, missing destination directory, locked document, empty PDF/UA title)
 * and for failures outside the core call.
 *
 * @param type The target standard. Must be one of the combinations listed on CPDFStandardMode.
 * @param error On return, the reason the conversion failed. Pass NULL if not needed.
 */
- (BOOL)writeStandardPDFToFilePath:(NSString * _Nonnull)saveFilePath
                          withType:(CPDFStandardMode *_Nonnull)type
                       iccFilePath:(NSString * _Nullable)iccFilePath
                      withUAConfig:(CPDFUAConfig* _Nullable)pdfUAConfig
                  isSaveFontSubset:(BOOL)isSaveFontSubset
                             error:(NSError * _Nullable * _Nullable)error;

/**
 * What the most recent successful writeStandardPDFToFilePath: call on this document removed or altered
 * in the output, e.g. annotations or form fields the target standard does not allow.
 *
 * @discussion Empty when the conversion changed nothing, failed, or has not been run.
 * The source document itself is never modified.
 */
@property (nonatomic,readonly) NSArray<CPDFStandardConversionWarning *> * _Nonnull standardConversionWarnings;

#pragma mark - PDF/Validation

/**
 * Validates the document against a PDF standard.
 *
 * @discussion This is a basic rule check, not a full certification equivalent to a
 * third-party validator. PDF/X, PDF/UA and PDF/VT validation are experimental
 * and may be incomplete.
 *
 * Supported targets (format / typenum / partType):
 *
 *  - PDF/A-1a, 1b                 CPDFStandardFormatPDFA   1       a, b
 *  - PDF/A-2a, 2u, 2b             CPDFStandardFormatPDFA   2       a, u, b
 *  - PDF/A-3a, 3u, 3b             CPDFStandardFormatPDFA   3       a, u, b
 *  - PDF/X-1a, X-3, X-4           CPDFStandardFormatPDFX   1, 3, 4 None
 *  - PDF/E-1, E-2                 CPDFStandardFormatPDFE   1, 2    None
 *  - PDF/UA                       CPDFStandardFormatPDFUA  ignored None
 *  - PDF/VT                       CPDFStandardFormatPDFVT  ignored None
 *
 * PDF/VT checks the VT level the document declares.
 *
 * @param type The standard to validate against.
 * @param basePath Directory used to resolve externally referenced files. Only used for PDF/X; may be nil.
 * @return The validation result, or nil if the document is not loaded, the document is locked,
 * the target is not supported, or the license does not allow PDF/A conversion.
 */
- (CPDFStandardValidationResult * _Nullable)validateStandardPDFWithType:(CPDFStandardMode * _Nonnull)type
                                                               basePath:(NSString * _Nullable)basePath;

#pragma mark - Find

/**
 * Returns a Boolean value indicating whether an asynchronous find operation is in progress.
 */
@property (nonatomic,readonly) BOOL isFinding;

/**
 * Synchronously finds all instances of the specified string in the document.
 *
 * @discussion Each hit gets added to an NSArray object as a CPDFSelection object. If there are no hits, this method returns an empty array.
 * Use this method when the complete search process will be brief and when you don’t need the flexibility or control offered by beginFindString:withOptions:.
 * @see CPDFSearchOptions
 */
- (NSArray<NSArray<CPDFSelection *> *> *)findString:(NSString *)string withOptions:(CPDFSearchOptions)options completionHandler:(void (^_Nullable)(NSInteger currentPageIndex))handler;

/**
 * Asynchronously finds all instances of the specified string in the document.
 *
 * @discussion This method returns immediately. It causes delegate methods to be called when searching begins and ends, on each search hit, and when the search proceeds to a new page.
 * @see CPDFDocumentDelegate
 */
- (void)beginFindString:(NSString *)string withOptions:(CPDFSearchOptions)options;

/**
 * Cancels a search initiated with beginFindString:withOptions:.
 */
- (void)cancelFindString;

/**
 * Synchronously finds all instances of the specified string in the document.
 *
 * @discussion Each hit gets added to an NSArray object as a CPDFSelection object. If there are no hits, this method returns an empty array.
 * Call only in Content Editing
 * @see CPDFSearchOptions
 */
- (NSArray<NSArray<CPDFSelection *> *> *_Nullable)findEditAllPageString:(NSString *_Nonnull)string withOptions:(CPDFSearchOptions)options completionHandler:(void (^_Nullable)(NSInteger currentPageIndex))handler;

/**
 * Synchronously finds all instances of the specified string in the document.
 *
 * @discussion Each hit gets added to an NSArray object as a CPDFSelection object. If there are no hits, this method returns an empty array.
 * @param indexSet A collection of page numbers to search
 * Call only in Content Editing
 * @see CPDFSearchOptions
 */
- (NSArray<NSArray<CPDFSelection *> *> *_Nullable)findEditFindPages:(NSIndexSet *_Nonnull)indexSet withString:(NSString *_Nonnull)string withOptions:(CPDFSearchOptions)options;

/**
 * Synchronously finds all instances of the specified string in the document.
 *
 * @discussion Each hit gets added to an NSArray object as a CPDFSelection object. If there are no hits, this method returns an empty array.
 * @param currentPage Which page to start with
 * Call only in Content Editing
 * @see CPDFSearchOptions
 */
- (NSArray<NSArray<CPDFSelection *> *> *_Nullable)startFindEditTextFromPage:(CPDFPage *_Nullable)currentPage withString:(NSString *_Nonnull)string options:(CPDFSearchOptions)options;

/**
 * Search result
 * Call only in Content Editing
 */
- (NSArray<NSArray<CPDFSelection *> *> *_Nullable)findEditSelections;

/**
 * Previous result
 * Call only in Content Editing
 */
- (CPDFSelection *_Nullable)findForwardEditText;

/**
 * Next result
 * Call only in Content Editing
 */
- (CPDFSelection *_Nullable)findBackwordEditText;

/**
 * Cancels a search initiated with findEditFindPages:
 * Call only in Content Editing
 */
- (void)cancelFindEditString;

/**
 * Replace the content edit by specifying selection
 * param selection Replaces the specified selection
 * param searchString Searched character
 * param replaceString Replace character
 * get newSelection The replacement results in a new selection
 * @see CPDFSearchOptions
 */
- (BOOL)replaceWithSelection:(CPDFSelection *_Nonnull)selection searchString:(NSString *_Nonnull)searchString toReplaceString:(NSString *_Nullable)replaceString completionHandler:(void (^_Nullable)(CPDFSelection * _Nullable newSelection))handler;

/**
 * Replace all search results
 * Call only in Content Editing
 */
- (BOOL)replaceAllEditTextWithString:(NSString *_Nonnull)string toReplaceString:(NSString *_Nullable)replaceString;


#pragma mark - Redact

/**
 * Applies redaction annotations in the document.
 */
- (void)applyRedactions;

@end

#pragma mark - Attachments (Document-level embedded files)

@class CPDFAttachment;

/**
 * Document-level file attachments, i.e. the entries of the document's /EmbeddedFiles name tree.
 *
 * @discussion Attachments are ordered by name in the PDF name tree, so adding or removing an
 * attachment can shift the indexes of the others. Re-fetch `attachments` after any add/remove.
 */
@interface CPDFDocument (Attachment)

/**
 * The number of document-level attachments.
 */
@property (nonatomic, readonly) NSUInteger attachmentCount;

/**
 * Returns all document-level attachments, in index order.
 */
- (NSArray<CPDFAttachment *> *_Nonnull)attachments;

/**
 * Returns the attachment at the specified index, or nil if the index is out of bounds.
 *
 * @discussion Indexes are zero based.
 */
- (CPDFAttachment *_Nullable)attachmentAtIndex:(NSUInteger)index;

/**
 * Embeds a file from disk as a document-level attachment.
 *
 * @param path The full path of the file to embed. Must be an existing, readable regular file.
 * @param name The attachment file name. If nil or empty, `path.lastPathComponent` is used.
 * @return The new attachment, or nil if failed (e.g. invalid path, or an attachment with the same name already exists).
 */
- (CPDFAttachment *_Nullable)addAttachmentWithPath:(NSString *_Nonnull)path name:(NSString *_Nullable)name;

/**
 * Embeds in-memory data as a document-level attachment.
 *
 * @param data The file content.
 * @param name The attachment file name. Must not be empty.
 * @return The new attachment, or nil if failed (e.g. an attachment with the same name already exists).
 */
- (CPDFAttachment *_Nullable)addAttachmentWithData:(NSData *_Nonnull)data name:(NSString *_Nonnull)name;

/**
 * Removes the attachment at the specified index.
 *
 * @discussion Indexes are zero based. The indexes of the following attachments shift down by one.
 * @return YES if succeeded; NO if the index is out of bounds or the removal failed.
 */
- (BOOL)removeAttachmentAtIndex:(NSUInteger)index;

/**
 * Removes the specified attachment. On success the attachment object becomes invalid.
 *
 * @return YES if succeeded; NO if the attachment does not belong to this document or the removal failed.
 */
- (BOOL)removeAttachment:(CPDFAttachment *_Nonnull)attachment;

@end

/**
 * The delegate for the CPDFDocument object.
 */
@protocol CPDFDocumentDelegate <NSObject>

@optional

/**
 * Called when the beginFindString:withOptions: or findString:withOptions: method begins finding.
 */
- (void)documentDidBeginDocumentFind:(CPDFDocument *)document;
/**
 * Called when the beginFindString:withOptions: or findString:withOptions: method returns.
 */
- (void)documentDidEndDocumentFind:(CPDFDocument *)document;
/**
 * Called when a find operation begins working on a new page of a document.
 */
- (void)documentDidBeginPageFind:(CPDFDocument *)document pageAtIndex:(NSUInteger)index;
/**
 * Called when a find operation finishes working on a page in a document.
 */
- (void)documentDidEndPageFind:(CPDFDocument *)document pageAtIndex:(NSUInteger)index;
/**
 * Called when a string match is found in a document.
 *
 * @discussion To determine the string selection found, use the selection.
 */
- (void)documentDidFindMatch:(CPDFSelection *)selection;

@end

@interface CPDFDocument (Deprecated)

- (BOOL)writeSignatureToURL:(NSURL *)url
                 withWidget:(CPDFSignatureWidgetAnnotation *)widget
                 PKCS12Cert:(NSString *)path
                   password:(NSString *)password
                   location:(NSString *)location
                     reason:(NSString *)reason
                permissions:(CPDFSignaturePermissions)permissions DEPRECATED_MSG_ATTRIBUTE("Use writeSignatureToURL:withWidget:PKCS12Cert:location:reason:permissions:");

- (void)writeOptimizeToURL:(NSURL *)url
               withOptions:(NSDictionary<CPDFDocumentOptimizeOption, id> *)options
           progressHandler:(void (^_Nullable)(float cPageIndex, float totalPageIndex))progressHandler
             cancelHandler:(BOOL (^_Nullable)(void))cancelHandler
         completionHandler:(void (^_Nullable)(BOOL finished))completionHandler; DEPRECATED_MSG_ATTRIBUTE("Use writeOptimizeToURL:withOptimizeOptions:progressHandler:cancelHandler:completionHandler:");

- (BOOL)writeOptimizeToURL:(NSURL *)url withOptions:(NSDictionary<CPDFDocumentOptimizeOption, id> *)options DEPRECATED_MSG_ATTRIBUTE("Use writeOptimizeToURL:withOptions:progressHandler:cancelHandler:completionHandler:");

- (BOOL)writeToURL:(NSURL *)url DEPRECATED_MSG_ATTRIBUTE("Use writeToURL:isSaveFontSubset:");

- (BOOL)writeToURL:(NSURL *)url withOptions:(NSDictionary<CPDFDocumentWriteOption, id> *)options DEPRECATED_MSG_ATTRIBUTE("Use writeToURL:withOptions:isSaveFontSubset:");

- (BOOL)writeFlattenToURL:(NSURL *)url DEPRECATED_MSG_ATTRIBUTE("Use writeFlattenToURL:isSaveFontSubset:");

- (BOOL)writeContentToURL:(NSURL *)url DEPRECATED_MSG_ATTRIBUTE("Use writeContentToURL:isSaveFontSubset:");

- (BOOL)writeDecryptToURL:(NSURL *)url DEPRECATED_MSG_ATTRIBUTE("Use writeDecryptToURL:isSaveFontSubset:");

- (BOOL)writePDFAToURL:(NSURL *)url withType:(CPDFType)type DEPRECATED_MSG_ATTRIBUTE("Use writePDFAToURL:withType:isSaveFontSubset:");


- (NSArray<NSArray<CPDFSelection *> *> *)findString:(NSString *)string withOptions:(CPDFSearchOptions)options DEPRECATED_MSG_ATTRIBUTE("Use findString:withOptions:completionHandler:");

- (void)findEditString:(NSString *)string withOptions:(CPDFSearchOptions)options DEPRECATED_MSG_ATTRIBUTE("Use findEditAllPageString:withOptions:");

- (void)findEditString:(NSString *)string findPages:(NSIndexSet *)indexSet withOptions:(CPDFSearchOptions)options DEPRECATED_MSG_ATTRIBUTE("Use findEditFindPages:withString:withOptions:");

- (CPDFSelection *)startFindEditTextWithCurrentPage:(CPDFPage *)currentPage withString:(NSString *)string withOptions:(CPDFSearchOptions)options DEPRECATED_MSG_ATTRIBUTE("Use startFindEditTextFromPage:withString:options:");

- (CPDFSelection *)findNextEditTextWithLastlection:(CPDFSelection *)lastSelection withString:(NSString *)string withOptions:(CPDFSearchOptions)options DEPRECATED_MSG_ATTRIBUTE("Use findBackwordEditText:");

- (CPDFSelection *)findPrevEditTextWithLastlection:(CPDFSelection *)lastSelection withString:(NSString *)string withOptions:(CPDFSearchOptions)options DEPRECATED_MSG_ATTRIBUTE("Use findForwardEditText:");

/**
 * Gets PDF/A conformance levels.
 *
 * @see CPDFType
 */
- (CPDFType)type DEPRECATED_MSG_ATTRIBUTE("Use standardType");

/**
 * Converts existing PDF files to PDF/A compliant documents, including PDF/A-1a and PDF/A-1b only.
 *
 * @discussion The conversion option analyzes the content of existing PDF files and performs a sequence of modifications in order to produce a PDF/A compliant document.
 * Features that are not suitable for long-term archiving (such as encryption, obsolete compression schemes, missing fonts, or device-dependent color) are replaced with their PDF/A compliant equivalents.
 * Because the conversion process applies only necessary changes to the source file, the information loss is minimal.
 * @see CPDFType
 */
- (BOOL)writePDFAToURL:(NSURL *)url withType:(CPDFType)type isSaveFontSubset:(BOOL)isSaveFontSubset DEPRECATED_MSG_ATTRIBUTE("Use writeStandardPDFToFilePath:withType:iccFilePath:withUAConfig:isSaveFontSubset:");

@end
