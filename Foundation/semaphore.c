//
//  semaphore.c
//  Foundation
//
//  Created by Евгений Лютц on 19.01.2020.
//  Copyright © 2020 Eugene Lutz. All rights reserved.
//

#include "private_interface.h"

SEMAPHORE* systemCreateSemaphore(SYSTEM* system, unsigned int value)
{
	assert(system);
	
	void* sema = system->semaphoreCreateFunc(value);
	assert(sema);
	
	SEMAPHORE* semaphore = malloc(sizeof(SEMAPHORE));
	semaphore->system = system;
	semaphore->data = sema;
		
	return semaphore;
}

void semaphoreRelease(SEMAPHORE* semaphore)
{
	assert(semaphore);
	
	semaphore->system->semaphoreReleaseFunc(semaphore->data);
	
	free(semaphore);
}

void semaphoreEnter(SEMAPHORE* semaphore)
{
	assert(semaphore);
	semaphore->system->semaphoreEnterFunc(semaphore->data);
}

void semaphoreLeave(SEMAPHORE* semaphore)
{
	assert(semaphore);
	semaphore->system->semaphoreLeaveFunc(semaphore->data);
}
