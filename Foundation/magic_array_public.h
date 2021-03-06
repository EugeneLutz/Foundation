//
//  magic_array_public.h
//  Foundation
//
//  Created by Евгений Лютц on 06.11.20.
//  Copyright © 2020 Eugene Lutz. All rights reserved.
//

#ifndef magic_array_public_h
#define magic_array_public_h

#include "foundation.h"

MAGIC_ARRAY* magicArrayCreateWithAllocator(DATA_ALLOCATOR* allocator, unsigned int capacityIncrement);
MAGIC_ARRAY* magicArrayCreate(unsigned int itemSize, unsigned int sizeIncrement);

void magicArrayInitializeWithAllocator(MAGIC_ARRAY* magicArray, DATA_ALLOCATOR* allocator, unsigned int capacityIncrement);
void magicArrayInitialize(MAGIC_ARRAY* magicArray, unsigned int itemSize, unsigned int capacityIncrement);

void magicArrayDeinitialize(MAGIC_ARRAY* magicArray);
void magicArrayRelease(MAGIC_ARRAY* magicArray);

void magicArrayClear(MAGIC_ARRAY* magicArray);

unsigned int magicArrayGetLength(MAGIC_ARRAY* magicArray);
void* magicArrayAddItem(MAGIC_ARRAY* magicArray);
void* magicArrayInsertItem(MAGIC_ARRAY* magicArray, unsigned int itemIndex);
void magicArrayRemoveItemByIndex(MAGIC_ARRAY* magicArray, unsigned long itemIndex);
int magicArrayRemoveItem(MAGIC_ARRAY* magicArray, void* item);
void* magicArrayGetItem(MAGIC_ARRAY* magicArray, unsigned long itemIndex);
unsigned int magicArrayGetItemIndex(MAGIC_ARRAY* array, void* item);

#endif /* magic_array_public_h */
