//
//  frustum.h
//  Foundation
//
//  Created by Евгений Лютц on 12.02.21.
//  Copyright © 2021 Eugene Lutz. All rights reserved.
//

#ifndef frustum_h
#define frustum_h

#include "foundation.h"

// Frustum culling
// https://gist.github.com/nothings/913056601b56e5719cc987684a16544e
// https://kotaku.com/horizon-zero-dawn-uses-all-sorts-of-clever-tricks-to-lo-1794385026

typedef struct FRUSTUM FRUSTUM;

typedef void (* FRUSTUM_OBJECT_APPEARED_FUNC)(FRUSTUM* frustum, void* objectId, void* userInfo);
typedef void (* FRUSTUM_OBJECT_DISAPPEARED_FUNC)(FRUSTUM* frustum, void* objectId, void* userInfo);

typedef struct FRUSTUM
{
	vector3f eyeLocation;
	
	//MAGIC_ARRAY items;	// incomplete type
}
FRUSTUM;

#endif /* frustum_h */
