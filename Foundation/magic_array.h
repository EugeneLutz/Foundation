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

// HeaderDoc Reference by Justin Loew
// http://www.cocoanutsdev.com/resources/headerdoc-reference-by-justin-loew

/*!
 @abstract
 Private structure that is used by @b MAGIC_ARRAY data.
 @discussion
 Normally you don't use this data type. The @b MAGIC_ARRAY object uses this structure on their own way.
 @warning
 It's a private data type. Access this structure elements if you know what's you're doing.
 */
typedef struct MAGIC_ARRAY_COMPONENT
{
	/*!
	 Number of allocated elements in @b data and @b engagedElements arrays.
	 */
	unsigned int capacity;
	
	/*!
	 Number of used elements in this component. Always less than or equal to @b capacity.
	 */
	unsigned int length;
	
	/*!
	 Determines first free (that is not used) element in @b data collection. Designed to reduce search time for first available to use element in @b engagedElements array.
	 */
	unsigned int firstFreeElementIndex;
	
	/*!
	 @abstract
	 Contents of array component. The value type depends of @b MAGIC_ARRAY.distribution mode or inheritance status.
	 
	 @discussion
	 If this structure is an element from @b MAGIC_ARRAY_COMPONENT.data array, then it is an array of user defined data type.
	 If @b MAGIC_ARRAY.distribution is @e MAGIC_ARRAY_ITEM_DISTRIBUTION_DONT_CARE, then it is an array of @e MAGIC_ARRAY_COMPONENT. In this case you can safely cast this value to @e MAGIC_ARRAY_COMPONENT*.
	 If @b MAGIC_ARRAY.distribution is @e MAGIC_ARRAY_ITEM_DISTRIBUTION_STRAIGHT, then it is an array of user defined data type.
	 The number of elements in this array is equal to the @b capacity value of this structure.
	*/
	void* data;
	
	/*!
	 Flags 0 or 1, which determine, which element of the @b data array is free to use or not. The number of elements in this array is equal to the @b capacity value of this structure.
	*/
	char* engagedElements;
}
MAGIC_ARRAY_COMPONENT;


/*!
 @abstract
 Structure that representing array of user defined data type.
 @discussion
 Made with love to make it easy to work with arrays.
 If @b MAGIC_ARRAY.distribution is @e MAGIC_ARRAY_ITEM_DISTRIBUTION_STRAIGHT, than you can use the @b magicArrayGetData function to access data.
 
 You can create an array this way:
 @code
 typedef struct PERSON
 {
	STRING name;
	int age;
 }
 PERSON;
 
 MAGIC_ARRAY persons;
 magicArrayInitialize(&personns, MAGIC_ARRAY_ITEM_DISTRIBUTION_DONT_CARE, sizeof(PERSON), 8);
 
 // ...
 @endcode
 
 An array can be disposed this way:
 @code
 // ...
 
 magicArrayDeinitialize(&persons);
 @endcode
 @warning
 Don't access elements of this structure unless you clearly know what you're doing. Instead use dedicated functions to work with this data type. It's more convenient and safe to use these functions.
 */
typedef struct MAGIC_ARRAY
{
	// TODO: good stuff
	// char* typeIdentifier;
	
	/*!
	 @discussion
	 Determines how will this array store and process its elements.
	 @see
	 See also MAGIC_ARRAY_ITEM_DISTRIBUTION for more information.
	 */
	MAGIC_ARRAY_ITEM_DISTRIBUTION distribution;
	
	/*!
	 If true, then every deleting item will be replaced with last item from array. This variable is not used at the moment.
	 */
	int allowItemsReorder;
	
	/*!
	 Size of user defined data type.
	 */
	unsigned int itemSize;
	
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
	
	/*!
	 Contains data collection of user defined data type. Used in different ways depending of distribution.
	*/
	MAGIC_ARRAY_COMPONENT data;
	
	int allocatorIsReferenced;
	DATA_ALLOCATOR* allocator;
}
MAGIC_ARRAY;

#endif /* magic_array_h */
