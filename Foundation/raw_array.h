//
//  raw_array.h
//  Foundation
//
//  Created by Евгений Лютц on 16.05.21.
//  Copyright © 2021 Eugene Lutz. All rights reserved.
//

#ifndef raw_array_h
#define raw_array_h

#include "foundation.h"

typedef struct RAW_ARRAY
{
	unsigned long itemSize;
	unsigned long capacityIncrement;
	unsigned long capacity;
	unsigned long length;
	void* items;	
}
RAW_ARRAY;

#endif /* raw_array_h */
