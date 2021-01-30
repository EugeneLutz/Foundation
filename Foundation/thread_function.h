//
//  thread_function.h
//  Foundation
//
//  Created by Евгений Лютц on 20.01.2020.
//  Copyright © 2020 Eugene Lutz. All rights reserved.
//

#ifndef thread_function_h
#define thread_function_h

#include "foundation.h"

typedef enum THREAD_PRIORITY
{
	THREAD_PRIORITY_LOW = 0,
	THREAD_PRIORITY_NORMAL,
	THREAD_PRIORITY_HIGH
}
THREAD_PRIORITY;

typedef void (* THREAD_FUNCTION_FUNC)(THREAD_PRIORITY priority, void* userInfo);

#endif /* thread_function_h */
