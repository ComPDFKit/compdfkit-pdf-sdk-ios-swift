//
//  CPDFKitPlatform.h
//  ComPDFKit
//
//  Copyright © 2014-2024 PDF Technologies, Inc. All Rights Reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE ComPDFKit LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#ifndef CPDFKitPlatform_h
#define CPDFKitPlatform_h

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>

#if TARGET_OS_IPHONE

#import <UIKit/UIKit.h>

#define CPDFKitPlatformColor        UIColor
#define CPDFKitPlatformImage        UIImage
#define CPDFKitPlatformFont         UIFont
#define CPDFKitPlatformEdgeInsets   UIEdgeInsets

#elif TARGET_OS_MAC

#import <Cocoa/Cocoa.h>

#define CPDFKitPlatformColor        NSColor
#define CPDFKitPlatformImage        NSImage
#define CPDFKitPlatformFont         NSFont
#define CPDFKitPlatformEdgeInsets   NSEdgeInsets

#endif

#endif /* CPDFKitPlatform_h */
