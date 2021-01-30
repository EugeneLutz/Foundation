//
//  system_interface.c
//  Foundation
//
//  Created by Евгений Лютц on 18.01.2020.
//  Copyright © 2020 Eugene Lutz. All rights reserved.
//

#include "private_interface.h"

#if defined(__APPLE__) && __APPLE__
#include "system_apple.h"
#endif


SYSTEM* systemCreateDefaultIfAvailable(void)
{
#if defined(__APPLE__) && __APPLE__
	return systemCreateDefaultApple();
#else
	return NULL;
#endif
}

void systemRelease(SYSTEM* system)
{
	assert(system);
	
	if (system->callbacksCreatedByDefault)
	{
#if defined(__APPLE__) && __APPLE__
		systemReleaseDefaultApple(system);
#endif
	}
}

void systemLog(SYSTEM* system, const char* message)
{
	assert(system);
	system->logFunc(message, system->userInfo);
}

void systemGetPathForResourceWithName(SYSTEM* system, STRING* outPath, const char* name, const char* type, EXECUTE_RESULT* executeResult)
{
	assert(system);
	assert(outPath);
	assert(name);
	assert(type);
	
	system->getPathForResourceWithNameAndTypeFunc(system, outPath, name, type, executeResult);
	if (executeResultIsFailed(executeResult)) {
		return;
	}
}
