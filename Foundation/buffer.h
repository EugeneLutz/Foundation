//
//  buffer.h
//  Foundation
//
//  Created by Евгений Лютц on 31.12.20.
//  Copyright © 2020 Eugene Lutz. All rights reserved.
//

#ifndef buffer_h
#define buffer_h

#include "private_interface.h"

typedef struct BUFFER
{
	unsigned long capacity;
	unsigned long length;
	unsigned long numReferences;
	char* data;
}
BUFFER;

#endif /* buffer_h */
