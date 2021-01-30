//
//  timing_apple.m
//  Foundation
//
//  Created by Евгений Лютц on 21.01.2020.
//  Copyright © 2020 Eugene Lutz. All rights reserved.
//

#import <QuartzCore/QuartzCore.h>
#include "private_interface.h"

static double default_internal_timingGetCurrentTime(void)
{
	return (double)CACurrentMediaTime();
}

void systemInitTimingFunctionsApple(SYSTEM* system)
{
	assert(system);
	
	system->getCurrentTimeFunc = default_internal_timingGetCurrentTime;
}
