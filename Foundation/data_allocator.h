//
//  data_allocator.h
//  Foundation
//
//  Created by Евгений Лютц on 01.01.21.
//  Copyright © 2021 Eugene Lutz. All rights reserved.
//

#ifndef data_allocator_h
#define data_allocator_h

#include "private_interface.h"

typedef struct DATA_BLOCK
{
	/// Index of the first available item or dataBlock
	unsigned long firstAvailableItem;
	
	/// Determines which item (@e data or @e dataBlocks arrays) is available (value is @b 1 ) or not (value is @b 0 ). Size of this array is always equals to the owner's @b dataBlockCapacity property.
	char* engagedItems;
	
	union
	{
		/// Static array of items, each has size of owner's @b itemSize. Size of this array is always equals to the owner's @b dataBlockCapacity property.
		void* data;
		
		/// Dynamic array of data blocks.
		DATA_BLOCK* dataBlocks;
	};
}
DATA_BLOCK;

typedef struct DATA_ALLOCATOR
{
	unsigned int itemSize;
	unsigned int dataBlockCapacity;
	unsigned int numDataBlocks;
	
	/**
	 @abstract dataBlocksContainer.
	 */
	DATA_BLOCK dataBlocksContainer;
}
DATA_ALLOCATOR;

#endif /* data_allocator_h */
