//
//  magic_array.c
//  Foundation
//
//  Created by Евгений Лютц on 06.11.20.
//  Copyright © 2020 Eugene Lutz. All rights reserved.
//

#include "private_interface.h"

MAGIC_ARRAY* magicArrayCreateWithAllocator(DATA_ALLOCATOR* allocator, unsigned int capacityIncrement)
{
	assert(allocator);
	MAGIC_ARRAY* magicArray = malloc(sizeof(MAGIC_ARRAY));
	magicArrayInitializeWithAllocator(magicArray, allocator, capacityIncrement);
	return magicArray;
}

MAGIC_ARRAY* magicArrayCreate(unsigned int itemSize, unsigned int sizeIncrement)
{
	MAGIC_ARRAY* magicArray = malloc(sizeof(MAGIC_ARRAY));
	magicArrayInitialize(magicArray, itemSize, sizeIncrement);
	return magicArray;
}


void magicArrayInitializeWithAllocator(MAGIC_ARRAY* magicArray, DATA_ALLOCATOR* allocator, unsigned int capacityIncrement)
{
	assert(magicArray);
	assert(allocator);
	
	magicArray->capaciryIncrement = capacityIncrement;
	magicArray->capacity = magicArray->capaciryIncrement;
	magicArray->length = 0;
	magicArray->allocatorIsReferenced = 1;
	magicArray->allocator = allocator;
	
	// allocate memory for a bit faster element access
	magicArray->elements = malloc(sizeof(DATA_BLOCK_ITEM) * magicArray->capacity);
}

void magicArrayInitialize(MAGIC_ARRAY* magicArray, unsigned int itemSize, unsigned int capacityIncrement)
{
	assert(magicArray);
	assert(itemSize > 0);
	assert(capacityIncrement > 0);
	
	magicArray->capaciryIncrement = capacityIncrement;
	magicArray->capacity = capacityIncrement;
	magicArray->length = 0;
	magicArray->allocatorIsReferenced = 0;
	magicArray->allocator = NULL;
	
	magicArray->elements = malloc(sizeof(DATA_BLOCK_ITEM) * magicArray->capacity);
	magicArray->allocator = dataAllocatorCreate(itemSize, capacityIncrement);
}

void magicArrayDeinitialize(MAGIC_ARRAY* magicArray)
{
	assert(magicArray);
		
	if (magicArray->allocatorIsReferenced)
	{
		for (unsigned long i = 0; i < magicArray->length; i++)
		{
			DATA_BLOCK_ITEM* item = magicArray->elements + i;
			dataAllocatorRemoveItem(magicArray->allocator, item);
		}
	}
	else
	{
		dataAllocatorRelease(magicArray->allocator);
	}
	free(magicArray->elements);
	
	debug_memset(magicArray, 0, sizeof(MAGIC_ARRAY));
}

void magicArrayRelease(MAGIC_ARRAY* magicArray)
{
	magicArrayDeinitialize(magicArray);
	free(magicArray);
}


void magicArrayClear(MAGIC_ARRAY* magicArray)
{
	assert(magicArray);
	
	if (magicArray->length == 0) {
		return;
	}
	
	if (magicArray->allocatorIsReferenced)
	{
		for (unsigned long i = 0; i < magicArray->length; i++)
		{
			DATA_BLOCK_ITEM* item = magicArray->elements + i;
			dataAllocatorRemoveItem(magicArray->allocator, item);
		}
	}
	else
	{
		dataAllocatorReset(magicArray->allocator);
	}
	
	magicArray->length = 0;
}


unsigned int magicArrayGetLength(MAGIC_ARRAY* magicArray)
{
	assert(magicArray);
	return magicArray->length;
}

static DATA_BLOCK_ITEM _magicArray_addUnorderedItem(MAGIC_ARRAY* magicArray)
{
	// Receive new item from data allocator
	DATA_BLOCK_ITEM item;
	dataAllocatorAddItem(magicArray->allocator, &item);
	magicArray->length++;
	
	if (magicArray->length >= magicArray->capacity)
	{
		magicArray->capacity += magicArray->capaciryIncrement;
		magicArray->elements = realloc(magicArray->elements, sizeof(DATA_BLOCK_ITEM) * magicArray->capacity);
		assert(magicArray->elements);
	}
	
	debug_memset(item.data, 0, magicArray->allocator->itemSize);
	
	return item;
}

void* magicArrayAddItem(MAGIC_ARRAY* magicArray)
{
	assert(magicArray);
	
	DATA_BLOCK_ITEM item = _magicArray_addUnorderedItem(magicArray);
	magicArray->elements[magicArray->length - 1] = item;
	return item.data;
}

void* magicArrayInsertItem(MAGIC_ARRAY* magicArray, unsigned int itemIndex)
{
	assert(magicArray);
	assert(itemIndex < magicArray->length + 1);
	
	// 1. Create a new element
	DATA_BLOCK_ITEM item = _magicArray_addUnorderedItem(magicArray);
	
	// 2. Shift values in element array
	for (unsigned int i = magicArray->length - 1; i > itemIndex; i--)
	{
		magicArray->elements[i] = magicArray->elements[i - 1];
	}
	
	// 3. Set the element value
	magicArray->elements[itemIndex] = item;
	
	return item.data;
}

void magicArrayRemoveItemByIndex(MAGIC_ARRAY* magicArray, unsigned long itemIndex)
{
	assert(magicArray);
	assert(itemIndex < magicArray->length);
	
	DATA_BLOCK_ITEM* magicItem = &magicArray->elements[itemIndex];
	
	dataAllocatorRemoveItem(magicArray->allocator, magicItem);
	
	// Don't ever vanish memory here!!!
	//debug_memset(magicItem->data, 0, magicArray->allocator->itemSize);
	
	// Shift elements
	for (unsigned long i = itemIndex + 1; i < magicArray->length; i++)
	{
		magicArray->elements[i - 1] = magicArray->elements[i];
	}
	
	magicArray->length--;
}

int magicArrayRemoveItem(MAGIC_ARRAY* magicArray, void* item)
{
	assert(magicArray);
	assert(item);
	
	for (unsigned int i = 0; i < magicArray->length; i++)
	{
		DATA_BLOCK_ITEM* element = magicArray->elements + i;
		if (element->data == item)
		{
			magicArrayRemoveItemByIndex(magicArray, i);
			return 1;
		}
	}
	
	return 0;
}

void* magicArrayGetItem(MAGIC_ARRAY* magicArray, unsigned long itemIndex)
{
	assert(magicArray);
	assert(itemIndex < magicArray->length);
		
	return magicArray->elements[itemIndex].data;
}

unsigned int magicArrayGetItemIndex(MAGIC_ARRAY* array, void* item)
{
	assert(array);
	
	for (unsigned int i = 0; i < array->length; i++)
	{
		if (array->elements[i].data == item)
		{
			return i;
		}
	}
	
	// Item is not found
	assert(0);
	return -1;
}
