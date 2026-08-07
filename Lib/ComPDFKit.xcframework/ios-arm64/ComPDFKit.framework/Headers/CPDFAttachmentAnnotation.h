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
 * Removes the embedded file attachment from the annotation.
 *
 * @return YES if succeeded.
 */
- (BOOL)removeEmbeddedFileAttachment;

@end
