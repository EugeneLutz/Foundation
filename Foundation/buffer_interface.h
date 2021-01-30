//
//  buffer_interface.h
//  Foundation
//
//  Created by Евгений Лютц on 31.12.20.
//  Copyright © 2020 Eugene Lutz. All rights reserved.
//

#ifndef buffer_interface_h
#define buffer_interface_h

#include "foundation.h"

BUFFER* bufferCreate(unsigned long length);
BUFFER* bufferCreateFromContentsOfFile(SYSTEM* system, const char* path, EXECUTE_RESULT* executeResult);
BUFFER* bufferCreateFromContentsOfResourceFile(SYSTEM* system, const char* name, const char* type, EXECUTE_RESULT* executeResult);
void bufferRelease(BUFFER* buffer);

unsigned long bufferGetLength(BUFFER* buffer);

#endif /* buffer_interface_h */
