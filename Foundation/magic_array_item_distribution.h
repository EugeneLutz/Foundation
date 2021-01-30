//
//  magic_array_item_distribution.h
//  Foundation
//
//  Created by Евгений Лютц on 06.11.20.
//  Copyright © 2020 Eugene Lutz. All rights reserved.
//

#ifndef magic_array_item_distribution_h
#define magic_array_item_distribution_h

/*!
 Determines how elements of an array are allocated and distributed in memory.
 */
typedef enum MAGIC_ARRAY_ITEM_DISTRIBUTION
{
	/*!
	 Use this value if you want to store references to elements of array that you create.
	 */
	MAGIC_ARRAY_ITEM_DISTRIBUTION_DONT_CARE = 0,
	
	/*!
	 Use this value if you do not store references to elements of array that you create. This option may gain some advantages for cache.
	 */
	MAGIC_ARRAY_ITEM_DISTRIBUTION_STRAIGHT
}
MAGIC_ARRAY_ITEM_DISTRIBUTION;

#endif /* magic_array_item_distribution_h */
