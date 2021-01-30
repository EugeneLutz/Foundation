//
//  routines.h
//  Foundation
//
//  Created by Евгений Лютц on 21.01.2020.
//  Copyright © 2020 Eugene Lutz. All rights reserved.
//

#ifndef foundation_routines_h
#define foundation_routines_h

#define SF_ARRAY_DEF(type, name) unsigned int name##Len;\
unsigned int name##Size;\
type* name;

#define SF_ARRAY_INIT(type, name, capacity) name##Len = 0;\
name##Size = capacity;\
name = malloc(sizeof(type) * capacity);

#define SF_ARRAY_RELEASE(name) free(name);

#define SF_ARRAY_PREPARE_NEXT(type, name, sizeIncrement)\
if (name##Len == name##Size)\
{\
	unsigned int _newSize = name##Size + sizeIncrement;\
	type* newData = realloc(name, sizeof(type) * _newSize);\
	assert(newData != NULL);\
	name = newData;\
	name##Size = _newSize;\
}

#define SF_ARRAY_LAST(name) (name[name##Len - 1])
#define SF_ARRAY_SET_LAST(name, value) ((name[name##Len - 1]) = value)
#define SF_ARRAY_NEXT(name) (name[name##Len])
#define SF_ARRAY_STASH_NEXT(name) (name##Len)++
#define SF_ARRAY_SHORTEN(name) name##Len--
#define SF_ARRAY_RESET(name) name##Len = 0
#define SF_ARRAY_LEN(name) name##Len
#define SF_ARRAY_CAPACITY(name) name##Size

#define SF_ARRAY_SHIFT_LEFT(name, startIndex)\
{\
	unsigned int _endIndex = name##Len - 1;\
	for (unsigned int _itemIndex = startIndex; _itemIndex < _endIndex; _itemIndex++)\
	{\
		name[_itemIndex] = name[_itemIndex + 1];\
	}\
}

#define SF_ARRAY_SHIFT_RIGHT(name, startIndex)\
{\
	unsigned int _endIndex = name##Len;\
	for (unsigned int _levelIndex = startIndex; _levelIndex < _endIndex; _levelIndex++)\
	{\
		name[_levelIndex + 1] = name[_levelIndex];\
	}\
}

#define SF_ARRAY_REMOVE_ITEM(name, itemIndex)\
SF_ARRAY_SHIFT_LEFT(name, itemIndex)\
SF_ARRAY_SHORTEN(name);

#define SF_ARRAY_INSERT_ITEM(type, sizeIncrement, name, item, itemIndex)\
SF_ARRAY_PREPARE_NEXT(type, name, sizeIncrement);\
SF_ARRAY_SHIFT_RIGHT(name, itemIndex);\
name[itemIndex] = item;\
SF_ARRAY_STASH_NEXT(name);

/*
#define SF_ARRAY_APPEND_ITEM(type, sizeIncrement, name, item)\
SF_ARRAY_INSERT_ITEM(type, sizeIncrement, name, item, SF_ARRAY_LEN(name))
*/

/*
 ???
#define SF_ARRAY_ITEM_AT_INDEX(name, itemIndex)\
assert(name);\
assert(itemIndex < name##Len);\
*/

#endif /* foundation_routines_h */
