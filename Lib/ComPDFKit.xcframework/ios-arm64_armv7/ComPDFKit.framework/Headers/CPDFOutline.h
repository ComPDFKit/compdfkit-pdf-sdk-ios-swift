//
//  CPDFOutline.h
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

@class CPDFDocument, CPDFDestination, CPDFAction;

/**
 * A CPDFOutline object is an element in a tree-structured hierarchy that can represent the structure of a PDF document.
 *
 * @discussion An outline is an optional component of a PDF document, useful for viewing the structure of the document and for navigating within it.
 * Outlines are created by the document’s author. If you represent a PDF document outline using outline objects, the root of the hierarchy is obtained from the PDF document itself.
 * This root outline is not visible and serves merely as a container for the visible outlines.
 */
@interface CPDFOutline : NSObject

#pragma mark - Accessors

/**
 * Returns the document with which the outline is associated.
 */
@property (nonatomic,readonly) CPDFDocument *document;

/**
 * Returns the parent outline object of the outline (returns NULL if called on the root outline object).
 */
@property (nonatomic,readonly) CPDFOutline *parent;

/**
 * Returns the number of child outline objects in the outline.
 */
@property (nonatomic,readonly) NSUInteger numberOfChildren;

/**
 * Returns the index of the outline item, relative to its siblings (and from the perspective of the parent).
 *
 * @discussion The root outline item (or any item with no parent) is always index 0.
 */
@property (nonatomic,readonly) NSUInteger index;

/**
 * Method to get / set the label for the outline.
 *
 * @discussion The root outline serves only as a container for the outlines it owns; it does not have a label.
 */
@property (nonatomic,retain) NSString *label;

/**
 * Method to get / set the destination associated with the outline.
 *
 * @discussion The root outline serves only as a container for the outlines it owns; it does not have a destination.
 * Note that a CPDFOutline object can have either a destination or an action, not both.
 * This method may return NULL if the outline has an associated action instead of a destination.
 * Note that if the associated action is a CPDFGoToAction, this method returns the destination from the CPDFGoToAction object.
 * However, it is better to use the action method for this purpose.
 */
@property (nonatomic,retain) CPDFDestination *destination;

/**
 * Method to get / set the action performed when users click the outline.
 *
 * @discussion The root outline serves only as a container for the outlines it owns; it does not have an action.
 * Note that a CPDFOutline object can have either an action or a destination, not both.
 * If the CPDFOutline object has a destination, instead of an action, action returns a CPDFGoToAction object (this is equivalent to calling destination on the CPDFOutline object).
 * For other action types, action returns the appropriate PDF Kit action type object, such as CPDFURLAction.
 */
@property (nonatomic,retain) CPDFAction *action;

/**
 * Returns the child outline object at the specified index.
 *
 * @discussion The index is zero-based. This method throws an exception if index is out of range.
 * A PDFOutline object retains all its children, so childAtIndex: returns the same retained child outline object every time it’s called.
 * This means that you do not need to retain the object returned by childAtIndex:.
 */
- (CPDFOutline *)childAtIndex:(NSUInteger)index;

/**
 * Create a outline object and inserts the outline object at the specified index.
 *
 * @discussion To build a PDF outline hierarchy, use this method to add child outline objects.
 */
- (CPDFOutline *)insertChildAtIndex:(NSUInteger)index;

/**
 * @discussion When moving items around within an outline hierarchy, you should retain the item and call -[removeFromParent] first.
 */
- (void)insertChild:(CPDFOutline *)child atIndex:(NSUInteger)index;

/**
 * Removes the outline object from its parent.
 */
- (void)removeFromParent;

@end
