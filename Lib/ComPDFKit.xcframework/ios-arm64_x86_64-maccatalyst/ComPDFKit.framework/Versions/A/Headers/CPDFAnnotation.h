//
//  CPDFAnnotation.h
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
#import <ComPDFKit/CPDFPage.h>
#import <ComPDFKit/CPDFBorder.h>

/**
 * A set of flags specifying various characteristics of the annotation.
 * ComPDFKit doesn't support all of those flag settings.
 */
typedef NS_OPTIONS(NSInteger, CPDFAnnotationFlags) {
    /* [IGNORED] If set, ignore annotation AP stream if there is no handler available. */
    CPDFAnnotationFlagInvisible = 1,
    /* If set, do not display or print the annotation or allow it to interact with the user. */
    CPDFAnnotationFlagHidden = 1 << 1,
    /* [IGNORED] If set, print the annotation when the page is printed. */
    CPDFAnnotationFlagPrint = 1 << 2,
    /* [IGNORED] If set, don't scale the annotation’s appearance to match the magnification of the page. */
    CPDFAnnotationFlagNoZoom = 1 << 3,
    /* [IGNORED] If set, don't rotate the annotation’s appearance to match the rotation of the page. */
    CPDFAnnotationFlagNoRotate = 1 << 4,
    /* [IGNORED] If set, don't display the annotation on the screen. (But printing might be allowed) */
    CPDFAnnotationFlagNoView = 1 << 5,
    /**
     * If set, don’t allow the annotation to be deleted or its properties to be modified, including `contents`.
     * This is ignored for widget annotations (form elements).
     * For widget annotations the `isReadOnly` property of the associated form field should be used instead.
     * This flag only restricts the ComPDFKit UI and does not impact programmatic modification of the annotation.
     */
    CPDFAnnotationFlagReadOnly = 1 << 6,
    /* If set, don’t allow the annotation to be deleted or its properties to be modified, except for `contents`. */
    CPDFAnnotationFlagLocked = 1 << 7,
    /* [IGNORED] If set, invert the interpretation of the `.noView` flag for certain events. */
    CPDFAnnotationFlagToggleNoView = 1 << 8,
    /* [IGNORED] If set, don't allow the `contents` of the annotation to be modified by the user. */
    CPDFAnnotationFlagLockedContents = 1 << 9
};

/**
 * An annotation in a PDF document.
 *
 * @discussion In addition to its primary textual content, a PDF file can contain annotations that represent links, form elements, highlighting circles, textual notes, and so on.
 * Each annotation is associated with a specific location on a page and may offer interactivity with the user.
 *
 * This is the base class for all annotations. A CPDFAnnotation object by itself is not useful, only subclasses (like CPDFCircleAnnotation, CPDFTextAnnotation) are interesting.
 * In parsing a PDF however, any unknown or unsupported annotations will be represented as this base class.
 */
@interface CPDFAnnotation : NSObject

#pragma mark - Initializers

/**
 * Initializes a PDF annotation object.
 *
 * @discussion Subclasses of CPDFAnnotation should use this method to initialize annotation instances.
 * Invoking initWithDocument: directly on a CPDFAnnotation object creates an illegal NULL type.
 */
- (instancetype)initWithDocument:(CPDFDocument *)document;

#pragma mark - Accessors

/**
 * Returns the page that the annotation is associated with (may return nil if annotation not associated with a page).
 *
 * @discussion The addAnnotation: method in the CPDFPage class lets you associate an annotation with a page.
 */
@property (nonatomic,readonly) CPDFPage *page;

/**
 * Returns the type of the annotation. Examples include: "Text", "Link", "Line", etc.
 *
 * @discussion The type of the annotation. Types include Line, Link, Text, and so on, referring to the CPDFAnnotation subclasses.
 * In the Adobe PDF Specification, this attribute is called Subtype, and the common “type” for all annotations in the PDF Specification is Annot.
 */
@property (nonatomic,readonly) NSString *type;

/**
 * Method to get / set the bounding box for the annotation in page space. Required for all annotations.
 *
 * @discussion Page space is coordinate system with the origin at the lower-left corner of the current page.
 */
@property (nonatomic,assign) CGRect bounds;

/**
 * Method to get / set the textual content (if any) associated with the annotation.
 *
 * @discussion Textual content is typically associated with CPDFTextAnnotation and CPDFFreeTextAnnotation annotations.
 */
@property (nonatomic,retain) NSString *contents;

/**
 * Method to get / set the stroke thickness for the annotation.
 *
 * @discussion For the "geometry" annotations (Circle, Ink, Line, Square), the stroke thickness indicates the line width.
 * CPDFAnnotation markup types (Highlight, Strikethrough, Underline) ignores the stroke thickness.
 */
@property (nonatomic,assign) CGFloat borderWidth;

/**
 * Optional border or border style that describes how to draw the annotation border (if any).
 * @discussion For the "geometry" annotations (Circle, Ink, Line, Square), the border indicates the line width and whether to draw with a dash pattern or solid pattern.
 * CPDFAnnotation markup types (Highlight, Strikethrough, Underline) ignores the border.
 */
@property (nonatomic,retain) CPDFBorder *border;

/**
 * Method to get / set the opacity for the annotation.
 */
@property (nonatomic,assign) CGFloat opacity;

/**
 * Method to get / set the color for the annotation.
 * @discussion For many annotations ("Circle", "Square") the stroke color. Used for other annotations as well.
 */
@property (nonatomic,retain) CPDFKitPlatformColor *color;

@property (nonatomic,assign) BOOL isNoRotate;

/**
 * Returns the modification date of the annotation.
 */
- (NSDate *)modificationDate;
- (void)setModificationDate:(NSDate *)modificationDate;

/**
 * Returns the name of the user who created the annotation.
 */
- (NSString *)userName;
- (void)setUserName:(NSString *)userName;

/**
 * Returns the flags of the annotation.
 *
 * @see CPDFAnnotationFlags
 */
- (CPDFAnnotationFlags)flags;
/**
 * Sets the flags of the annotation.
 *
 * @see CPDFAnnotationFlags
 */
- (void)setFlags:(CPDFAnnotationFlags)flags;

/**
 * This is a convenience property that checks for `CPDFAnnotationFlagHidden` in `flags`.
 */
- (BOOL)isHidden;
- (void)setHidden:(BOOL)hidden;

/**
 * This is a convenience property that checks for `CPDFAnnotationFlagReadOnly` in `flags`.
 */
- (BOOL)isReadOnly;
- (void)setReadOnly:(BOOL)readOnly;

/**
 * This is a convenience property that checks for `CPDFAnnotationFlagLocked` in `flags`.
 */
- (BOOL)isLocked;
- (void)setLocked:(BOOL)locked;

/**
 * Update appearance stream for the annotation.
 *
 * @discussion ComPDFKit will update the annotation appearance by default when you modify the annotation properties.
 * You can also manually update the appearance by calling the updateAppearanceStream method,
 * but you must call the updateAppearanceStream method manually when you modify the bounds of CPDFTextAnnotation, CPDFStampAnnotation, CPDFSignatureAnnotation annotations.
 */
- (void)updateAppearanceStream;

#pragma mark - Drawing

/**
 * Draw method. Draws in page-space relative to origin of "box" passed in and to the given context.
 */
- (void)drawWithBox:(CPDFDisplayBox)box inContext:(CGContextRef)context;

@end
