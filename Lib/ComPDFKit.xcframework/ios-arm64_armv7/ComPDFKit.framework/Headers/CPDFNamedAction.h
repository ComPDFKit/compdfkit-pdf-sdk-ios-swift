//
//  CPDFNamedAction.h
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

typedef NS_ENUM(NSInteger, CPDFNamedActionName) {
    CPDFNamedActionNone = 0,
    CPDFNamedActionNextPage = 1,
    CPDFNamedActionPreviousPage = 2,
    CPDFNamedActionFirstPage = 3,
    CPDFNamedActionLastPage = 4,
    CPDFNamedActionPrint = 5
};

/**
 * CPDFNamedAction defines methods used to work with actions in PDF documents, some of which are named in the Adobe PDF Specification.
 *
 * @discussion A CPDFNamedAction object represents an action with a defined name.
 */
@interface CPDFNamedAction : CPDFAction

- (instancetype)initWithName:(CPDFNamedActionName)name NS_DESIGNATED_INITIALIZER;

#pragma mark - Accessors

/**
 * Returns the name of the named action.
 *
 * @see CPDFNamedActionName
 */
- (CPDFNamedActionName)name;

@end
