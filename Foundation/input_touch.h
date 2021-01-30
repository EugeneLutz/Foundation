//
//  input_touch.h
//  Foundation
//
//  Created by Евгений Лютц on 29.04.20.
//  Copyright © 2020 Eugene Lutz. All rights reserved.
//

#ifndef input_touch_h
#define input_touch_h

#include "private_interface.h"

typedef struct INPUT_TOUCH
{
	unsigned int index;
	TOUCH_ACTION action;
	vector2f startPosition;
	vector2f position;
	vector2f delta;
	float radius;
	float force;
}
INPUT_TOUCH;

#endif /* input_touch_h */
