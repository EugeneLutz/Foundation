//
//  data_block_item.h
//  Foundation
//
//  Created by Евгений Лютц on 01.01.21.
//  Copyright © 2021 Eugene Lutz. All rights reserved.
//

#ifndef data_block_item_h
#define data_block_item_h

#include "foundation.h"

typedef struct DATA_BLOCK_ITEM
{
	unsigned long dataBlockIndex;
	unsigned long itemIndex;
	void* data;
}
DATA_BLOCK_ITEM;

#endif /* data_block_item_h */
