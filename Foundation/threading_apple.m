//
//  threading_apple.m
//  Foundation
//
//  Created by Евгений Лютц on 19.01.2020.
//  Copyright © 2020 Eugene Lutz. All rights reserved.
//

#import <Foundation/Foundation.h>
#include "private_interface.h"

void* default_semaphoreCreate(unsigned int size)
{
	dispatch_semaphore_t semaphore = dispatch_semaphore_create(size);
	return (__bridge_retained void*)semaphore;
}

void default_semaphoreRelease(void* semaphore)
{
	assert(semaphore);
	dispatch_semaphore_t oc_semaphore = (__bridge_transfer dispatch_semaphore_t)semaphore;
	oc_semaphore = nil;
	
	// Counted automatically?
	// https://developer.apple.com/documentation/dispatch/1496328-dispatch_release
	//dispatch_release(oc_semaphore);
}

void default_semaphoreEnter(void* semaphore)
{
	assert(semaphore);
	
	dispatch_semaphore_t sema = (__bridge dispatch_semaphore_t)semaphore;
	dispatch_semaphore_wait(sema, DISPATCH_TIME_FOREVER);
}

void default_semaphoreLeave(void* semaphore)
{
	assert(semaphore);
	
	dispatch_semaphore_t sema = (__bridge dispatch_semaphore_t)semaphore;
	dispatch_semaphore_signal(sema);
}

void default_threadDispatch(void* thread, THREAD_FUNCTION_FUNC threadFunction, THREAD_PRIORITY priority, void* threadData, EXECUTE_RESULT* executeResult)
{
	assert(threadFunction);
	
	dispatch_queue_t globalQueue = dispatch_get_global_queue(QOS_CLASS_USER_INITIATED, 0);
	dispatch_async(globalQueue, ^{
		threadFunction(priority, threadData);
	});
}

void systemInitThreadingFunctionsApple(SYSTEM* system)
{
	assert(system);
	
	system->semaphoreCreateFunc = default_semaphoreCreate;
	system->semaphoreReleaseFunc = default_semaphoreRelease;
	system->semaphoreEnterFunc = default_semaphoreEnter;
	system->semaphoreLeaveFunc = default_semaphoreLeave;
	system->threadDispatchFunc = default_threadDispatch;
}
