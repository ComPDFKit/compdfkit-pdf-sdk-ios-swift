//
//  CPDFDocument.h
//  ComPDFKit
//
//  Copyright © 2014-2024 PDF Technologies, Inc. All Rights Reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE ComPDFKit LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <ComPDFKit/CPDFKitPlatform.h>

extern NSNotificationName const CPDFDocumentDidUnlockNotification;

extern NSNotificationName const CPDFDocumentPageCountChangedNotification;

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

/**
 * An object that represents a PDF file and defines methods for writing, searching, and selecting PDF data.
 *
 * @discussion The other utility classes are either instantiated from methods in CPDFDocument, as are CPDFPage and CPDFOutline; or support it, as do CPDFWatermark and CPDFDestination.
 * You initialize a CPDFDocument object with a URL to a PDF file. You can then ask for the page count, add or delete pages, perform a find, or parse selected content into an NSString object.
 */
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
@property (nonatomic,assign) id<CPDFDocumentDelegate> delegate;

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

#pragma mark - Save

/**
 * A Boolean value indicating whether the document has been modified.
 */
- (BOOL)isModified;

/**
 * Writes the document to a location specified by the passed-in URL.
 */
- (BOOL)writeToURL:(NSURL *)url;

/**
 * Writes the document to the specified URL with the specified options.
 *
 * @discussion Set the password to the document by setting options.
 * @param options CPDFDocumentOwnerPasswordOption, CPDFDocumentUserPasswordOption.
 */
- (BOOL)writeToURL:(NSURL *)url withOptions:(NSDictionary<CPDFDocumentWriteOption, id> *)options;

/**
 * Writes the document to the specified URL after flattening.
 */
- (BOOL)writeFlattenToURL:(NSURL *)url;

/**
 * Writes the document to the specified URL after removing annotions and form field entries.
 */
- (BOOL)writeContentToURL:(NSURL *)url;

/**
 * Writes the document to the specified URL after removing permissions.
 */
- (BOOL)writeDecryptToURL:(NSURL *)url;

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
     * Add a signature to a document.
     * @param url Save path for the signature file.
     * @param widget Signature widget.
     * @param path Certificate file path.
     * @param password Certificate file password
     * @param location The hostname or physical location of the CPU which was used to sign the document.
     * @param reason Signature reason.
     * @param type Modify permission type. See more types by CPDFSignaturePermissions
     * @return Return true: Write signature successfully. Return false: Write signature failed.
*/
- (BOOL)writeSignatureToURL:(NSURL *)url
                 withWidget:(CPDFSignatureWidgetAnnotation *)widget
                 PKCS12Cert:(NSString *)path
                   password:(NSString *)password
                   location:(NSString *)location
                     reason:(NSString *)reason
                permissions:(CPDFSignaturePermissions)permissions;

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

#pragma mark - PDF/A

/**
 * Gets PDF/A conformance levels.
 *
 * @see CPDFType
 */
- (CPDFType)type;

/**
 * Converts existing PDF files to PDF/A compliant documents, including PDF/A-1a and PDF/A-1b only.
 *
 * @discussion The conversion option analyzes the content of existing PDF files and performs a sequence of modifications in order to produce a PDF/A compliant document.
 * Features that are not suitable for long-term archiving (such as encryption, obsolete compression schemes, missing fonts, or device-dependent color) are replaced with their PDF/A compliant equivalents.
 * Because the conversion process applies only necessary changes to the source file, the information loss is minimal.
 * @see CPDFType
 */
- (BOOL)writePDFAToURL:(NSURL *)url withType:(CPDFType)type;

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
- (NSArray<NSArray<CPDFSelection *> *> *)findString:(NSString *)string withOptions:(CPDFSearchOptions)options;

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
- (NSArray<NSArray<CPDFSelection *> *> *_Nullable)findEditAllPageString:(NSString *_Nonnull)string withOptions:(CPDFSearchOptions)options;

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

- (void)findEditString:(NSString *)string withOptions:(CPDFSearchOptions)options DEPRECATED_MSG_ATTRIBUTE("Use findEditAllPageString:withOptions:");

- (void)findEditString:(NSString *)string findPages:(NSIndexSet *)indexSet withOptions:(CPDFSearchOptions)options DEPRECATED_MSG_ATTRIBUTE("Use findEditFindPages:withString:withOptions:");

- (CPDFSelection *)startFindEditTextWithCurrentPage:(CPDFPage *)currentPage withString:(NSString *)string withOptions:(CPDFSearchOptions)options DEPRECATED_MSG_ATTRIBUTE("Use startFindEditTextFromPage:withString:options:");

- (CPDFSelection *)findNextEditTextWithLastlection:(CPDFSelection *)lastSelection withString:(NSString *)string withOptions:(CPDFSearchOptions)options DEPRECATED_MSG_ATTRIBUTE("Use findBackwordEditText:");

- (CPDFSelection *)findPrevEditTextWithLastlection:(CPDFSelection *)lastSelection withString:(NSString *)string withOptions:(CPDFSearchOptions)options DEPRECATED_MSG_ATTRIBUTE("Use findForwardEditText:");

@end
