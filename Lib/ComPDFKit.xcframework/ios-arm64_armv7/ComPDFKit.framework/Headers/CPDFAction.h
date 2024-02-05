//
//  CPDFAction.h
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

/**
 * An action that is performed when, for example, a PDF annotation is activated or an outline item is clicked.
 *
 * @discussion A CPDFAction object represents an action associated with a PDF element, such as an annotation or a link, that the viewer application can perform. See the Adobe PDF Specification for more about actions and action types.
 * CPDFAction is an abstract superclass of the following concrete classes: CPDFGoToAction, CPDFURLAction, CPDFNamedAction, CPDFResetFormAction.
 */
@interface CPDFAction : NSObject

/**
 * Returns the type of the action.
 *
 * @discussion Type based on the Adobe PDF Specification (1.7), Table 8.48: Action types.
 */
@property (nonatomic,readonly) NSInteger type;

@end
