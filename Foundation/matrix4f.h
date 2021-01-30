//
//  matrix4f.h
//  Foundation
//
//  Created by Евгений Лютц on 25.12.20.
//  Copyright © 2020 Eugene Lutz. All rights reserved.
//

#ifndef matrix4f_h
#define matrix4f_h

#include "foundation.h"

#if defined(__APPLE__) && __APPLE__

#include <simd/simd.h>
typedef matrix_float4x4 matrix4f;

#else

typedef struct matrix4f
{
	vector4f c0;
	vector4f c1;
	vector4f c2;
	vector4f c3;
}
matrix4f;

#endif

#endif /* matrix4f_h */
