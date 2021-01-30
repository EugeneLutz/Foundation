//
//  system_apple.m
//  Foundation
//
//  Created by Евгений Лютц on 10.03.2020.
//  Copyright © 2020 Eugene Lutz. All rights reserved.
//

#include "system_apple.h"
#import <Foundation/Foundation.h>

typedef struct SYSTEM_APPLE
{
	// some data
}
SYSTEM_APPLE;

static void _systemLogFuncApple(const char* message, void* userInfo)
{
	NSLog(@"%s", message);
}

SYSTEM* systemCreateDefaultApple(void)
{
	SYSTEM* system = malloc(sizeof(SYSTEM));	
	system->callbacksCreatedByDefault = 1;
	system->logFunc = _systemLogFuncApple;
	systemInitIOFunctionsApple(system);
	systemInitThreadingFunctionsApple(system);
	systemInitTimingFunctionsApple(system);
	system->userInfo = NULL;
	
	return system;
}

void systemReleaseDefaultApple(SYSTEM* system)
{
	assert(system);
	
	free(system);
}
