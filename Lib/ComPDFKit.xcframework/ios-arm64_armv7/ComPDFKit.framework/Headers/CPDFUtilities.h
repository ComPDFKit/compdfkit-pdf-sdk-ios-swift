//
//  CPDFUtilities.h
//  ComPDFKit
//
//  Copyright © 2014-2024 PDF Technologies, Inc. All Rights Reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE ComPDFKit LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#ifndef CPDFUtilities_h
#define CPDFUtilities_h

#define C_Cache_Folder             [NSSearchPathForDirectoriesInDomains(NSCachesDirectory, NSUserDomainMask, YES) firstObject]
#define CPDFKiC_Cache_Folder       [C_Cache_Folder stringByAppendingPathComponent:@"CPDFKitCache"]
#define CPDFKit_Cache_Image_Folder [CPDFKiC_Cache_Folder stringByAppendingPathComponent:@"Image"]
#define CPDFKit_Cache_PDF_Folder   [CPDFKiC_Cache_Folder stringByAppendingPathComponent:@"PDF"]
#define CPDFKit_Cache_Media_Folder [CPDFKiC_Cache_Folder stringByAppendingPathComponent:@"Media"]

#endif /* CPDFUtilities_h */
