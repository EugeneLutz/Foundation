//
//  input_mouse.c
//  Foundation
//
//  Created by Евгений Лютц on 23.01.2020.
//  Copyright © 2020 Eugene Lutz. All rights reserved.
//

#include "private_interface.h"

MOUSE_ACTION inputMouseGetAction(INPUT_MOUSE* inputMouse)
{
	assert(inputMouse);
	return inputMouse->action;
}

MOUSE_KEY inputMouseGetKey(INPUT_MOUSE* inputMouse)
{
	assert(inputMouse);
	return inputMouse->key;
}

unsigned int inputMouseGetOtherKeyCode(INPUT_MOUSE* inputMouse)
{
	assert(inputMouse);
	return inputMouse->otherKeyCode;
}

float inputMouseGetXPosition(INPUT_MOUSE* inputMouse)
{
	assert(inputMouse);
	return inputMouse->xPosition;
}

float inputMouseGetYPosition(INPUT_MOUSE* inputMouse)
{
	assert(inputMouse);
	return inputMouse->yPosition;
}

float inputMouseGetXMove(INPUT_MOUSE* inputMouse)
{
	assert(inputMouse);
	return inputMouse->xMove;
}

float inputMouseGetYMove(INPUT_MOUSE* inputMouse)
{
	assert(inputMouse);
	return inputMouse->yMove;
}

float inputMouseGetXScroll(INPUT_MOUSE* inputMouse)
{
	assert(inputMouse);
	return inputMouse->xScroll;
}

float inputMouseGetYScroll(INPUT_MOUSE* inputMouse)
{
	assert(inputMouse);
	return inputMouse->yScroll;
}
