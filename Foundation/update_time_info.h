//
//  update_time_info.h
//  Foundation
//
//  Created by Евгений Лютц on 26.01.2020.
//  Copyright © 2020 Eugene Lutz. All rights reserved.
//

#ifndef update_time_info_h
#define update_time_info_h

#include "foundation.h"

/**
 * @abstract
 * Update time informaton.
 *
 * @discussion
 * This structure is suitable for update loops which use time information to update some data.
 */
typedef struct UPDATE_TIME_INFO
{
	double startTime;
	double lastTime;
	double currentTime;
	double timeElapsed;
	//float timeElapsedFloat;
}
UPDATE_TIME_INFO;

#endif /* update_time_info_h */
