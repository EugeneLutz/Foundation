//
//  system_threading_functions.h
//  Foundation
//
//  Created by Евгений Лютц on 19.01.2020.
//  Copyright © 2020 Eugene Lutz. All rights reserved.
//

#ifndef system_threading_functions_h
#define system_threading_functions_h

#include "foundation.h"

typedef void* (* SEMAPHORE_CREATE_FUNC)(unsigned int size);
typedef void (* SEMAPHORE_RELEASE_FUNC)(void* semaphore);

typedef void (* SEMAPHORE_ENTER_FUNC)(void* semaphore);
typedef void (* SEMAPHORE_LEAVE_FUNC)(void* semaphore);


typedef void (* THREAD_DISPATCH_FUNC)(void* thread, THREAD_FUNCTION_FUNC threadFunction, THREAD_PRIORITY priority, void* threadData, /*void* userInfo,*/ EXECUTE_RESULT* executeResult);

#endif /* system_threading_functions_h */
