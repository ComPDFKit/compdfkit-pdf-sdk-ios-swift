//
//  CPDFAttachment.h
//  ComPDFKit
//
//  Copyright © 2014-2026 PDF Technologies, Inc. All Rights Reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE ComPDFKit LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class CPDFDocument;

/**
 * A CPDFAttachment object represents a document-level embedded file, i.e. an entry of the
 * document's /EmbeddedFiles name tree (also known as a "file attachment" of the document).
 *
 * @discussion Obtain instances from `-[CPDFDocument attachments]`, `-[CPDFDocument attachmentAtIndex:]`
 * or the `-[CPDFDocument addAttachmentWithPath:name:]` family. Do not create instances directly.
 *
 * Attachments are ordered by name inside the PDF name tree, so adding or removing an attachment can
 * shift the index of other attachments. An existing object tries to relocate itself by name before
 * each operation, but callers should re-fetch `-[CPDFDocument attachments]` after any add/remove.
 *
 * The metadata properties (`name`, `fileDescription`, `mimeType`, `size`) are a snapshot taken when the
 * object was created, refreshed after mutations made through this object.
 *
 * Once an attachment has been removed from its document, the object becomes invalid: `index` returns
 * `NSNotFound` and every operation returns NO or nil.
 */
@interface CPDFAttachment : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/**
 * The document that owns the attachment.
 */
@property (nonatomic, readonly, weak, nullable) CPDFDocument *document;

/**
 * The zero-based index of the attachment in the document's embedded-file list, or `NSNotFound`
 * if the attachment has been removed or can no longer be located.
 */
@property (nonatomic, readonly) NSUInteger index;

/**
 * The file name of the attachment (the /UF or /F entry of the file specification).
 */
@property (nonatomic, readonly, nullable) NSString *name;

/**
 * The description of the attachment (the /Desc entry of the file specification).
 *
 * @discussion Setting this property writes the new value into the PDF. If the write fails the
 * property keeps its previous value. Setting nil stores an empty description.
 */
@property (nonatomic, copy, nullable) NSString *fileDescription;

/**
 * The MIME type of the embedded file (the /Subtype entry of the embedded file stream), or nil
 * when the PDF does not specify one. Attachments added by this SDK have no MIME type.
 */
@property (nonatomic, readonly, nullable) NSString *mimeType;

/**
 * The size in bytes of the decoded embedded file content.
 */
@property (nonatomic, readonly) unsigned long long size;

/**
 * Returns the decoded content of the embedded file.
 *
 * @return The file content, an empty data object for an empty file, or nil if the attachment is invalid.
 */
- (nullable NSData *)data;

/**
 * Writes the decoded content of the embedded file to a target path.
 *
 * @param path The full destination file path. An existing file is overwritten.
 * @return YES if succeeded.
 */
- (BOOL)writeToPath:(NSString *)path;

/**
 * Replaces the content of the embedded file.
 *
 * @discussion The embedded file stream is rebuilt, so its parameter dictionary is reset to
 * /Size, /CreationDate, /ModDate and /CheckSum: custom values previously set with
 * `-setStringValue:forKey:` and the MIME type are discarded.
 *
 * @param data The new file content.
 * @return YES if succeeded.
 */
- (BOOL)setData:(NSData *)data;

/**
 * Returns whether the embedded file parameter dictionary (/Params) contains the given key.
 *
 * @param key The dictionary key, without the leading slash (e.g. @"Size", @"CheckSum").
 */
- (BOOL)hasKey:(NSString *)key;

/**
 * Returns the native PDF object type of a value in the embedded file parameter dictionary (/Params).
 *
 * @param key The dictionary key, without the leading slash.
 * @return The engine's PDF object type, or -1 if the key is empty, missing, or the attachment is invalid.
 * The PDF object type values are: 0 unknown, 1 boolean, 2 number, 3 string, 4 name,
 * 5 array, 6 dictionary, 7 stream, 8 null, and 9 reference.
 * @discussion This query does not convert the value to a string, so numeric parameters such as
 * /Size can be distinguished from string parameters.
 */
- (NSInteger)valueTypeForKey:(NSString *)key;

/**
 * Returns the string value of a key in the embedded file parameter dictionary (/Params).
 *
 * @discussion Non-string values (e.g. the integer /Size) read back as an empty string.
 * /CheckSum is returned as a hex string such as "<3F2E...>".
 *
 * @param key The dictionary key, without the leading slash.
 * @return The value, or nil if the key does not exist or the attachment is invalid.
 */
- (nullable NSString *)stringValueForKey:(NSString *)key;

/**
 * Sets a string value in the embedded file parameter dictionary (/Params).
 *
 * @discussion Only ASCII values are supported; values containing other characters are rejected
 * (returns NO) because they cannot be stored losslessly.
 *
 * @param value The string value. Must contain only ASCII characters.
 * @param key The dictionary key, without the leading slash.
 * @return YES if succeeded.
 */
- (BOOL)setStringValue:(NSString *)value forKey:(NSString *)key;

@end

NS_ASSUME_NONNULL_END
