//
//  CPDFOptimizeOption.h
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

@class CPDFDocument;

typedef NS_ENUM(int, CPDF_OPTIMIZE_FLAG) {
    CPDFOPTIMIZE_FLAG_RMNOTUSE = 1,                          // Whether to remove unused objects
    CPDFOPTIMIZE_FLAG_RMEPTOBJ = 1<<1,                       // Whether to remove empty objects
    CPDFOPTIMIZE_FLAG_RMSPEATTR = 1<<2,                      // Whether to remove special attributes
    CPDFOPTIMIZE_FLAG_RMEMBFONT = 1<<3,                      // Whether to remove embedded fonts
    CPDFOPTIMIZE_FLAG_RMINVALINK = 1<<4,                     // Whether to remove invalid links
    CPDFOPTIMIZE_FLAG_RMINVABK = 1<<5,                       // Whether to remove invalid bookmarks
    CPDFOPTIMIZE_FLAG_BCOMPRESSIMAGE = 1<<6,                 // Whether to compress images
    CPDFOPTIMIZE_FLAG_RMBK = 1<<7,                           // Whether to remove bookmarks
    CPDFOPTIMIZE_FLAG_RMANNOT = 1<<8,                        // Abandon all annotations
    CPDFOPTIMIZE_FLAG_RMFORM = 1<<9,                         // Abandon all forms
    CPDFOPTIMIZE_FLAG_RMMULMEDIA = 1<<10,                    // Abandon all multimedia
    CPDFOPTIMIZE_FLAG_RMDOCINFO = 1<<11,                     // Abandon document information
    CPDFOPTIMIZE_FLAG_RMMEDTADATA = 1<<12,                   // Abandon document metadata
    CPDFOPTIMIZE_FLAG_RMOBJDATA = 1<<13,                     // Abandon all object data
    CPDFOPTIMIZE_FLAG_RMFILEATTACHMENT = 1<<14,              // Abandon file attachments
    CPDFOPTIMIZE_FLAG_RMEXTERNCROSSREF = 1<<15,              // Abandon external cross-references
    CPDFOPTIMIZE_FLAG_RMOTHERAPPDATA = 1<<16,                // Abandon other application-specific data
    CPDFOPTIMIZE_FLAG_RMHIDERLAYER = 1<<17,                  // Abandon hidden layers
    CPDFOPTIMIZE_FLAG_MERGEVISIBLELAYER = 1<<18,             // Merge visible layers
    CPDFOPTIMIZE_FLAG_USEFLATE = 1<<19,                      // Use Flate encoding for unencoded streams
    CPDFOPTIMIZE_FLAG_FLAT_REPLACELZW = 1<<20,               // Replace LZW encoding with Flate encoding in streams
    CPDFOPTIMIZE_FLAG_RMUNUSEDTARGET = 1<<21,                // Abandon unused named targets
    CPDFOPTIMIZE_FLAG_OPTIMIZEPAGECONTENT = 1<<22,           // Optimize page content
    CPDFOPTIMIZE_FLAG_OPTIMIZEPDFFASTWEBVIEW = 1<<23,        // Optimize PDF for fast web viewing
    CPDFOPTIMIZE_FLAG_RMFORMCOMMITIMPORTRESETACTION = 1<<24, // Abandon all form submit, import, and reset actions
    CPDFOPTIMIZE_FLAG_RMJSACTION = 1<<25,                    // Abandon all JavaScript actions
    CPDFOPTIMIZE_FLAG_RMPAGETHUMBNAIL = 1<<26,               // Abandon embedded page thumbnails
    CPDFOPTIMIZE_FLAG_RMREPLACEIMAGE = 1<<27,                // Abandon replacement images
    CPDFOPTIMIZE_FLAG_RMLABEL = 1<<28,                       // Abandon document labels
    CPDFOPTIMIZE_FLAG_RMPRINTSETTINGS = 1<<29,               // Abandon print settings
    CPDFOPTIMIZE_FLAG_RMSEARCHINDEX = 1<<30,                 // Abandon search index
};

typedef NS_ENUM(unsigned char,CPDF_COMP_ALG) {
    CPDFCOMP_ALG_JPEG2000 = 1,
    CPDFCOMP_ALG_JPEG = 2,
    CPDFCOMP_ALG_JBIG2 = 3,
    CPDFCOMP_ALG_CCITT4 = 4,
    CPDFCOMP_ALG_CCITT3 = 5,
//    CPDFCOMP_ALG_ZIP 6 //no use
};

typedef struct _CPDFOptimizeImageOption {
    int uperPpi;
    int targetPpi;
    CPDF_COMP_ALG compAlg;
    int quality;
    int blockSize;
}CPDFOptimizeImageOption;


extern NSNotificationName const CPDFDocumentOptimizeProgressDidUpdateNotification;
extern NSString * const CPDFOptimizeProgressPageIndexKey;

extern NSString * const CPDFOptimizeCOLImageOptionKey;
extern NSString * const CPDFOptimizeGRAImageOptionKey;
extern NSString * const CPDFOptimizeMONImageOptionKey;

extern NSString * const CPDFOptimizeFlagKey;

@interface CPDFOptimizeOption : NSObject

#pragma mark - Accessors

/**
 * Returns the document with which the outline is associated.
 */
@property (nonatomic,readonly)  CPDFDocument *document;

/**
 * Image Option
 */
@property (nonatomic,readwrite) CPDFOptimizeImageOption col_imageOption;

/**
 * Reserved, temporarily ineffective Image Option
 */
@property (nonatomic,readwrite) CPDFOptimizeImageOption gra_imageOption;
@property (nonatomic,readwrite) CPDFOptimizeImageOption mon_imageOption;

/**
 * Image Quality
 */
@property (nonatomic,readwrite) float imageQuality;

/**
 * Optimize Flag
 */
@property (nonatomic,readwrite) CPDF_OPTIMIZE_FLAG optimizeflag;

/**
 * Cancel
 */
@property (nonatomic,readwrite) BOOL isCanceled;


- (instancetype)initWithDocument:(CPDFDocument *)document;

/**
 * Start Progress Monitor
 */
- (void)startProgressMonitor;

- (void)startCompress;

- (BOOL)saveAsCopyWithPath:(NSString *)path;

@end
