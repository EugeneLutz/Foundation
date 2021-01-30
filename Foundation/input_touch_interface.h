//
//  input_touch_interface.h
//  Foundation
//
//  Created by Евгений Лютц on 29.04.20.
//  Copyright © 2020 Eugene Lutz. All rights reserved.
//

#ifndef input_touch_interface_h
#define input_touch_interface_h

#include "foundation.h"

unsigned int touchInputGetIndex(INPUT_TOUCH* touchInput);
TOUCH_ACTION touchInputGetAction(INPUT_TOUCH* touchInput);
vector2f touchInputGetStartPosition(INPUT_TOUCH* touchInput);
vector2f touchInputGetPosition(INPUT_TOUCH* touchInput);
vector2f touchInputGetDelta(INPUT_TOUCH* touchInput);
float touchInputGetRadius(INPUT_TOUCH* touchInput);
float touchInputGetForce(INPUT_TOUCH* touchInput);

#endif /* input_touch_interface_h */
