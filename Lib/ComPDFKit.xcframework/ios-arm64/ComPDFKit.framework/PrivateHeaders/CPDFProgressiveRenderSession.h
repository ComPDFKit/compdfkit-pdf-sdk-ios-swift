//
//  CPDFProgressiveRenderSession.h
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

@class CPDFPage;

/**
 * Progress of a time-sliced page render.
 *
 * C++: pso::pdf::ProgressiveRenderStatus (pso/pdf/progressive_render_session.h:12-17).
 * The ordering matches the C++ enum one-to-one.
 */
typedef NS_ENUM(NSInteger, CPDFProgressiveRenderStatus) {
    /** The session exists but -startRender has not been called yet. */
    CPDFProgressiveRenderStatusReady = 0,
    /** Work remains; call -continueRender again. */
    CPDFProgressiveRenderStatusToBeContinued,
    /** The page finished rendering. */
    CPDFProgressiveRenderStatusDone,
    /** The render failed and cannot be resumed. */
    CPDFProgressiveRenderStatusFailed,
};

/**
 * Inputs for a progressive render.
 *
 * C++: pso::pdf::ProgressiveRenderOptions (pso/pdf/progressive_render_session.h:19-29).
 */
@interface CPDFProgressiveRenderOptions : NSObject

/**
 * Where the page is drawn inside the session bitmap, in pixels. The origin maps
 * to start_x / start_y and the size maps to size_x / size_y
 * (progressive_render_session.h:20-23); the page is scaled to fill the size.
 *
 * Defaults to CGRectZero, which renders nothing — always set it.
 */
@property (nonatomic,assign) CGRect renderRect;

/**
 * Page rotation in quarter turns: 0, 1, 2 or 3.
 *
 * C++: ProgressiveRenderOptions::rotation (progressive_render_session.h:24).
 */
@property (nonatomic,assign) NSInteger rotation;

/**
 * Draw annotations and form widgets. Default NO.
 *
 * Sets pso::pdf::RenderFlag::kAnnotations in ProgressiveRenderOptions::flags and
 * turns on ProgressiveRenderOptions::render_forms
 * (progressive_render_session.h:25-26).
 */
@property (nonatomic,assign) BOOL isDrawAnnot;

/**
 * Render in dark mode — grayscale plus night mode, on a black background.
 * Default NO. Matches the behaviour of -renderPageOfRect:pageDrawRectOptions:.
 */
@property (nonatomic,assign) BOOL isDrawDrakMode;

/**
 * Colour the bitmap is cleared to before drawing. nil (the default) means
 * opaque white. Ignored while isDrawDrakMode is YES.
 *
 * C++: ProgressiveRenderOptions::background_color
 * (progressive_render_session.h:27).
 */
@property (nonatomic,retain) CPDFKitPlatformColor *backgroundColor;

/**
 * Per-step budget in milliseconds. Defaults to 8, matching the C++ default
 * (progressive_render_session.h:28). 0 asks the core to run each step to
 * completion without yielding.
 */
@property (nonatomic,assign) NSInteger timeSliceMilliseconds;

@end

/**
 * A cancellable, time-sliced render of a single page.
 *
 * Drive it by calling -startRender once and then -continueRender for as long as
 * the returned status is CPDFProgressiveRenderStatusToBeContinued, reading
 * -currentImage in between to show an intermediate frame.
 *
 * THREADING: a session must be driven serially. Never call -continueRender from
 * two threads at once, and never run two sessions against the same CPDFPage
 * concurrently. Each call serializes against the rest of the library on the
 * shared task queue, so a step blocks the calling thread for roughly
 * timeSliceMilliseconds.
 *
 * C++: pso::pdf::ProgressiveRenderSession (pso/pdf/progressive_render_session.h:31-56).
 */
@interface CPDFProgressiveRenderSession : NSObject

/**
 * Starts a progressive render of `page`. Returns nil when the page cannot be
 * rendered or the core library refuses to create a session.
 *
 * The receiver keeps `page` alive for as long as it lives, because the C++
 * session holds a bare pointer to the underlying page.
 *
 * C++: pso::pdf::Page::StartProgressiveRender(const ProgressiveRenderOptions&)
 * (pso/pdf/page.h:274-275).
 */
- (instancetype)initWithPage:(CPDFPage *)page options:(CPDFProgressiveRenderOptions *)options;

- (instancetype)init NS_UNAVAILABLE;

/** The page being rendered. */
@property (nonatomic,readonly) CPDFPage *page;

/**
 * Status of the most recent step.
 *
 * C++: ProgressiveRenderSession::GetStatus() (progressive_render_session.h:42).
 */
@property (nonatomic,readonly) CPDFProgressiveRenderStatus status;

/**
 * Whether the session has been closed and can no longer be advanced.
 *
 * C++: ProgressiveRenderSession::IsClosed() (progressive_render_session.h:44).
 */
@property (nonatomic,readonly,getter=isClosed) BOOL closed;

/**
 * Runs the first step. Valid once per session; calling it again returns the
 * current status without doing any work.
 *
 * C++: ProgressiveRenderSession::Start() (progressive_render_session.h:38).
 */
- (CPDFProgressiveRenderStatus)startRender;

/**
 * Advances by one time slice. Only meaningful while the status is
 * CPDFProgressiveRenderStatusToBeContinued.
 *
 * C++: ProgressiveRenderSession::Continue() (progressive_render_session.h:39).
 */
- (CPDFProgressiveRenderStatus)continueRender;

/**
 * Cancels the render and releases the session bitmap. Idempotent, and also
 * called from -dealloc. -currentImage returns nil afterwards.
 *
 * C++: ProgressiveRenderSession::Close() (progressive_render_session.h:40).
 */
- (void)close;

/**
 * Snapshot of the bitmap rendered so far, or nil once the session is closed.
 *
 * While the status is CPDFProgressiveRenderStatusToBeContinued this is an
 * intermediate frame — fine to show as a preview, not to save as final output.
 * Form and widget appearances are drawn only after the page content completes,
 * so they appear late.
 *
 * Each call copies the pixels out of the session bitmap, so it is safe to keep
 * the returned image after the next -continueRender.
 *
 * C++: ProgressiveRenderSession::GetBitmap() (progressive_render_session.h:43),
 * whose bitmap is owned by the session and must not be destroyed by the caller.
 */
- (CPDFKitPlatformImage *)currentImage;

@end
