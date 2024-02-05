//
//  CPDFAnnotationLink.h
//  ComPDFKit
//
//  Copyright © 2014-2024 PDF Technologies, Inc. All Rights Reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE ComPDFKit LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <ComPDFKit/CPDFAnnotation.h>

@class CPDFDestination;

/**
 * A CPDFLinkAnnotation object represents either a hypertext link to another location in the document (specified as a CPDFDestination object) or a URL.
 */
@interface CPDFLinkAnnotation : CPDFAnnotation

/**
 * Gets the destination for the link when the destination was specified as a CPDFDestination object.
 *
 * @discussion Destination for the link. May be nil if no destination associated with link; in this case the -[URL] may be valid.
 */
- (CPDFDestination *)destination;
- (void)setDestination:(CPDFDestination *)destination;

/**
 * Gets the destination for the link when the destination was specified as a URL.
 *
 * @discussion URL for the link. May be nil if no URL action associated with link; in this case the -[destination] may be valid.
 */
- (NSString *)URL;
- (void)setURL:(NSString *)url;

@end
