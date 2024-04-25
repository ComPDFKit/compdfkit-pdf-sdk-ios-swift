//
//  CPDFView.h
//  ComPDFKit
//
//  Copyright © 2014-2024 PDF Technologies, Inc. All Rights Reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE ComPDFKit LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <UIKit/UIKit.h>
#import <ComPDFKit/CPDFKitPlatform.h>

@class CPDFView, CPDFDocument, CPDFPage, CPDFSelection, CPDFDestination, CPDFFreeTextAnnotation, CPDFTextWidgetAnnotation,CPDFAnnotation,CPDFFont,CPDFBorder;

typedef NS_ENUM(NSInteger, CEditingSelectState) {
    CEditingSelectStateEmpty = 0,
    CEditingSelectStateEditTextArea,
    CEditingSelectStateEditNoneText,
    CEditingSelectStateEditSelectText,
};

typedef NS_OPTIONS(NSInteger, CEditingLoadType) {
    CEditingLoadTypeText =            (1UL << 0),
    CEditingLoadTypeImage =           (1UL << 1),
};

typedef NS_OPTIONS(NSInteger, CEditingLocation) {
    CEditingLocationLineBegin      =  0,
    CEditingLoadTypeLineEnd,
    CEditingLoadTypeSectionBegin,
    CEditingLoadTypeSectionEnd,
    CEditingLoadTypePreWord,
    CEditingLoadTypeNextWord,
    CEditingLoadTypePreCharPlace,
    CEditingLoadTypeNextCharPlace,
    CEditingLoadTypeUpCharPlace,
    CEditingLoadTypeDownCharPlace,
};

typedef NS_ENUM(NSInteger, CPDFDisplayDirection) {
    CPDFDisplayDirectionVertical = 0,
    CPDFDisplayDirectionHorizontal = 1,
};

typedef NS_ENUM(NSInteger, CPDFDisplayMode) {
    CPDFDisplayModeNormal = 0,
    CPDFDisplayModeNight = 1,
    CPDFDisplayModeSoft = 2,
    CPDFDisplayModeGreen = 3,
    CPDFDisplayModeCustom = 4
};

typedef NS_OPTIONS(NSInteger, CAddEditingAreaType) {
    CAddEditingAreaTypeNone  = 0,
    CAddEditingAreaTypeText,
    CAddEditingAreaTypeImage,
};

extern NSNotificationName const CPDFViewDocumentChangedNotification;
extern NSNotificationName const CPDFViewPageChangedNotification;

#pragma mark - CEditAttributes

@interface CEditAttributes : NSObject

@property (nonatomic,retain) UIFont *_Nonnull font;

@property (nonatomic,retain) UIColor *_Nonnull fontColor;

@property (nonatomic,assign) BOOL isBold;

@property (nonatomic,assign) BOOL isItalic;

@property (nonatomic,assign) NSTextAlignment alignment;

@end

#pragma mark - CPDFEditArea

@interface CPDFEditArea : NSObject

/**
 * Gets the current page of the text block.
 */
@property (nonatomic,readonly) CPDFPage *page;

/**
 * Gets the position size of the text block.
 */
@property (nonatomic,readonly) CGRect bounds;

/**
 * Gets the current selection.
 */
@property (nonatomic,readonly) CPDFSelection *selection;

/**
 * Whether it is text code block.
 */
- (BOOL)IsTextArea;

/**
 * Whether it is image code block.
 */
- (BOOL)IsImageArea;

@end

#pragma mark - CPDFEditTextArea

@interface CPDFEditTextArea : CPDFEditArea

/**
 * Get the string content of the text block.
 */
- (nullable NSString *)editTextAreaString;

@end


#pragma mark - CPDFEditImageArea

@interface CPDFEditImageArea : CPDFEditArea

/**
 * Crop region (x, y, width, height).
 */
@property (nonatomic,readonly) CGRect cropRect;

/**
 * Crop mode or not.
 */
@property (nonatomic,assign) BOOL isCropMode;

/**
 * Get a thumbnail of the corresponding size for the image block.
 */
- (nullable UIImage *)thumbnailImageWithSize:(CGSize)thumbSize;

@end

#pragma mark - CPDFEditingConfig

@interface CPDFEditingConfig : NSObject

/**
 * Sets the unselected border color of the text code block.
 */
@property (nonatomic,retain) CPDFKitPlatformColor *editingBorderColor;

/**
 * Sets the selected border color of the text code block.
 */
@property (nonatomic,retain) CPDFKitPlatformColor *editingSelectionBorderColor;

/**
 * Border width of the text code block.
 */
@property (nonatomic,assign) CGFloat editingBorderWidth;

/**
 * Array of dashed lines of the text code block.
 */
@property (nonatomic,retain) NSArray * editingBorderDashPattern;

/**
 * Sets the offset interval at which blocks are displayed
 */
@property (nonatomic,assign) CGFloat editingOffsetGap;

/**
 * Set the move range spacing for the text editing page
 */
@property (nonatomic,assign) CGFloat pageSpacingGap;

@end

@protocol CPDFViewDelegate <NSObject>

@optional

- (void)PDFViewDocumentDidLoaded:(CPDFView *)pdfView;

- (void)PDFViewCurrentPageDidChanged:(CPDFView *)pdfView;

- (void)PDFViewDidClickOnLink:(CPDFView *)pdfView withURL:(NSString *)url;

- (void)PDFViewPerformURL:(CPDFView *)pdfView withContent:(NSString *)content;

- (void)PDFViewPerformUOP:(CPDFView *)pdfView withContent:(NSString *)content;

- (void)PDFViewPerformPrint:(CPDFView *)pdfView;

- (void)PDFViewPerformReset:(CPDFView *)pdfView;

- (void)PDFViewShouldBeginEditing:(CPDFView *)pdfView textView:(UITextView *)textView forAnnotation:(CPDFFreeTextAnnotation *)annotation;

- (void)PDFViewShouldEndEditing:(CPDFView *)pdfView textView:(UITextView *)textView forAnnotation:(CPDFFreeTextAnnotation *)annotation;

- (void)PDFViewShouldBeginEditing:(CPDFView *)pdfView textView:(UITextView *)textView forTextWidget:(CPDFTextWidgetAnnotation *)textWidget;

- (void)PDFViewShouldEndEditing:(CPDFView *)pdfView textView:(UITextView *)textView forTextWidget:(CPDFTextWidgetAnnotation *)textWidget;

- (void)PDFViewDidEndDragging:(CPDFView *)pdfView;

- (void)PDFViewEditingCropBoundsDidChanged:(CPDFView *)pdfView editingArea:(CPDFEditArea *)editArea;

- (void)PDFViewEditingOperationDidChanged:(CPDFView *)pdfView;

- (void)PDFViewEditingSelectStateDidChanged:(CPDFView *)pdfView;

- (void)PDFEditingViewShouldBeginEditing:(CPDFView *)pdfView textView:(UITextView *)textView;

- (void)PDFEditingViewShouldEndEditing:(CPDFView *)pdfView textView:(UITextView *)textView;

- (void)PDFViewEditingAddTextArea:(CPDFView * _Nonnull)pdfView addPage:(CPDFPage * _Nonnull )page addRect:(CGRect)rect;

- (void)PDFViewEditingAddImageArea:(CPDFView * _Nonnull)pdfView addPage:(CPDFPage * _Nonnull)page addRect:(CGRect)rect;

- (BOOL)PDFEditingViewCanPerformAction:(SEL)action withSender:(id)sender;

- (BOOL)PDFEditingViewCanDoubleEnterEdit:(CPDFView * _Nonnull)pdfView;

@end

/**
 * This class is the main view of ComPDFKit you can instantiate a CPDFView that will host the contents of a CPDFDocument.
 *
 * @discussion CPDFView may be the only class you need to deal with for adding PDF functionality to your application.
 * It lets you display PDF data and allows users to select content, navigate through a document, set zoom level, and copy textual content to the Pasteboard.
 * CPDFView also keeps track of page history. You can subclass CPDFView to create a custom PDF viewer.
 */
@interface CPDFView : UIView

#pragma mark - Document

/**
 * Methods for associating a CPDFDocument with a CPDFView.
 */
@property (nonatomic,retain) CPDFDocument *document;

#pragma mark - Accessors

/**
 * Returns the view’s delegate.
 *
 * @see CPDFViewDelegate
 */
@property (nonatomic,assign) id<CPDFViewDelegate> delegate;

/**
 * A Boolean value indicating whether the document displays two pages side-by-side.
 */
@property (nonatomic,assign) BOOL displayTwoUp;

/**
 * Specifies whether the first page is to be presented as a cover and displayed by itself (for two-up modes).
 */
@property (nonatomic,assign) BOOL displaysAsBook;

/**
 * The layout direction, either vertical or horizontal, for the given display mode.
 *
 * @discussion Defaults to vertical layout (CPDFDisplayDirectionVertical).
 * @see CPDFDisplayDirection
 */
@property (nonatomic,assign) CPDFDisplayDirection displayDirection;

/**
 * A Boolean value indicating whether the view is displaying page breaks.
 *
 * @discussion Toggle displaying or not displaying page breaks (spacing) between pages. This spacing value is defined by the pageBreakMargins property.
 * If displaysPageBreaks is NO, then pageBreakMargins will always return { 10.0, 10.0, 10.0, 10.0 }. Default is YES.
 */
@property (nonatomic,assign) BOOL displaysPageBreaks;

/**
 * The spacing between pages as defined by the top, bottom, left, and right margins.
 *
 * @discussion If displaysPageBreaks is enabled, you may customize the spacing between pages by defining margins for the top, bottom, left, and right of each page.
 * Note that pageBreakMargins only allows positive values and will clamp any negative value to 0.0.
 * By default, if displaysPageBreaks is enabled, pageBreakMargins is { 10.0, 10.0, 10.0, 10.0 } (with respect to top, left, bottom, right), otherwise it is { 0.0, 0.0, 0.0, 0.0 }.
 */
@property (nonatomic,assign) UIEdgeInsets pageBreakMargins;

/**
 * The page render mode, either normal, night, soft, green or custom, for the given display mode.
 *
 * @see CPDFDisplayMode
 */
@property (nonatomic,assign) CPDFDisplayMode displayMode;
/**
 * If displayMode is CPDFDisplayModeCustom, you may customize the color of the page rendering.
 */
@property (nonatomic,retain) UIColor *displayModeCustomColor;

/**
 * A Boolean value indicating whether the view is displaying page crop.
 *
 * @discussion Automatically crop out valid content from the page, If there is no content in the page, no cropping will be done.
 */
@property (nonatomic,assign) BOOL displayCrop;

/**
 * A Boolean value that determines whether scrolling is enabled for the document view.
 */
@property (nonatomic,assign) BOOL scrollEnabled;

/**
 * A Boolean value that determines whether scrolling is disabled in the vertical direction for the document view.
 */
@property (nonatomic,assign) BOOL directionaHorizontalLockEnabled;

/**
 * The current scale factor for the view.
 *
 * @discussion Method to get / set the current scaling on the displayed PDF document. Default is 1.0.
 */
@property (nonatomic,assign) CGFloat scaleFactor;

- (void)setScaleFactor:(CGFloat)scaleFactor animated:(BOOL)animated;

#pragma mark - TextSelection

/**
 * Enter the text selection effect
 */
- (void)enterTextSelection:(CPDFSelection *_Nonnull)selection;

/**
 * Exit the text selection effect
 */
- (void)exitTextSelection;

#pragma mark - Draw

@property (nonatomic,readonly) BOOL isDrawing;
@property (nonatomic,readonly) BOOL isDrawErasing;

- (void)beginDrawing;
- (void)endDrawing;
- (void)commitDrawing;

- (void)setDrawErasing:(BOOL)isErasing;
- (void)drawUndo;
- (void)drawRedo;

#pragma mark - Annotation

- (void)editAnnotationFreeText:(CPDFFreeTextAnnotation *)freeText;
- (void)commitEditAnnotationFreeText;
- (void)setEditAnnotationFreeTextFont:(UIFont *)font;
- (void)setEditAnnotationFreeTextColor:(UIColor *)color;

- (void)setEditAnnotationFreeTextBorderColor:(CPDFKitPlatformColor *_Nullable)color;
- (void)setEditAnnotationFreeTextBorder:(CPDFBorder *_Nullable)border;
- (void)setEditAnnotationFreeAlignment:(NSTextAlignment)alignment;


#pragma mark - Page

/**
 * Returns the current page index.
 */
@property (nonatomic,readonly) NSInteger currentPageIndex;

/**
 * Scrolls to the specified page.
 */
- (void)goToPageIndex:(NSInteger)pageIndex animated:(BOOL)animated;

/**
 * Returns a CPDFDestination object representing the current page and the current point in the view specified in page space.
 */
@property (nonatomic,readonly) CPDFDestination *currentDestination;

/**
 * Goes to the specified destination.
 *
 * Destinations include a page and a point on the page specified in page space.
 */
- (void)goToDestination:(CPDFDestination *)destination animated:(BOOL)animated;

/**
 * Goes to the specified rectangle on the specified page.
 *
 * @discussion This allows you to scroll the CPDFView object to a specific CPDFAnnotation or CPDFSelection object,
 * because both of these objects have bounds methods that return an annotation or selection position in page space.
 * Note that rect is specified in page-space coordinates. Page space is a coordinate system with the origin at the lower-left corner of the current page.
 */
- (void)goToRect:(CGRect)rect onPage:(CPDFPage *)page animated:(BOOL)animated;


- (void)goToRect:(CGRect)rect onPage:(CPDFPage *)page offsetY:(CGFloat)offsetY animated:(BOOL)animated;

/**
 * Returns an array of CPDFPage objects that represent the currently visible pages.
 */
@property (nonatomic,readonly) NSArray<CPDFPage *> *visiblePages;

#pragma mark - Selection

/**
 * Enter text selection mode.
 *
 * @discussion The scrollEnabled is NO in the text selection mode.
 */
@property (nonatomic,assign) BOOL textSelectionMode;

/**
 * Returns actual instance of the current CPDFSelection object.
 *
 * @discussion The view redraws as necessary but does not scroll.
 */
@property (nonatomic,readonly) CPDFSelection *currentSelection;

/**
 * Clears the selection.
 *
 * @discussion The view redraws as necessary but does not scroll.
 */
- (void)clearSelection;

/**
 * Goes to the first character of the specified selection.
 */
- (void)goToSelection:(CPDFSelection *)selection animated:(BOOL)animated;

/**
 * The following calls allow you to associate a CPDFSelection with a CPDFView.
 *
 * @discussion The selection do not go away when the user clicks in the CPDFView, etc. You must explicitly remove them by passing nil to -[setHighlightedSelection:animated:].
 * This method allow you to highlight text perhaps to indicate matches from a text search. Commonly used for highlighting search results.
 */
- (void)setHighlightedSelection:(CPDFSelection *)selection animated:(BOOL)animated;

#pragma mark - Display

/**
 * The innermost view used by CPDFView or by your CPDFView subclass.
 *
 * @discussion The innermost view is the one displaying the visible document pages.
 */
- (UIScrollView *)documentView;

/**
 * Performs layout of the inner views.
 *
 * @discussion The CPDFView actually contains several subviews. Changes to the PDF content may require changes to these inner views,
 * so you must call this method explicitly if you use PDF Kit utility classes to add or remove a page, rotate a page, or perform other operations affecting visible layout.
 * This method is called automatically from CPDFView methods that affect the visible layout (such as setDocument:).
 */
- (void)layoutDocumentView;

/**
 * Draw and render of the currently visible pages.
 */
- (void)setNeedsDisplayForVisiblePages;

/**
 * Draw and render of the specified page.
 */
- (void)setNeedsDisplayForPage:(CPDFPage *)page;

#pragma mark - Rendering

/**
 * Draw and render a visible page to a context.
 *
 * @discussion For subclasses. This method is called for each visible page requiring rendering. By subclassing you can draw on top of the PDF page.
 */
- (void)drawPage:(CPDFPage *)page toContext:(CGContextRef)context;

#pragma mark - Menu

- (NSArray<UIMenuItem *> *)menuItemsAtPoint:(CGPoint)point forPage:(CPDFPage *)page;

#pragma mark - Touch

- (void)touchBeganAtPoint:(CGPoint)point forPage:(CPDFPage *)page;
- (void)touchMovedAtPoint:(CGPoint)point forPage:(CPDFPage *)page;
- (void)touchEndedAtPoint:(CGPoint)point forPage:(CPDFPage *)page;
- (void)touchCancelledAtPoint:(CGPoint)point forPage:(CPDFPage *)page;

- (void)longPressAnnotation:(CPDFAnnotation *)annotation atPoint:(CGPoint)point forPage:(CPDFPage *)page;
- (BOOL)longPressGestureShouldBeginAtPoint:(CGPoint)point forPage:(CPDFPage *)page;

#pragma mark - Conversion

/**
 * Converts a point from view space to page space.
 *
 * @discussion Page space is a coordinate system with the origin at the lower-left corner of the current page.
 * View space is a coordinate system with the origin at the upper-left corner of the current PDF view.
 */
- (CGPoint)convertPoint:(CGPoint)point toPage:(CPDFPage *)page;

/**
 * Converts a rectangle from view space to page space.
 *
 * @discussion Page space is a coordinate system with the origin at the lower-left corner of the current page.
 * View space is a coordinate system with the origin at the upper-left corner of the current PDF view.
 */
- (CGRect)convertRect:(CGRect)rect toPage:(CPDFPage *)page;

/**
 * Converts a point from page space to view space.
 *
 * @discussion Page space is a coordinate system with the origin at the lower-left corner of the current page.
 * View space is a coordinate system with the origin at the upper-left corner of the current PDF view.
 */
- (CGPoint)convertPoint:(CGPoint)point fromPage:(CPDFPage *)page;

/**
 * Converts a rectangle from page space to view space.
 *
 * @discussion Page space is a coordinate system with the origin at the lower-left corner of the current page.
 * View space is a coordinate system with the origin at the upper-left corner of the current PDF view.
 */
- (CGRect)convertRect:(CGRect)rect fromPage:(CPDFPage *)page;

#pragma mark - Edit

/**
 * This method is about configuring of editing content.
 */
@property (nonatomic,retain) CPDFEditingConfig *editingConfig;

/**
 * The properties of the editing modes: Edit text, edit images, edit text & images.
 */
@property (nonatomic,readonly) CEditingLoadType editingLoadType;

/**
 * Begins editing content.
 */
- (void)beginEditingLoadType:(CEditingLoadType)editingLoadType;

/**
 * Change the editing modes.
 */
- (void)changeEditingLoadType:(CEditingLoadType)editingLoadType;

/**
 * Text adding mode or image adding mode.
 */
- (CAddEditingAreaType)shouAddEditAreaType;

/**
 * Which feature mode (Setting text or images).
 */
- (void)setShouAddEditAreaType:(CAddEditingAreaType)shouAddEditAreaType;

/**
 * Ends editing content.
 */
- (void)endOfEditing;

/**
 * Submits the edited content.
 */
- (void)commitEditing;

/**
 * Gets whether to enter the editing mode.
 */
- (BOOL)isEditing;

/**
 * Whether the content is modified.
 */
- (BOOL)isEdited;

/**
 * The selected block.
 */
- (CPDFEditArea *)editingArea;

/**
 * The location of the click is the cursor position
 */
- (BOOL)isClickSelectCharItem;

/**
 * Clicks the context menu of block.
 */
- (NSArray<UIMenuItem *> *)menuItemsEditingAtPoint:(CGPoint)point forPage:(CPDFPage *)page;

/**
 * The statuses when editing.
 *
 * @see CEditingSelectState
 */
- (CEditingSelectState )editStatus;

/**
 * Remove editing area when finishing editing.
 */
- (void)endEditIsRemoveBlockWithEditArea:(CPDFEditArea *)editArea;

/**
 * Clear the selected text item during editing.
 */
- (void)clearEditingSelectCharItem;

/**
 * Clear the editing area.
 */
- (void)clearEditingSelectCharRange;


#pragma mark - Edit Text & Image

/**
 * Sets the position of the text (image) block
 */
- (void)setBoundsEditArea:(CPDFEditArea *)editArea withBounds:(CGRect)bounds;

/**
 * Delete text (image) block
 */
- (void)deleteEditingArea:(CPDFEditArea *)editArea;

/**
 * Whether to support undo on current page.
 */
- (BOOL)canEditTextUndo;

/**
 * Whether to support redo on current page.
 */
- (BOOL)canEditTextRedo;

/**
 * Undo on current page.
 */
- (void)editTextUndo;

/**
 * Redo on current page.
 */
- (void)editTextRedo;

#pragma mark - Edit Text

/**
 * Gets the font size of a text block or a piece of text.
 *
 */
- (CGFloat)editingSelectionFontSize DEPRECATED_MSG_ATTRIBUTE("use editingSelectionFontSizesWithTextArea instead.");
- (CGFloat)editingSelectionFontSizesWithTextArea:(CPDFEditTextArea *)textArea;

/**
 * Sets the font size of a text block or a piece of text.
 */
- (void)setEditingSelectionFontSize:(CGFloat)fontSize withTextArea:(CPDFEditTextArea *)textArea isAutoSize:(BOOL)isAutoSize;

- (void)setEditingSelectionFontSize:(CGFloat)fontSize DEPRECATED_MSG_ATTRIBUTE("use setEditingAutoSelectionFontSize:withTextArea:isAutoSize: instead.");

/**
 * Gets the font color of a text block or a piece of text.
 */
- (CPDFKitPlatformColor *)editingSelectionFontColor DEPRECATED_MSG_ATTRIBUTE("use editingSelectionFontColorWithTextArea instead,");

- (CPDFKitPlatformColor *)editingSelectionFontColorWithTextArea:(CPDFEditTextArea *)textArea;

/**
 * Sets the font color of a text block or a piece of text.
 */
- (void)setEditingSelectionFontColor:(CPDFKitPlatformColor *)fontColor DEPRECATED_MSG_ATTRIBUTE("use setEditingSelectionFontColor:withTextArea: instead.");

- (void)setEditingSelectionFontColor:(CPDFKitPlatformColor *)fontColor withTextArea:(CPDFEditTextArea *)textArea;

/**
 * Gets the alignment of a text block or a piece of text.
 */
- (NSTextAlignment)editingSelectionAlignment DEPRECATED_MSG_ATTRIBUTE("use editingSelectionAlignmentWithTextArea: instead.");
- (NSTextAlignment)editingSelectionAlignmentWithTextArea:(CPDFEditTextArea *)textArea;

/**
 * Sets the alignment of a text block or a piece of text.
 */
- (void)setCurrentSelectionAlignment:(NSTextAlignment)alignment DEPRECATED_MSG_ATTRIBUTE("use setCurrentSelectionAlignment:withTextArea: instead.");
- (void)setCurrentSelectionAlignment:(NSTextAlignment)alignment withTextArea:(CPDFEditTextArea *)textArea;

/**
 * The font name of the currently selected text block.
 */
- (NSString *)editingSelectionFontName DEPRECATED_MSG_ATTRIBUTE("use editingSelectionCFontWithTextArea");
- (NSString *)editingSelectionFontNameWithTextArea:(CPDFEditTextArea *)textArea DEPRECATED_MSG_ATTRIBUTE("use editingSelectionCFontWithTextArea.");
- (CPDFFont *)editingSelectionCFontWithTextArea:(CPDFEditTextArea *)textArea;

/**
 * Sets the font name of the selected text block. (Several standard fonts are currently supported)
 */
- (void)setEditingSelectionFontName:(NSString *)fontName DEPRECATED_MSG_ATTRIBUTE("use setEditSelectionCFont: withTextArea:");
- (void)setEditingSelectionFontName:(NSString *)fontName withTextArea:(CPDFEditTextArea *)textArea DEPRECATED_MSG_ATTRIBUTE("use setEditSelectionCFont: withTextArea:");
- (BOOL)setEditSelectionCFont:(CPDFFont *_Nonnull)font withTextArea:(CPDFEditTextArea *_Nullable)textArea ;

/**
 * Sets the currently selected text is italic.
 */
- (void)setCurrentSelectionIsItalic:(BOOL)isItalic DEPRECATED_MSG_ATTRIBUTE("use setCurrentSelectionIsItalic: withTextArea: instead.");
- (BOOL)setCurrentSelectionIsItalic:(BOOL)isItalic withTextArea:(CPDFEditTextArea *)textArea;

/**
 * Whether the font of the currently selected text block is italic.
 */
- (BOOL)isItalicCurrentSelection DEPRECATED_MSG_ATTRIBUTE("use isItalicCurrentSelectionWithTextArea: instead.");
- (BOOL)isItalicCurrentSelectionWithTextArea:(CPDFEditTextArea *)textArea;

/**
 * Sets the currently selected text is bold.
 */
- (void)setCurrentSelectionIsBold:(BOOL)isBold DEPRECATED_MSG_ATTRIBUTE("use setCurrentSelectionIsBold:withTextArea: instead.");
- (BOOL)setCurrentSelectionIsBold:(BOOL)isBold withTextArea:(CPDFEditTextArea *)textArea;

/**
 * Whether the font of the currently selected text block is bold.
 */
- (BOOL)isBoldCurrentSelection DEPRECATED_MSG_ATTRIBUTE("isBoldCurrentSelectionWithTextArea:");
- (BOOL)isBoldCurrentSelectionWithTextArea:(CPDFEditTextArea *)textArea;

/**
 * Create a blank text block.
 * @param rect The area of the text box.
 * @param attributes The text font properties.
 * @param page The created page number.
 * @return Returns whether the creation is successful.
 */
- (BOOL)createEmptyStringBounds:(CGRect)rect withAttributes:(NSDictionary<NSAttributedStringKey, id> *)attributes page:(CPDFPage *)page DEPRECATED_MSG_ATTRIBUTE("use createStringBounds:withAttributes:page:");

/**
 * Create a blank text block.
 * @param rect The area of the text box.
 * @param attributes The text font properties.
 * @param page The created page number.
 * @return Returns whether the creation is successful.
 */
- (BOOL)createStringBounds:(CGRect)rect withAttributes:(CEditAttributes *_Nullable)attributes page:(CPDFPage *_Nonnull)page;

/**
 * Sets text transparency.
 */
- (BOOL)setCharsFontTransparency:(float)transparency DEPRECATED_MSG_ATTRIBUTE("use setCharsFontTransparency:withTextArea: instead.");
- (BOOL)setCharsFontTransparency:(float)transparency withTextArea:(CPDFEditTextArea *)textArea;

/**
 * Jump cursor to a specific position in a text area.
* @param editingLocation Cursor position
* @param editArea Current text block
* @param isSelectRanage Whether to select text from the current cursor position till the end of the cursor position.
 */
- (void)jumpEditingLoction:(CEditingLocation)editingLocation withTextArea:(CPDFEditTextArea *)editArea isSelectRanage:(BOOL)isSelectRanage;

/**
 * Get the opacity of image boxes or the last character of the text.
 */
- (CGFloat)getCurrentOpacity;

/**
 * Get the font size of a certain range of text.
 */
- (CGFloat)editingSelectionFontSizeByRangeEditArea:(CPDFEditTextArea *)editArea;

/**
 * Get the font color of a certain range of text.
 */
- (CPDFKitPlatformColor *)editingSelectionFontColorByRangeEditArea:(CPDFEditTextArea *)editArea;

/**
 * Get the font name of a certain range of text.
 */
- (NSString *)editingSelectionFontNameByRangeEditArea:(CPDFEditTextArea *)editArea;

/**
 * Determine whether a certain range of text is italic.
 */
- (BOOL)isItalicCurrentSelectionByRangeEditArea:(CPDFEditTextArea *)editArea;

/**
 * Determine whether a certain range of text is bold.
 */
- (BOOL)isBoldCurrentSelectionByRangeEditArea:(CPDFEditTextArea *)editArea;

/**
 * Get the alignment of a certain range of text.
 */
- (NSTextAlignment)currentSelectionAlignmentByRangeEditArea:(CPDFEditTextArea *)editArea;

/**
 * Get the opacity of a certain range of text.
 */
- (CGFloat)opacityByRangeForEditArea:(CPDFEditArea *)editArea;

/**
 * Enter text editing state.
 */
- (BOOL)textFocusedOnWithTextArea:(CPDFEditTextArea *)textArea;

/**
 * End text editing state.
 */
- (BOOL)textFocusedOffWithTextArea:(CPDFEditTextArea *)textArea;

#pragma mark - Edit Image

/*
 * Get the rotation Angle of the picture
 */
- (CGFloat)getRotationEditArea:(CPDFEditImageArea*)editArea;

/*
 * Sets the rotation angle of image.
 */
- (void)rotateEditArea:(CPDFEditImageArea *)editArea rotateAngle:(float)angle;

/*
 * Mirrors the image horizontally.
 */
- (BOOL)horizontalMirrorEditArea:(CPDFEditImageArea *)editArea;

/*
 * Mirrors the image vertically.
 */
- (BOOL)verticalMirrorEditArea:(CPDFEditImageArea *)editArea;

/*
 * Crops the specified size.
 */
- (void)cropEditArea:(CPDFEditImageArea *)editArea withRect:(CGRect)rect;

/*
 *  Gets the cropped size.
 */
- (CGRect)getClipRectEditArea:(CPDFEditImageArea *)editArea;

/*
 *  Ends cropping.
 */
- (void)beginCropEditArea:(CPDFEditImageArea *)editArea;

/*
 *  End cutting
 */
- (void)endCropEditArea:(CPDFEditImageArea *)editArea;

/*
 *  Extracts the image to the specified path.
 */
- (BOOL)extractImageEditArea:(CPDFEditImageArea *)editArea filePath:(NSString*)filePath;

/*
 *  Extracts the image to the specified path.
 */
- (BOOL)extractImageWithEditImageArea:(CPDFEditArea *)editArea;

/*
 *  Gets image transparency.
 */
- (float)getImageTransparencyEditArea:(CPDFEditImageArea *)editArea;

/*
 *  Sets image transparency.
 */
- (BOOL)setImageTransparencyEditArea:(CPDFEditImageArea *)editArea transparency:(float)transparency;

/*
 * Adds interface of the image.
 */
- (BOOL)createEmptyImage:(CGRect)rect page:(CPDFPage *)page path:(NSString*)imagePath;

- (BOOL)createEmptyImage:(CGRect)rect page:(CPDFPage *_Nonnull)page image:(CPDFKitPlatformImage *_Nonnull)image;


/*
 * Replace of the image.
 */

- (BOOL)replaceEditImageArea:(CPDFEditImageArea *)editArea imagePath:(NSString *)imagePath rect:(CGRect)rect ;

- (BOOL)replaceEditImageArea:(CPDFEditImageArea * _Nonnull)editArea image:(CPDFKitPlatformImage *_Nonnull)image rect:(CGRect)rect ;

@end

@interface CPDFView (EditingDeprecated)

- (BOOL)replaceEditImageArea:(CPDFEditImageArea *)editArea imagePath:(NSString *)imagePath DEPRECATED_MSG_ATTRIBUTE("Use editingConfig::replaceEditImageArea:imagePath:rect:");

- (NSArray*)getFontList DEPRECATED_MSG_ATTRIBUTE("use CPDFFont");

@end
