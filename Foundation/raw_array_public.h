//
//  raw_array_public.h
//  Foundation
//
//  Created by Евгений Лютц on 16.05.21.
//  Copyright © 2021 Eugene Lutz. All rights reserved.
//

#ifndef raw_array_public_h
#define raw_array_public_h

#include "foundation.h"

void rawArrayInitialize(RAW_ARRAY* array, unsigned long itemSize, unsigned long capacityIncrement);
void rawArrayDeinitialize(RAW_ARRAY* array);

RAW_ARRAY* rawArrayCreate(unsigned long itemSize, unsigned long capacityIncrement);
void rawArrayRelease(RAW_ARRAY* array);

void* rawArrayAddItem(RAW_ARRAY* array);
void* rawArrayGetItem(RAW_ARRAY* array, unsigned long itemIndex);
void* rawArrayGetData(RAW_ARRAY* array);
void rawArrayRemoveItemByIndex(RAW_ARRAY* array, unsigned long itemIndex);
void rawArrayRemoveItem(RAW_ARRAY* array, void* item);
void rawArrayClear(RAW_ARRAY* array);

#endif /* raw_array_public_h */
