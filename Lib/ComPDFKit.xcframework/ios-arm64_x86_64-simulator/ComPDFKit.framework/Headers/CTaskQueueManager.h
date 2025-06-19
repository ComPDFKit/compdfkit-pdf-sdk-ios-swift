//
//  CTaskQueueManager.h
//  ComPDFKit
//
//  Created by lizhe on 2024/11/5.
//  Copyright © 2024 Kdan Mobile. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

static void *kHighPriorityQueueKey = &kHighPriorityQueueKey;

static void *kSearchHighPriorityQueueKey = &kSearchHighPriorityQueueKey;

@interface CTaskQueueManager : NSObject
+ (instancetype)sharedManager;

// 提交异步任务
- (void)submitAsyncTask:(dispatch_block_t)task;

- (void)submitSearchAsyncTask:(dispatch_block_t)task;

// 提交同步任务（自动避免死锁）
- (void)submitSyncTask:(dispatch_block_t)task;

+ (dispatch_queue_t)pdfReloadQueue;

@end

NS_ASSUME_NONNULL_END
