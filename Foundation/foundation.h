//
//  foundation.h
//  Foundation
//
//  Created by Евгений Лютц on 18.01.2020.
//  Copyright © 2020 Eugene Lutz. All rights reserved.
//

#ifndef magic_foundation_h
#define magic_foundation_h

// HeaderDoc Reference by Justin Loew:
// http://www.cocoanutsdev.com/resources/headerdoc-reference-by-justin-loew

#ifdef __cplusplus
extern "C" {
#endif

// MARK: - Enumerations

#include "magic_array_item_distribution.h"
#include "magic_dictionary_element_type.h"

#include "input_types.h"
#include "key_action.h"
#include "key_button_type.h"
#include "mouse_action.h"
#include "mouse_key.h"
#include "touch_action.h"

#include "file_mode.h"

// MARK: - Type declarations

typedef struct EXECUTE_RESULT EXECUTE_RESULT;
typedef struct BUFFER BUFFER;
typedef struct BUFFER_READER BUFFER_READER;
typedef struct BUFFER_WRITER BUFFER_WRITER;
typedef struct DATA_ALLOCATOR DATA_ALLOCATOR;
typedef struct STRING STRING;
typedef struct MAGIC_ARRAY MAGIC_ARRAY;
typedef struct MAGIC_DICTIONARY MAGIC_DICTIONARY;

typedef struct INPUT_KEYBOARD INPUT_KEYBOARD;
typedef struct TRACKING_KEYBOARD_BUTTON TRACKING_KEYBOARD_BUTTON;
typedef struct INPUT_MOUSE INPUT_MOUSE;
typedef struct INPUT_TOUCH INPUT_TOUCH;
typedef struct INPUT_COMMAND INPUT_COMMAND;

/**
 * @abstract
 * User input responder handle.
 
 * @discussion
 * Input responder is meant to accept and delegate for further process user input information, for example, keyboard, mouse, gamepad input etc. You create this object by calling the @b inputResponderCreate function and release with @b inputResponderRelease. All accepted input data will be delegated to the @b delegate function specified in the  @b inputResponderCreate function.
 *
 * There are two ways to handle input information: handling input events and reading key state. For example, handling mouse input events is convenient for rotating in-game camera, while reading key state is convenient for character animation processing (e.g. play jump animation if space key is being pressed).
 */
typedef struct INPUT_RESPONDER INPUT_RESPONDER;

typedef struct FILE_READER FILE_READER;
typedef struct SEMAPHORE SEMAPHORE;
typedef struct SYSTEM SYSTEM;

// MARK: - Function declarations

#include "input_responder_delegate.h"
#include "system_functions.h"
#include "system_io_functions.h"
#include "thread_function.h"
#include "system_threading_functions.h"
#include "system_timing_functions.h"

// MARK: - Public structures

#include "execute_result.h"

#include "buffer_reader.h"
#include "buffer_writer.h"

#include "vector2f.h"
#include "vector3f.h"
#include "vector4f.h"
#include "quaternionf.h"
#include "matrix3f.h"
#include "matrix4f.h"
#include "ray.h"
#include "segment.h"
#include "frustum.h"

#include "data_block_item.h"
#include "magic_string.h"
#include "magic_array.h"
#include "magic_dictionary.h"

// MARK: - Public interface

#include "math_utils.h"
#include "routines.h"

#include "vector2f_interface.h"
#include "vector3f_interface.h"
#include "vector4f_interface.h"
#include "quaternionf_interface.h"
#include "matrix3f_interface.h"
#include "matrix4f_interface.h"
#include "ray_interface.h"
#include "segment_interface.h"
#include "frustum_interface.h"

#include "buffer_interface.h"
#include "buffer_reader_interface.h"
#include "buffer_writer_interface.h"
#include "data_allocator_public.h"
#include "magic_string_interface.h"
#include "magic_array_public.h"
#include "magic_dictionary_interface.h"
#include "execute_result_interface.h"

#include "input_keyboard_interface.h"
#include "tracking_keyboard_button_interface.h"
#include "input_mouse_interface.h"
#include "input_touch_interface.h"
#include "input_command_interface.h"
#include "input_responder_delegate.h"
#include "input_responder_interface.h"

#include "file_reader_interface.h"
#include "semaphore_interface.h"
#include "thread_interface.h"
#include "timing_interface.h"
#include "update_time_info.h"
#include "system_interface.h"

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* magic_foundation_h */
