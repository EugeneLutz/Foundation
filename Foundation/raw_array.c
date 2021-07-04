//
//  raw_array.c
//  Foundation
//
//  Created by Евгений Лютц on 16.05.21.
//  Copyright © 2021 Eugene Lutz. All rights reserved.
//

#include "private_interface.h"

// TODO: implement

void rawArrayInitialize(RAW_ARRAY* array, unsigned long itemSize, unsigned long capacityIncrement)
{
	assert(array);
	
	array->itemSize = itemSize;
	array->capacityIncrement = capacityIncrement;
	array->capacity = capacityIncrement;
	array->length = 0;
	array->items = malloc(array->itemSize * array->capacity);
}

void rawArrayDeinitialize(RAW_ARRAY* array)
{
	assert(array);
	
	free(array->items);
}


RAW_ARRAY* rawArrayCreate(unsigned long itemSize, unsigned long capacityIncrement)
{
	RAW_ARRAY* array = malloc(sizeof(RAW_ARRAY));
	rawArrayInitialize(array, itemSize, capacityIncrement);
	return array;
}

void rawArrayRelease(RAW_ARRAY* array)
{
	assert(array);
	rawArrayDeinitialize(array);
	free(array);
}


void* rawArrayAddItem(RAW_ARRAY* array)
{
	assert(array);
	
	void* item = ((char*)array->items) + array->itemSize * array->length;
	
	array->length++;
	assert(array->length < array->capacity);
	return item;
}

void* rawArrayGetItem(RAW_ARRAY* array, unsigned long itemIndex)
{
	assert(array);
	
	// TODO: increase array size here
	assert(itemIndex < array->length);
	
	return ((char*)array->items) + array->itemSize * itemIndex;
}

void* rawArrayGetData(RAW_ARRAY* array)
{
	assert(array);
	
	return array->items;
}

void rawArrayRemoveItemByIndex(RAW_ARRAY* array, unsigned long itemIndex)
{
	assert(array);
	
	unsigned long moveLength = array->length - 1 - itemIndex;
	array->length--;
	
	if (moveLength > 0)
	{
		void* dst = ((char*)array->items) + array->itemSize * itemIndex;
		void* src = ((char*)dst) + array->itemSize;
		memmove(dst, src, moveLength);
	}
}

void rawArrayRemoveItem(RAW_ARRAY* array, void* item)
{
	assert(array);
	
	for (unsigned long i = 0; i < array->length; i++)
	{
		void* currentItem = ((char*)array->items) + array->itemSize * i;
		if (currentItem == item)
		{
			rawArrayRemoveItemByIndex(array, i);
			return;
		}
	}
}

void rawArrayClear(RAW_ARRAY* array)
{
	assert(array);
	
	array->length = 0;
}
