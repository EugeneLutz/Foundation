//
//  vector4f.h
//  Foundation
//
//  Created by Евгений Лютц on 25.12.20.
//  Copyright © 2020 Eugene Lutz. All rights reserved.
//

#ifndef vector4f_h
#define vector4f_h

#include "foundation.h"

#if defined(__APPLE__) && __APPLE__

#include <simd/simd.h>
typedef simd_float4 vector4f;

#else

typedef struct vector4f
{
	float x;
	float y;
	float z;
	float w;
}
vector4f;

#endif

#endif /* vector4f_h */
