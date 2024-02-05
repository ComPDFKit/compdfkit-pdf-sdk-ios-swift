//
//  CPDFGoToAction.h
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

@class CPDFDestination;

/**
 * CPDFGoToAction, a subclass of CPDFAction, defines methods for getting and setting the destination of a go-to action.
 *
 * @discussion A CPDFGoToAction object represents the action of going to a specific location within the PDF document.
 */
@interface CPDFGoToAction : CPDFAction

#pragma mark - Initializers

/**
 * Initializes the go-to action.
 *
 * @param destination The destination with which to initialize the go-to action.
 */
- (instancetype)initWithDestination:(CPDFDestination *)destination NS_DESIGNATED_INITIALIZER;

#pragma mark - Accessors

/**
 * Returns the destination associated with the action.
 */
- (CPDFDestination *)destination;

@end
