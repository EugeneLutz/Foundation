//
//  mouse_action.h
//  Foundation
//
//  Created by Евгений Лютц on 20.01.2020.
//  Copyright © 2020 Eugene Lutz. All rights reserved.
//

#ifndef mouse_action_h
#define mouse_action_h

#include "foundation.h"

typedef enum MOUSE_ACTION
{
	MOUSE_ACTION_DOWN = 0,
	MOUSE_ACTION_UP,
	MOUSE_ACTION_MOVE,
	MOUSE_ACTION_SCROLL
}
MOUSE_ACTION;

#endif /* mouse_action_h */
