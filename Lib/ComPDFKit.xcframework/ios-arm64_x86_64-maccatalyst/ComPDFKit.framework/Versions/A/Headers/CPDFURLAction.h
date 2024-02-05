//
//  CPDFURLAction.h
//  ComPDFKit
//
//  Copyright © 2014-2024 PDF Technologies, Inc. All Rights Reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE ComPDFKit LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <ComPDFKit/CPDFAction.h>

/**
 * CPDFURLAction, a subclass of CPDFAction, defines methods for getting and setting the URL associated with a URL action.
 */
@interface CPDFURLAction : CPDFAction

#pragma mark - Initializers

/**
 * Initializes a URL action with the specified URL.
 *
 * @param url The URL to set the action to.
 */
- (instancetype)initWithURL:(NSString *)url NS_DESIGNATED_INITIALIZER;

#pragma mark - Accessors

/**
 * Returns the URL associated with the URL action.
 */
- (NSString *)url;

@end
