//
//  magic_array.h
//  Foundation
//
//  Created by Евгений Лютц on 06.11.20.
//  Copyright © 2020 Eugene Lutz. All rights reserved.
//

#ifndef magic_array_h
#define magic_array_h

#include "foundation.h"

/*!
 @abstract
 Structure that representing array of user defined data type.
 @discussion
 Made with love to make it easy to work with arrays.
 
 You can create an array this way:
 @code
 typedef struct PERSON
 {
	STRING name;
	int age;
 }
 PERSON;
 
 MAGIC_ARRAY persons;
 magicArrayInitialize(&personns, sizeof(PERSON), 8);
 
 // ...
 @endcode
 
 An array can be disposed this way:
 @code
 // ...
 
 magicArrayDeinitialize(&persons);
 @endcode
 
 Another way to initialize an array is to use data allocator (DATA_ALLOCATOR).
 
 @warning
 Don't access elements of this structure unless you clearly know what you're doing. Instead use dedicated functions to work with this data type. It's more convenient and safe to use these functions.
 */
typedef struct MAGIC_ARRAY
{
	// TODO: good stuff
	// char* typeIdentifier;
	
	unsigned int capaciryIncrement;
	unsigned int capacity;
	
	/*!
	 Number of added elements in the array.
	 */
	unsigned int length;
	
	/*!
	 Representation of collection elements. Used to make a sequence of added elements.
	 */
	DATA_BLOCK_ITEM* elements;
	
	int allocatorIsReferenced;
	DATA_ALLOCATOR* allocator;
}
MAGIC_ARRAY;

#endif /* magic_array_h */
