//
//  input_command_interface.h
//  Foundation
//
//  Created by Евгений Лютц on 23.01.2020.
//  Copyright © 2020 Eugene Lutz. All rights reserved.
//

#ifndef input_command_interface_h
#define input_command_interface_h

#include "foundation.h"

INPUT_COMMAND_TYPE inputCommandGetInputType(INPUT_COMMAND* inputCommand);
INPUT_KEYBOARD* inputCommandGetKeyboardInput(INPUT_COMMAND* inputCommand);
INPUT_MOUSE* inputCommandGetMouseInput(INPUT_COMMAND* inputCommand);
INPUT_TOUCH* inputCommandGetTouchInput(INPUT_COMMAND* inputCommand);
double inputCommandGetInputTime(INPUT_COMMAND* inputCommand);

#endif /* input_command_interface_h */
