//
//  CPDFPage.h
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
#import <ComPDFKit/CPDFDocument.h>

extern NSNotificationName const CPDFPageEditingDidChangedNotification;

/**
 * The following box types may be used with CPDFPage drawing and bounds-setting methods.
 * See the Adobe PDF Specification for more information on box types, units, and coordinate systems.
 */
typedef NS_ENUM(NSInteger, CPDFDisplayBox) {
    /** A rectangle defining the boundaries of the physical medium for display or printing, expressed in default user-space units. */
    CPDFDisplayMediaBox = 0,
    /** A rectangle defining the boundaries of the visible region , expressed in default user-space units. Default value equal to CPDFDisplayMediaBox. */
    CPDFDisplayCropBox = 1,
    /** A rectangle defining the boundaries of the clip region for the page contents in a production environment. Default value equal to CPDFDisplayCropBox. */
    CPDFDisplayBleedBox = 2,
    /** A rectangle defining the intended boundaries of the finished page. Default value equal to CPDFDisplayCropBox. */
    CPDFDisplayTrimBox = 3,
    /** A rectangle defining the boundaries of the page’s meaningful content including surrounding white space intended for display. Default value equal to CPDFDisplayCropBox. */
    CPDFDisplayArtBox = 4
};

extern NSNotificationName const CPDFPageDidLoadAnnotationNotification;
extern NSNotificationName const CPDFPageDidAddAnnotationNotification;
extern NSNotificationName const CPDFPageDidRemoveAnnotationNotification;
extern NSNotificationName const CPDFPageDidFindSearchChangeNotification;

@class CPDFDocument, CPDFAnnotation, CPDFSelection;

/**
 * CPDFPage, a subclass of NSObject, defines methods used to render PDF pages and work with annotations, text, and selections.
 *
 * @discussion CPDFPage is a logical representation of a PDF document's page. Your application instantiates a CPDFPage object by asking for one from a CPDFDocument object.
 * For simple display and navigation of PDF documents within your application, you don’t need to use CPDFPage. You need only use CPDFView.
 */
@interface CPDFPage : NSObject

#pragma mark - Accessors

/**
 * Returns the CPDFDocument object with which the page is associated.
 */
@property (nonatomic,readonly) CPDFDocument *document;

/**
 * Returns the label for the page.
 *
 * @discussion Typically, the label is “1” for the first page, “2” for the second page, and so on, but nonnumerical labels are also possible (such as “xxi”, “4-1” and so on).
 */
@property (nonatomic,readonly) NSString *label;

/**
 * Returns the bounds for the specified PDF display box.
 *
 * @see CPDFDisplayBox
 */
- (CGRect)boundsForBox:(CPDFDisplayBox)box;

/**
 * Sets the bounds for the specified box.
 *
 * @discussion If the box does not exist, this method creates it for you.
 * @see CPDFDisplayBox
 */
- (void)setBounds:(CGRect)bounds forBox:(CPDFDisplayBox)box;

/**
 * Sets the rotation angle for the page in degrees.
 *
 * @discussion Rotation on a page. Must be 0, 90, 180 or 270 (negative rotations will be "normalized" to one of 0, 90, 180 or 270).
 * Some PDF's have an inherent rotation and so -[rotation] may be non-zero when a PDF is first opened.
 */
@property (nonatomic,assign) NSInteger rotation;

@property (nonatomic,readonly) CGRect bounds;

/**
 * Returns the size of page after rotation.
 */
@property (nonatomic,readonly) CGSize size;

#pragma mark - Annotations

/**
 * Returns an array containing the page’s annotations.
 *
 * @discussion The elements of the array will most likely be typed to subclasses of the CPDFAnnotation class.
 */
@property (nonatomic,readonly) NSArray<CPDFAnnotation *> *annotations;

/**
 * Adds the specified annotation object to the page.
 */
- (void)addAnnotation:(CPDFAnnotation *)annotation;
/**
 * Removes the specified annotation from the page.
 */
- (void)removeAnnotation:(CPDFAnnotation *)annotation;
/**
 * Removes all annotations from the page.
 */
- (void)removeAllAnnotations;

/**
 * Returns the annotation, if there is one, at the specified point.
 *
 * @discussion Use this method for hit-testing based on the current cursor position. If more than one annotation shares the specified point,
 * the frontmost (or topmost) one is returned (the annotations are searched in reverse order of their appearance in the PDF data file). Returns NULL if there is no annotation at point.
 * Specify the point in page space. Page space is a coordinate system with the origin at the lower-left corner of the current page.
 */
- (CPDFAnnotation *)annotationAtPoint:(CGPoint)point;
- (BOOL)annotation:(CPDFAnnotation *)annotation atPoint:(CGPoint)point;

#pragma mark - Conversion

/**
 * This transform correctly rotates and offsets based on the given page's rotation property.
 */
- (CGAffineTransform)transform;

#pragma mark - Rendering

/**
 * Convenience function that returns an image of this page, with annotations.
 */
- (CPDFKitPlatformImage *)thumbnailOfSize:(CGSize)size;

#pragma mark - Find
/**
 *Page number search for content editing*
 */
- (NSArray<NSArray<CPDFSelection *> *> *)findEditString:(NSString *)string withOptions:(CPDFSearchOptions)options;

#pragma mark - Text

/**
 * Returns the number of characters on the page, including whitespace characters.
 *
 * @discussion Number of characters on the page (including linefeeds and spaces inserted).
 */
@property (nonatomic,readonly) NSUInteger numberOfCharacters;

/**
 * Returns the bounds, in page space, of the character at the specified index.
 *
 * @discussion In the unlikely event that there is more than one character at the specified index point, only the bounds of the first character is returned.
 * Page space is a coordinate system with the origin at the lower-left corner of the current page. Note that the bounds returned are not guaranteed to have integer coordinates.
 */
- (CGRect)characterBoundsAtIndex:(NSInteger)index;

/**
 * Returns the character index value for the specified point in page space.
 *
 * @discussion Returns the index of the first character if multiple characters are at this point. If there is no character at the specified point, the method returns -1.
 * Page space is a coordinate system with the origin at the lower-left corner of the current page.
 */
- (NSInteger)characterIndexAtPoint:(CGPoint)point;

/**
 * Returns an NSString object representing the text on the page.
 *
 * @discussion String (with linefeeds and in some cases spaces inserted) representing the text on the page.
 */
@property (nonatomic,readonly) NSString *string;

/**
 * Returns the text enclosed within the specified rectangle, expressed in page coordinates.
 *
 * @discussion Given a rect in page-space, returns a selection representing enclosed text on page.
 */
- (NSString *)stringForRect:(CGRect)rect;

/**
 * Returns the text enclosed within the specified range.
 */
- (NSString *)stringForRange:(NSRange)range;

/**
 * Returns the text enclosed within the specified range.
 */
- (NSString *)stringForLocation:(NSUInteger)location length:(NSUInteger)length;

#pragma mark - Selections

/**
 * Returns the text contained within the specified range.
 *
 * @discussion Given a range, returns a selection representing text within that range. Will clamp any range that goes out of bounds. Will return NULL for an empty selection.
 */
- (CPDFSelection *)selectionForRange:(NSRange)range;

#pragma mark - Redact

/**
 * Applies redaction annotations in the page.
 */
- (void)applyRedactions;

@end
