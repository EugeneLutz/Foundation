//
//  input_mouse.h
//  Foundation
//
//  Created by Евгений Лютц on 20.01.2020.
//  Copyright © 2020 Eugene Lutz. All rights reserved.
//

#ifndef input_mouse_h
#define input_mouse_h

#include "private_interface.h"

typedef struct INPUT_MOUSE
{
	MOUSE_ACTION action;
	MOUSE_KEY key;
	unsigned int otherKeyCode;
	float xPosition;
	float yPosition;
	float xMove;
	float yMove;
	float xScroll;
	float yScroll;
}
INPUT_MOUSE;

#endif /* input_mouse_h */
