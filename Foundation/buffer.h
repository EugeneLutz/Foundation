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
	/// Determines whether @b data was created by it's buffer constructor or was it refenced from ohter place.
	int referenced;
	
	unsigned long capacity;
	unsigned long length;
	char* data;
}
BUFFER;

#endif /* buffer_h */
