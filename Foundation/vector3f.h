//
//  vector3f.h
//  Foundation
//
//  Created by Евгений Лютц on 25.12.20.
//  Copyright © 2020 Eugene Lutz. All rights reserved.
//

#ifndef vector3f_h
#define vector3f_h

#include "foundation.h"

#if defined(__APPLE__) && __APPLE__

#include <simd/simd.h>
typedef simd_float3 vector3f;

#else

typedef struct vector3f
{
	float x;
	float y;
	float z;
}
vector3f;

#endif

#endif /* vector3f_h */
