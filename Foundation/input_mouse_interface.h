//
//  input_mouse_interface.h
//  Foundation
//
//  Created by Евгений Лютц on 23.01.2020.
//  Copyright © 2020 Eugene Lutz. All rights reserved.
//

#ifndef input_mouse_interface_h
#define input_mouse_interface_h

#include "foundation.h"


MOUSE_ACTION inputMouseGetAction(INPUT_MOUSE* inputMouse);
MOUSE_KEY inputMouseGetKey(INPUT_MOUSE* inputMouse);
unsigned int inputMouseGetOtherKeyCode(INPUT_MOUSE* inputMouse);
float inputMouseGetXPosition(INPUT_MOUSE* inputMouse);
float inputMouseGetYPosition(INPUT_MOUSE* inputMouse);
float inputMouseGetXMove(INPUT_MOUSE* inputMouse);
float inputMouseGetYMove(INPUT_MOUSE* inputMouse);
float inputMouseGetXScroll(INPUT_MOUSE* inputMouse);
float inputMouseGetYScroll(INPUT_MOUSE* inputMouse);

#endif /* input_mouse_interface_h */
