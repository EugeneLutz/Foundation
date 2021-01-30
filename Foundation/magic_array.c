//
//  magic_array.c
//  Foundation
//
//  Created by Евгений Лютц on 06.11.20.
//  Copyright © 2020 Eugene Lutz. All rights reserved.
//

#include "private_interface.h"

static void _magicArrayComponent_initialize(MAGIC_ARRAY_COMPONENT* component, unsigned int itemSize, unsigned int capacity)
{
	component->capacity = capacity;
	component->length = 0;
	component->firstFreeElementIndex = 0;
	
	const unsigned int dataSize = itemSize * component->capacity;
	component->data = malloc(dataSize);
	debug_memset(component->data, 0, dataSize);
	
	const unsigned int engagedElementsSize = sizeof(char) * capacity;
	component->engagedElements = malloc(engagedElementsSize);
	memset(component->engagedElements, 0, engagedElementsSize);
}

static void _magicArrayComponent_grow(MAGIC_ARRAY_COMPONENT* component, unsigned int itemSize, unsigned int sizeIncrement)
{
	const unsigned int oldCapacity = component->capacity;
	
	component->capacity += sizeIncrement;
	
	const unsigned int dataSize = itemSize * component->capacity;
	void* data = realloc(component->data, dataSize);
	assert(data);
	component->data = data;
#if DEBUG
	//void* dataPtr = ((char*)data) + (itemSize * oldCapacity);
	//const unsigned int dirtyDataSize = itemSize * capaciryIncrement;
	//memset(dataPtr, 0, dirtyDataSize);
#endif
	
	const unsigned int engagedElementsSize = sizeof(char) * component->capacity;
	char* engagedElements = realloc(component->engagedElements, engagedElementsSize);
	assert(engagedElements);
	component->engagedElements = engagedElements;
	char* engagedElementsDirtyData = (char*)engagedElements + (sizeof(char) * oldCapacity);
	const unsigned int engagedElementsDirtyDataSize = sizeof(char) * sizeIncrement;
	memset(engagedElementsDirtyData, 0, engagedElementsDirtyDataSize);
}

static void _magicArrayComponent_deinitialize(MAGIC_ARRAY_COMPONENT* component)
{
	free(component->engagedElements);
	free(component->data);
}


MAGIC_ARRAY* magicArrayCreateWithAllocator(DATA_ALLOCATOR* allocator)
{
	assert(allocator);
	MAGIC_ARRAY* magicArray = malloc(sizeof(MAGIC_ARRAY));
	magicArrayInitializeWithAllocator(magicArray, allocator);
	return magicArray;
}

MAGIC_ARRAY* magicArrayCreate(MAGIC_ARRAY_ITEM_DISTRIBUTION distribution, unsigned int itemSize, unsigned int sizeIncrement)
{
	MAGIC_ARRAY* magicArray = malloc(sizeof(MAGIC_ARRAY));
	magicArrayInitialize(magicArray, distribution, itemSize, sizeIncrement);
	return magicArray;
}


void magicArrayInitializeWithAllocator(MAGIC_ARRAY* magicArray, DATA_ALLOCATOR* allocator)
{
	assert(magicArray);
	assert(allocator);
	
	magicArray->distribution = MAGIC_ARRAY_ITEM_DISTRIBUTION_DONT_CARE;
	magicArray->allowItemsReorder = 0;	// Is not used
	magicArray->itemSize = 0;			// Is not used
	magicArray->capaciryIncrement = 0;	// Is not used
	magicArray->length = 0;
	memset(&magicArray->data, 0, sizeof(MAGIC_ARRAY_COMPONENT));	// Is not used
	magicArray->allocatorIsReferenced = 1;
	magicArray->allocator = allocator;
	
	// allocate memory for a bit faster element access
	magicArray->elements = malloc(sizeof(DATA_BLOCK_ITEM) * allocator->dataBlockCapacity * allocator->numDataBlocks);
}

void magicArrayInitialize(MAGIC_ARRAY* magicArray, MAGIC_ARRAY_ITEM_DISTRIBUTION distribution, unsigned int itemSize, unsigned int capacityIncrement)
{
	assert(magicArray);
	assert(itemSize > 0);
	assert(capacityIncrement > 0);
	assert(distribution == MAGIC_ARRAY_ITEM_DISTRIBUTION_DONT_CARE ||
		   distribution == MAGIC_ARRAY_ITEM_DISTRIBUTION_STRAIGHT);
	
	magicArray->distribution = distribution;
	magicArray->allowItemsReorder = 0;
	magicArray->itemSize = itemSize;
	magicArray->capaciryIncrement = capacityIncrement;
	magicArray->length = 0;
	magicArray->allocatorIsReferenced = 0;
	magicArray->allocator = NULL;
	
	if (distribution == MAGIC_ARRAY_ITEM_DISTRIBUTION_DONT_CARE)
	{
		magicArray->elements = malloc(sizeof(DATA_BLOCK_ITEM) * capacityIncrement);
		magicArray->allocator = dataAllocatorCreate(itemSize, capacityIncrement);
	}
	else
	{
		_magicArrayComponent_initialize(&magicArray->data, magicArray->itemSize, magicArray->capaciryIncrement);
		
		// allocate memory for a bit faster element access
		magicArray->capacity = capacityIncrement;
		magicArray->elements = malloc(sizeof(DATA_BLOCK_ITEM) * magicArray->capacity);
	}
}

void magicArrayDeinitialize(MAGIC_ARRAY* magicArray)
{
	assert(magicArray);
	
	if (magicArray->distribution == MAGIC_ARRAY_ITEM_DISTRIBUTION_DONT_CARE)
	{
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
	}
	else
	{
		_magicArrayComponent_deinitialize(&magicArray->data);
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
	
	if (magicArray->distribution == MAGIC_ARRAY_ITEM_DISTRIBUTION_DONT_CARE)
	{
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
	}
	else
	{
		magicArray->data.length = 0;
		magicArray->data.firstFreeElementIndex = 0;
		memset(magicArray->data.engagedElements, 0, sizeof(char) * magicArray->data.capacity);
	}
	
	magicArray->length = 0;
}


unsigned int magicArrayGetLength(MAGIC_ARRAY* magicArray)
{
	assert(magicArray);
	return magicArray->length;
}

void* magicArrayAddItem(MAGIC_ARRAY* magicArray)
{
	assert(magicArray);
	
	if (magicArray->distribution == MAGIC_ARRAY_ITEM_DISTRIBUTION_DONT_CARE)
	{
		DATA_ALLOCATOR* allocator = magicArray->allocator;
		const long lastCapacity = allocator->dataBlockCapacity * allocator->numDataBlocks;
		DATA_BLOCK_ITEM item;
		dataAllocatorAddItem(allocator, &item);
		const long currentCapacity = allocator->dataBlockCapacity * allocator->numDataBlocks;
		if (currentCapacity != lastCapacity)
		{
			magicArray->elements = realloc(magicArray->elements, sizeof(DATA_BLOCK_ITEM) * currentCapacity);
			assert(magicArray->elements);
		}
		
		magicArray->elements[magicArray->length] = item;
		magicArray->length++;
		
		return item.data;
	}
	else
	{
		// 1. If all collection is full, then grow it
		if (magicArray->data.firstFreeElementIndex == magicArray->data.capacity)
		{
			_magicArrayComponent_grow(&magicArray->data, magicArray->itemSize, magicArray->capaciryIncrement);
			magicArray->capacity = magicArray->data.capacity;
			
			DATA_BLOCK_ITEM* elements = realloc(magicArray->elements, sizeof(DATA_BLOCK_ITEM) * magicArray->capacity);
			assert(elements);
			magicArray->elements = elements;
			
			for (unsigned long i = 0; i < magicArray->length; i++)
			{
				const unsigned int dataMemoryOffset = magicArray->itemSize * (unsigned int)i;
				void* item = ((char*)(magicArray->data.data)) + dataMemoryOffset;
				magicArray->elements[i].data = item;
			}
		}
		
		// 2. Get first available item
		const unsigned int dataMemoryOffset = magicArray->itemSize * magicArray->data.firstFreeElementIndex;
		void* item = ((char*)(magicArray->data.data)) + dataMemoryOffset;
		
		// 3. Update array status
		magicArray->elements[magicArray->length].dataBlockIndex = 0;	// unused in this case
		magicArray->elements[magicArray->length].itemIndex = magicArray->length;
		magicArray->elements[magicArray->length].data = item;
		magicArray->length++;
		magicArray->data.length++;
		magicArray->data.engagedElements[magicArray->data.firstFreeElementIndex] = 1;
		
		// 4. Find next available item
		while (magicArray->data.firstFreeElementIndex < magicArray->data.capacity &&
			   magicArray->data.engagedElements[magicArray->data.firstFreeElementIndex])
		{
			magicArray->data.firstFreeElementIndex++;
		}
		
		return item;
	}
}

void magicArrayRemoveItemByIndex(MAGIC_ARRAY* magicArray, unsigned int itemIndex)
{
	assert(magicArray);
	assert(itemIndex < magicArray->length);
	
	DATA_BLOCK_ITEM* magicItem = &magicArray->elements[itemIndex];
	
	if (magicArray->distribution == MAGIC_ARRAY_ITEM_DISTRIBUTION_DONT_CARE)
	{
		dataAllocatorRemoveItem(magicArray->allocator, magicItem);
		debug_memset(magicItem->data, 0, magicArray->allocator->itemSize);
	}
	else
	{
		const unsigned int itemIndexInCollection = magicItem->itemIndex;
		magicArray->data.engagedElements[itemIndexInCollection] = 0;
		if (itemIndexInCollection < magicArray->data.firstFreeElementIndex)
		{
			magicArray->data.firstFreeElementIndex = itemIndexInCollection;
		}
		magicArray->data.length--;
		
		debug_memset(magicItem->data, 0, magicArray->itemSize);
	}
	
	// Shift elements
	for (unsigned int i = itemIndex + 1; i < magicArray->length; i++)
	{
		magicArray->elements[i - 1] = magicArray->elements[i];
	}
	
	magicArray->length--;
}

void magicArrayRemoveItem(MAGIC_ARRAY* magicArray, void* item)
{
	assert(magicArray);
	assert(item);
	
	int removed = 0;
	for (unsigned int i = 0; i < magicArray->length; i++)
	{
		DATA_BLOCK_ITEM* element = magicArray->elements + i;
		if (element->data == item)
		{
			magicArrayRemoveItemByIndex(magicArray, i);
			removed = 1;
			break;
		}
	}
	
	assert(removed);
}

void* magicArrayGetItem(MAGIC_ARRAY* magicArray, unsigned long itemIndex)
{
	assert(magicArray);
	assert(itemIndex < magicArray->length);
	
#if DEBUG
	if (magicArray->distribution == MAGIC_ARRAY_ITEM_DISTRIBUTION_STRAIGHT)
	{
		assert(magicArray->data.engagedElements[itemIndex]);
	}
#endif
	
	return magicArray->elements[itemIndex].data;
}

void* magicArrayGetData(MAGIC_ARRAY* magicArray)
{
	assert(magicArray);
	assert(magicArray->allocator == NULL);
	assert(magicArray->distribution == MAGIC_ARRAY_ITEM_DISTRIBUTION_STRAIGHT);
	//assert(magicArray->allowItemsReorder);
	return magicArray->data.data;
}
