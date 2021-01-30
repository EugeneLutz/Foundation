//
//  semaphore_interface.h
//  Foundation
//
//  Created by Евгений Лютц on 19.01.2020.
//  Copyright © 2020 Eugene Lutz. All rights reserved.
//

#ifndef semaphore_interface_h
#define semaphore_interface_h

#include "foundation.h"

SEMAPHORE* systemCreateSemaphore(SYSTEM* system, unsigned int value);
void semaphoreRelease(SEMAPHORE* semaphore);

void semaphoreEnter(SEMAPHORE* semaphore);
void semaphoreLeave(SEMAPHORE* semaphore);

#endif /* semaphore_interface_h */
