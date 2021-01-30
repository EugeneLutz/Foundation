//
//  touch_action.h
//  Foundation
//
//  Created by Евгений Лютц on 29.04.20.
//  Copyright © 2020 Eugene Lutz. All rights reserved.
//

#ifndef touch_action_h
#define touch_action_h

#include "foundation.h"

typedef enum TOUCH_ACTION
{
	TOUCH_ACTION_DOWN = 0,
	TOUCH_ACTION_UP,
	TOUCH_ACTION_MOVE,
	TOUCH_ACTION_CANCEL
}
TOUCH_ACTION;

#endif /* touch_action_h */
