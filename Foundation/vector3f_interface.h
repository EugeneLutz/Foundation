//
//  vector3f_interface.h
//  Foundation
//
//  Created by Евгений Лютц on 25.12.20.
//  Copyright © 2020 Eugene Lutz. All rights reserved.
//

#ifndef vector3f_interface_h
#define vector3f_interface_h

#include "foundation.h"

#if defined(__APPLE__) && __APPLE__

static inline vector3f vector3fCreate(float x, float y, float z) { return simd_make_float3(x, y, z); }
static inline float vector3fLen(vector3f x) { return simd_length(x); }
static inline vector3f vector3fSumFloat(vector3f x, float y) { return x + y; }
static inline vector3f vector3fSubFloat(vector3f x, float y) { return x - y; }
static inline vector3f vector3fMulFloat(vector3f x, float y) { return x * y; }
static inline vector3f vector3fDivFloat(vector3f x, float y) { return x / y; }
static inline vector3f vector3fSum(vector3f x, vector3f y) { return x + y; }
static inline vector3f vector3fSub(vector3f x, vector3f y) { return x - y; }
static inline vector3f vector3fMul(vector3f x, vector3f y) { return x * y; }
static inline vector3f vector3fDiv(vector3f x, vector3f y) { return x / y; }
static inline vector3f vector3fNormalize(vector3f x) { return simd_normalize((x)); }
static inline vector3f vector3fCross(vector3f x, vector3f y) { return simd_cross(x, y); }
static inline float vector3fDot(vector3f x, vector3f y) { return simd_dot(x, y); }

#else

vector3f vector3fCreate(float x, float y, float z);
float vector3fLen(vector3f x);
vector3f vector3fSumFloat(vector3f x, float y);
vector3f vector3fSubFloat(vector3f x, float y);
vector3f vector3fMulFloat(vector3f x, float y);
vector3f vector3fDivFloat(vector3f x, float y);
vector3f vector3fSum(vector3f x, vector3f y);
vector3f vector3fSub(vector3f x, vector3f y);
vector3f vector3fMul(vector3f x, vector3f y);
vector3f vector3fDiv(vector3f x, vector3f y);
vector3f vector3fNormalize(vector3f x);
vector3f vector3fCross(vector3f x, vector3f y);
float vector3fDot(vector3f x, vector3f y);

#endif

static inline vector3f vector3fNull(void)
{
	return vector3fCreate(0.0f, 0.0f, 0.0f);
}

#endif /* vector3f_interface_h */
