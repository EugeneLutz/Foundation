//
//  buffer_private_interface.h
//  Foundation
//
//  Created by Евгений Лютц on 01.01.21.
//  Copyright © 2021 Eugene Lutz. All rights reserved.
//

#ifndef buffer_private_interface_h
#define buffer_private_interface_h

#include "private_interface.h"

void bufferInitialize(BUFFER* buffer, unsigned long capacity);
void bufferDeinitialize(BUFFER* buffer);

/// Makes sure that buffer has enough length. It buffer's length is not sufficient, then it grows.
void bufferRequestSize(BUFFER* buffer, unsigned long length);

#endif /* buffer_private_interface_h */
