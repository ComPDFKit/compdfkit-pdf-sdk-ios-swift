//
//  CTaskQueueManager.h
//  ComPDFKit
//
//  Copyright © 2014-2026 PDF Technologies, Inc. All Rights Reserved.
//
//  THIS SOURCE CODE AND ANY ACCOMPANYING DOCUMENTATION ARE PROTECTED BY INTERNATIONAL COPYRIGHT LAW
//  AND MAY NOT BE RESOLD OR REDISTRIBUTED. USAGE IS BOUND TO THE ComPDFKit LICENSE AGREEMENT.
//  UNAUTHORIZED REPRODUCTION OR DISTRIBUTION IS SUBJECT TO CIVIL AND CRIMINAL PENALTIES.
//  This notice may not be removed from this file.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

static void *kHighPriorityQueueKey = &kHighPriorityQueueKey;

static void *kSearchHighPriorityQueueKey = &kSearchHighPriorityQueueKey;

@interface CTaskQueueManager : NSObject
+ (instancetype)sharedManager;

- (void)submitAsyncTask:(dispatch_block_t)task;

- (void)submitSearchAsyncTask:(dispatch_block_t)task;

- (void)submitSyncTask:(dispatch_block_t)task;

+ (dispatch_queue_t)pdfReloadQueue;

@end

NS_ASSUME_NONNULL_END
