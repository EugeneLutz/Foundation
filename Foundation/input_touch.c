//
//  input_touch.c
//  Foundation
//
//  Created by Евгений Лютц on 29.04.20.
//  Copyright © 2020 Eugene Lutz. All rights reserved.
//

#include "private_interface.h"

unsigned int touchInputGetIndex(INPUT_TOUCH* touchInput)
{
	assert(touchInput);
	return touchInput->index;
}

TOUCH_ACTION touchInputGetAction(INPUT_TOUCH* touchInput)
{
	assert(touchInput);
	return touchInput->action;
}

vector2f touchInputGetStartPosition(INPUT_TOUCH* touchInput)
{
	assert(touchInput);
	return touchInput->startPosition;
}

vector2f touchInputGetPosition(INPUT_TOUCH* touchInput)
{
	assert(touchInput);
	return touchInput->position;
}

vector2f touchInputGetDelta(INPUT_TOUCH* touchInput)
{
	assert(touchInput);
	return touchInput->delta;
}

float touchInputGetRadius(INPUT_TOUCH* touchInput)
{
	assert(touchInput);
	return touchInput->radius;
}

float touchInputGetForce(INPUT_TOUCH* touchInput)
{
	assert(touchInput);
	return touchInput->force;
}
