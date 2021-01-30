//
//  timing_interface.c
//  Foundation
//
//  Created by Евгений Лютц on 21.01.2020.
//  Copyright © 2020 Eugene Lutz. All rights reserved.
//

#include "private_interface.h"

double systemGetCurrentTime(SYSTEM* system)
{
	assert(system);
	return system->getCurrentTimeFunc();
}
