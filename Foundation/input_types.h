//
//  input_types.h
//  Foundation
//
//  Created by Евгений Лютц on 20.01.2020.
//  Copyright © 2020 Eugene Lutz. All rights reserved.
//

#ifndef input_types_h
#define input_types_h

#include "foundation.h"

typedef enum INPUT_COMMAND_TYPE
{
	INPUT_COMMAND_TYPE_KEYBOARD = 0,
	INPUT_COMMAND_TYPE_MOUSE,
	INPUT_COMMAND_TYPE_TOUCH,
	//INPUT_COMMAND_TYPE_GAMEPAD
}
INPUT_COMMAND_TYPE;

#define INPUT_MODIFIER_SHIFT	(0b0000000000000001)
//#define INPUT_MODIFIER_LSHIFT	(0b0000000000000001)
//#define INPUT_MODIFIER_RSHIFT	(0b0000000000000011)

#define INPUT_MODIFIER_CONTROL	(0b0000000000000100)
//#define INPUT_MODIFIER_LCONTROL	(0b0000000000000100)
//#define INPUT_MODIFIER_RCONTROL	(0b0000000000001100)

#define INPUT_MODIFIER_OPTION	(0b0000000000010000)
//#define INPUT_MODIFIER_LOPTION	(0b0000000000010000)
//#define INPUT_MODIFIER_ROPTION	(0b0000000000110000)

#define INPUT_MODIFIER_COMMAND	(0b0000000001000000)
//#define INPUT_MODIFIER_LCOMMAND	(0b0000000001000000)
//#define INPUT_MODIFIER_RCOMMAND	(0b0000000011000000)

#define INPUT_MODIFIER_FUNCTION	(0b0000000100000000)
//#define INPUT_MODIFIER_LFUNCTION	(0b0000000100000000)
//#define INPUT_MODIFIER_RFUNCTION	(0b0000001100000000)

#define INPUT_MODIFIER_CAPSLOCK	(0b0000010000000000)
//#define INPUT_MODIFIER_LCAPSLOCK	(0b0000010000000000)
//#define INPUT_MODIFIER_RCAPSLOCK	(0b0000110000000000)

#endif /* input_types_h */
