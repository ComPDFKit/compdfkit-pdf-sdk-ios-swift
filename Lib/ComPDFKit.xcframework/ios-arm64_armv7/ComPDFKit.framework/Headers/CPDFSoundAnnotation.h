//
//  CPDFSoundAnnotation.h
//  ComPDFKit
//
//  Copyright © 2014-2024 PDF Technologies, Inc. All Rights Reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE ComPDFKit LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <ComPDFKit/CPDFAnnotation.h>

/**
 * A CPDFSoundAnnotation object shall analogous to a text annotation except that instead of a text note, it contains sound recorded from the computer’s microphone or imported from a file.
 */
@interface CPDFSoundAnnotation : CPDFAnnotation

@property (nonatomic,assign) BOOL isPlaying;

- (NSString *)mediaPath;
- (BOOL)setMediaPath:(NSString *)path;

@end
