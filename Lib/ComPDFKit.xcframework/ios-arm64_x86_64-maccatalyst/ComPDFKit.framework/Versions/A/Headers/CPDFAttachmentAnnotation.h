//
//  CPDFAttachmentAnnotation.h
//  ComPDFKit
//
//  Copyright © 2014-2025 PDF Technologies, Inc. All Rights Reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE ComPDFKit LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <ComPDFKit/CPDFAnnotation.h>

/**
 * A CPDFAttachmentAnnotation object represents a file attachment annotation.
 */
@interface CPDFAttachmentAnnotation : CPDFAnnotation

/**
 * The annotation's icon name (the /Name entry), or nil when no name is available.
 *
 * @discussion Standard attachment icon names are Graph, PushPin, Paperclip and Tag.
 * Custom names are preserved, although their appearance depends on the PDF viewer.
 * Setting nil or an empty string leaves the current icon unchanged. A successful change
 * requests an annotation appearance update and marks the document as modified.
 */
@property (nonatomic, copy, nullable) NSString *iconName;

/**
 * The name of the embedded file (the /UF entry of the file specification, falling back to /F),
 * or nil when the annotation has no embedded file.
 *
 * @discussion The embedded file properties are read from the document on every access, so they
 * reflect a file replaced with setEmbeddedFileAtPath:attachName: right away. They are nil (or 0)
 * when the file specification is missing, invalid, or refers to an external file.
 */
@property (nonatomic, readonly, nullable) NSString *attachmentName;

/**
 * The size of the embedded file in bytes, or 0 when the annotation has no embedded file.
 *
 * @discussion Taken from the /Params /Size entry of the embedded file stream when present,
 * otherwise from the decoded stream length.
 */
@property (nonatomic, readonly) unsigned long long fileSize;

/**
 * The MIME type of the embedded file (the /Subtype entry of the embedded file stream),
 * or nil when it is not specified.
 */
@property (nonatomic, readonly, nullable) NSString *mimeType;

/**
 * The description of the embedded file (the /Desc entry of the file specification),
 * or nil when it is not specified.
 *
 * @discussion Setting a value writes /FS /Desc and marks the document as modified; setting nil or
 * an empty string clears it. Setting has no effect when the annotation has no embedded file.
 * This is not the annotation's text (`contents`).
 */
@property (nonatomic, copy, nullable) NSString *fileDescription;

/**
 * Reads the decoded content of the embedded file into memory, without writing a temporary file.
 *
 * @return The file content, or nil when the annotation has no embedded file. A valid empty file
 * returns empty data.
 */
- (NSData *_Nullable)embeddedFileData;

/**
 * Sets an embedded file attachment for the annotation.
 *
 * @param filePath The full file path to embed.
 * @param attachName The attachment display name.
 * @return YES if succeeded.
 */
- (BOOL)setEmbeddedFileAtPath:(NSString *_Nullable)filePath attachName:(NSString *_Nullable)attachName;

/**
 * Saves the embedded file attachment to a target path.
 *
 * @param filePath The target path to save to.
 * @return YES if succeeded.
 */
- (BOOL)saveEmbeddedFileToPath:(NSString *_Nullable)filePath;

/**
 * Removes the embedded file attachment together with this annotation.
 *
 * @discussion A file attachment annotation cannot exist without its embedded file, so the
 * annotation itself is removed from its page as well. On success the page's annotations no
 * longer contain this annotation and CPDFPageDidRemoveAnnotationNotification is posted.
 * To replace the file content while keeping the annotation, use setEmbeddedFileAtPath:attachName: instead.
 *
 * @return YES if succeeded.
 */
- (BOOL)removeEmbeddedFileAttachment;

@end
