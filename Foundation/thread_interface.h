//
//  thread_interface.h
//  Foundation
//
//  Created by Евгений Лютц on 20.01.2020.
//  Copyright © 2020 Eugene Lutz. All rights reserved.
//

#ifndef thread_interface_h
#define thread_interface_h

#include "foundation.h"

void systemDispatchThread(SYSTEM* system, THREAD_PRIORITY priority, THREAD_FUNCTION_FUNC threadFunction, void* threadData, EXECUTE_RESULT* executeResult);

#endif /* thread_interface_h */
