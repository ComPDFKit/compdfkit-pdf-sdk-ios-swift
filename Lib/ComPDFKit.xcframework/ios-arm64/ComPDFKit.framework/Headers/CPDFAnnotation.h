//
//  CPDFAnnotation.h
//  ComPDFKit
//
//  Copyright © 2014-2026 PDF Technologies, Inc. All Rights Reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE ComPDFKit LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <ComPDFKit/CPDFKitPlatform.h>
#import <ComPDFKit/CPDFPage.h>
#import <ComPDFKit/CPDFBorder.h>

@class CPDFAngleMeasureInfo;
@class CPDFCountMeasureInfo;

/**
 * Snapping mode used by the ruler snapping (object snapping) feature.
 *
 * @discussion This is an Objective-C wrapper for the C++ SnappingMode enum in pso::measure::Ruler.
 */
typedef NS_OPTIONS(NSInteger, CPDFSnappingMode) {
    CPDFSnappingModeNone = 0,
    /** Default: enable all snapping types. */
    CPDFSnappingModeDefault = 15,
    /** Snap to a point on a line. */
    CPDFSnappingModePointOnLine = 1,
    /** Snap to the midpoint of a line. */
    CPDFSnappingModeLineMidpoint = 2,
    /** Snap to the intersection point of lines. */
    CPDFSnappingModeLineIntersection = 4,
    /** Snap to the endpoint of a line/path. */
    CPDFSnappingModePathEndpoint = 8,
};

/**
 * To setting reply state of the repply state annotation.
 */
typedef NS_ENUM(NSInteger, CPDFAnnotationState) {
    /*A mark state */
    CPDFAnnotationStateMarked = 0,
    CPDFAnnotationStateUnMarked,
    /*A review state*/
    CPDFAnnotationStateAccepted,
    CPDFAnnotationStateRejected,
    CPDFAnnotationStateCanceled,
    CPDFAnnotationStateCompleted,
    CPDFAnnotationStateNone,
    /*A error state*/
    CPDFAnnotationStateError
};

/**
 * Distinguish between different types of reply annotation.
 */
typedef NS_ENUM(NSInteger, CPDFReplyAnnotationType)  {
    CPDFReplyAnnotationTypeNone = 0,
    /*CPDFReplyAnnotation*/
    CPDFReplyAnnotationTypeReply,
    /*CPDFReplyStateAnnotation*/
    CPDFReplyAnnotationTypeMark,
    CPDFReplyAnnotationTypeReview
};

typedef NS_ENUM(NSInteger, CPDFAnnotationDraggedHandle) {
    CPDFAnnotationDraggedHandleNone = -1,
    CPDFAnnotationDraggedHandleMinXMinY = 0,
    CPDFAnnotationDraggedHandleMidXMinY = 1,
    CPDFAnnotationDraggedHandleMaxXMinY = 2,
    CPDFAnnotationDraggedHandleMaxXMidY = 3,
    CPDFAnnotationDraggedHandleMaxXMaxY = 4,
    CPDFAnnotationDraggedHandleMidXMaxY = 5,
    CPDFAnnotationDraggedHandleMinXMaxY = 6,
    CPDFAnnotationDraggedHandleMinXMidY = 7,
};

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
 *
 * @note Migration from previous versions:
 *       - Use @c -initWithPage:document: to create annotations, then call
 *         @c -[CPDFPage updateAndAddAnnotation:] to attach them.
 *       - A new method @c -copyToPage: is available for copying an annotation to a target page.
 *       - Use @c -copyForUndoRestore before removing an annotation when the
 *         annotation must be restored later by undo/redo.
 */
/**
 * CPDFAnnotation does not conform to NSCopying.
 * Use \c -copyToPage: to copy an annotation to a target page.
 */
@interface CPDFAnnotation : NSObject

#pragma mark - Initializers

/**
 * Creates a new annotation object associated with the given page and document.
 *
 * @discussion This initializer creates the underlying engine annotation object
 *             (via @c CreateAnnot) and binds it to the page. Call
 *             @c -[CPDFPage updateAndAddAnnotation:] to finish the wrapper-side
 *             registration, appearance generation, and undo/redo notification.
 *
 * @param page     The page on which the annotation will eventually reside.
 * @param document The document that owns the page.
 *
 * @return A new annotation instance, or @c nil if creation failed.
 */
- (nullable instancetype)initWithPage:(CPDFPage *)page document:(CPDFDocument *)document;

#pragma mark - Accessors

/**
 * Returns the page that the annotation is associated with (may return nil if annotation not associated with a page).
 *
 * @discussion New annotation objects are associated with a page during
 *             @c -initWithPage:document: creation.
 */
@property (nonatomic, readonly, weak) CPDFPage *page;

/**
 * Copies the annotation to the specified target page.
 *
 * @param page The target page to copy the annotation to. The copied annotation will be added to this page.
 * @return For an ordinary annotation, a new annotation wrapper on the target
 *         page. For a restorable copy returned by @c -copyForUndoRestore, the
 *         original wrapper may be returned when it is still alive and has been
 *         physically removed. Returns @c nil when copying or safe restoration
 *         fails.
 */
- (nullable CPDFAnnotation *)copyToPage:(CPDFPage *)page;

/**
 * Creates a restorable copy for undo/redo before the receiver is removed.
 *
 * @discussion The returned annotation is backed by an internal temporary document
 *             that is retained by the copied annotation. Keep the returned object
 *             in your undo item, then call @c -copyToPage: on it to restore a new
 *             annotation to the target page during undo/redo. Call this method
 *             before removing the original annotation from its page.
 *             The SDK weakly associates the original wrapper with this copy.
 *             Restoring through @c -copyToPage: reuses that wrapper when safe,
 *             without retaining its page or native annotation. If the original
 *             wrapper has already been released, restoration creates a new
 *             wrapper as a compatibility fallback.
 *
 * @return A restorable annotation copy, or nil if the copy failed.
 */
- (nullable CPDFAnnotation *)copyForUndoRestore;

/**
 * Releases the temporary document retained by @c -copyForUndoRestore.
 *
 * @discussion Call this after the undo/redo restore has successfully copied the
 *             restorable annotation back to the target page with @c -copyToPage:.
 *             After calling this method, do not use the same restorable
 *             annotation as a copy source again.
 */
- (void)releaseUndoRestoreDocument;

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
@property (nonatomic,strong) NSString *contents;

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
@property (nonatomic,strong) CPDFBorder *_Nullable border;

/**
 * Method to get / set the opacity for the annotation.
 */
@property (nonatomic,assign) CGFloat opacity;

/**
 * Method to get / set the color for the annotation.
 * @discussion For many annotations ("Circle", "Square") the stroke color. Used for other annotations as well.
 */
@property (nonatomic,strong) CPDFKitPlatformColor *color;

/**
 * remove color(Set it to transparent, or set SetColor: to nil)
 */
- (BOOL)removeColor;

@property (nonatomic,assign) BOOL isNoRotate;

/**
 * Returns the modification date of the annotation.
 */
- (NSDate *_Nullable)modificationDate;
- (void)setModificationDate:(NSDate *_Nullable)modificationDate;

/**
 * Returns the creation date of the annotation.
 */
- (NSDate *_Nullable)creationDate;
- (void)setCreationDate:(NSDate *_Nullable)creationDate;

/**
 * Returns the name of the user who created the annotation.
 */
- (NSString *)userName;
- (void)setUserName:(NSString *)userName;

/**
 * * Returns the image of the annotation.
*/
- (CPDFKitPlatformImage *_Nonnull)anntationImage;

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

- (void)updateAnnotationRotationAppearanceStream;

#pragma mark - Rotation

/**
 * Sets the rotation angle for the annotation in degrees.
 *
 * @discussion Rotation on a annotation. Must be -180 ~ 180.
 */
@property (nonatomic,readonly) NSInteger annotationRotation;

/**
 * Method to get the all rect vertex points after rotation.
 *
 * @discussion Vertex points of the current page.
 */
@property (nonatomic, readonly) NSArray<NSValue *> * _Nonnull saveRectRotationPoints;

/**
 * Method to get  the  rect befer rotation.based on the rect when the rotation angle is 0 degrees.
 *
 * @discussion rect of the current page.
 */
@property (nonatomic, readonly) CGRect saveSourceRect;

/**
 * Method to Quickly set the annotation rotation angle, and simultaneously update the saveRectRotationPoints and annotationRotation property.
 *
 * @discussion Rotation on a annotation. The annotationRotation based on when the rotation angle is 0 degrees. Must be -180 ~ 180.
 */
- (void)updateAnnotationRotation:(NSInteger)annotationRotation;

/**
 * Method to move stampAnnotation
 *
 * @discussion offset
 */
- (void)moveAnnotationWithActivePage:(CPDFPage *_Nonnull)newActivePage offset:(CPDFKitPlatformPoint)offset;

/**
 * Method to drag stampAnnotation
 *
 * @discussion draggedIndex
 */
- (void)dragAnnotationWithCurrentPagePoint:(CGPoint)currentPagePoint draggedIndex:(CPDFAnnotationDraggedHandle)draggedIndex;

#pragma mark - Reply

// Create Reply Annotation
// must call SetRect to compatible with adobe
- (CPDFAnnotation *)createReplyAnnotation;

// Create Reply State Annotation
// must call SetRect to compatible with adobe
- (CPDFAnnotation *)createReplyStateAnnotation:(CPDFAnnotationState)state;

// Get all Reply Annotation
@property (nonatomic,readonly) NSArray<CPDFAnnotation *> *replyAnnotations;

// Get Reply Annotation Type
@property (nonatomic,readonly) CPDFReplyAnnotationType replyAnnotationType;

// Reply State Annotation to set
- (BOOL)setAnnotState:(CPDFAnnotationState)state;
- (CPDFAnnotationState)getAnnotState;

#pragma mark - Drawing

/**
 * Draw method. Draws in page-space relative to origin of "box" passed in and to the given context.
 */
- (void)drawWithBox:(CPDFDisplayBox)box inContext:(CGContextRef _Nonnull )context;

#pragma mark - Measurement

/**
 * Applies count measurement information to the annotation.
 *
 * @discussion Count measurement requires a document for initialization.
 */
- (void)setCountMeasureInfo:(CPDFCountMeasureInfo *_Nonnull)measureInfo document:(CPDFDocument *_Nonnull)document;
- (CPDFCountMeasureInfo *_Nullable)countMeasureInfo;

/**
 * Applies angle measurement information to the annotation.
 */
- (void)setAngleMeasureInfo:(CPDFAngleMeasureInfo *_Nonnull)measureInfo;
- (CPDFAngleMeasureInfo *_Nullable)angleMeasureInfo;

/**
 * Initializes the ruler snapping snapshot for a given page.
 *
 * @param document The target document.
 * @param pageIndex Zero-based page index.
 * @param mode The snapping mode.
 * @return YES if succeeded.
 */
+ (BOOL)prepareRulerSnappingSnapshotWithDocument:(CPDFDocument *_Nonnull)document
                                      pageIndex:(NSInteger)pageIndex
                                           mode:(CPDFSnappingMode)mode;

/**
 * Closes the ruler snapping snapshot.
 */
+ (BOOL)closeRulerSnappingSnapshot;

/**
 * Snaps a point to the nearest snapping target within a radius.
 *
 * @param point The input point (page space). On success it will be updated to the snapped point.
 * @param outMode The output snapping mode if snapped (optional).
 * @param radius The snapping radius.
 * @return YES if a snapping target is found.
 */
+ (BOOL)snapPointToNearest:(CPDFKitPlatformPoint *_Nonnull)point
                   outMode:(CPDFSnappingMode *_Nullable)outMode
                    radius:(double)radius;

@end
