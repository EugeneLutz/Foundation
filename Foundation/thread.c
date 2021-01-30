//
//  thread.c
//  Foundation
//
//  Created by Евгений Лютц on 20.01.2020.
//  Copyright © 2020 Eugene Lutz. All rights reserved.
//

#include "private_interface.h"

void systemDispatchThread(SYSTEM* system, THREAD_PRIORITY priority, THREAD_FUNCTION_FUNC threadFunction, void* threadData, /*sf_nullable*/ EXECUTE_RESULT* executeResult)
{
	assert(system);
	
	system->threadDispatchFunc(NULL, threadFunction, priority, threadData, executeResult);
}
