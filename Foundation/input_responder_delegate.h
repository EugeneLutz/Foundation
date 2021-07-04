//
//  input_responder_delegate.h
//  Foundation
//
//  Created by Евгений Лютц on 20.01.2020.
//  Copyright © 2020 Eugene Lutz. All rights reserved.
//

#ifndef input_responder_delegate_h
#define input_responder_delegate_h

#include "foundation.h"

/**
 @abstract Callback for responding to input commands.
 @return @b 0 if command should be accumulated (see @e inputResponderResetInput for more information), otherwise @b 1. TODO: implement this in input_responder.c
 */
typedef int (* INPUT_RESPONDER_DELEGATE_FUNC)(INPUT_COMMAND* command, void* userInfo);

#endif /* input_responder_delegate_h */
