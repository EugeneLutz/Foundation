//
//  matrix3f.h
//  Foundation
//
//  Created by Евгений Лютц on 25.12.20.
//  Copyright © 2020 Eugene Lutz. All rights reserved.
//

#ifndef matrix3f_h
#define matrix3f_h

#include "foundation.h"

#if defined(__APPLE__) && __APPLE__

#include <simd/simd.h>
typedef matrix_float3x3 matrix3f;

#else

typedef struct matrix3f
{
	vector3f c0;
	vector3f c1;
	vector3f c2;
}
matrix3f;

#endif

#endif /* matrix3f_h */
