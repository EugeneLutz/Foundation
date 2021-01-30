//
//  vector2f.h
//  Foundation
//
//  Created by Евгений Лютц on 15.09.20.
//  Copyright © 2020 Eugene Lutz. All rights reserved.
//

#ifndef vector2f_h
#define vector2f_h

#include "foundation.h"

#if defined(__APPLE__) && __APPLE__

#include <simd/simd.h>
typedef simd_float2 vector2f;

#else

typedef struct vector2f
{
	float x;
	float y;
}
vector2f;

#endif

#endif /* vector2f_h */
