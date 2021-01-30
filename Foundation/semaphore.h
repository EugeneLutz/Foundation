//
//  semaphore.h
//  Foundation
//
//  Created by Евгений Лютц on 19.01.2020.
//  Copyright © 2020 Eugene Lutz. All rights reserved.
//

#ifndef semaphore_h
#define semaphore_h

#include "private_interface.h"

typedef struct SEMAPHORE
{
	SYSTEM* system;
	void* data;
}
SEMAPHORE;

#endif /* semaphore_h */
