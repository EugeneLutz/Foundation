//
//  private_interface.h
//  Foundation
//
//  Created by Евгений Лютц on 06.11.20.
//  Copyright © 2020 Eugene Lutz. All rights reserved.
//

#ifndef foundation_private_interface_h
#define foundation_private_interface_h

#include "foundation.h"
#include "private_common.h"

// MARK: - Type declarations

typedef struct DATA_BLOCK DATA_BLOCK;

// MARK: - Private structures

#include "buffer.h"
#include "buffer_reader.h"
#include "buffer_writer.h"
#include "data_allocator.h"

#include "magic_dictionary_element.h"
#include "input_keyboard.h"
#include "tracking_keyboard_button.h"
#include "input_mouse.h"
#include "input_touch.h"
#include "input_command.h"
#include "input_responder.h"

#include "system.h"
#include "file_reader.h"
#include "semaphore.h"

// MARK: - Private interface

#include "buffer_private_interface.h"
#include "data_allocator_private_interface.h"
#include "tracking_keyboard_button_private_interface.h"

#endif /* foundation_private_interface_h */
