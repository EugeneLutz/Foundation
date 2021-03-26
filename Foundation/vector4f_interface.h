//
//  vector4f_interface.h
//  Foundation
//
//  Created by Евгений Лютц on 25.12.20.
//  Copyright © 2020 Eugene Lutz. All rights reserved.
//

#ifndef vector4f_interface_h
#define vector4f_interface_h

#include "foundation.h"

#if defined(__APPLE__) && __APPLE__

static inline vector4f vector4fCreate(float x, float y, float z, float w) { return simd_make_float4(x, y, z, w); }
static inline float vector4fLen(vector4f x) { return simd_length(x); }
static inline vector4f vector4fSumFloat(vector4f x, float y) { return x + y; }
static inline vector4f vector4fSubFloat(vector4f x, float y) { return x - y; }
static inline vector4f vector4fMulFloat(vector4f x, float y) { return x * y; }
static inline vector4f vector4fDivFloat(vector4f x, float y) { return x / y; }
static inline vector4f vector4fSum(vector4f x, vector4f y) { return x + y; }
static inline vector4f vector4fSub(vector4f x, vector4f y) { return x - y; }
static inline vector4f vector4fMul(vector4f x, vector4f y) { return x * y; }
static inline vector4f vector4fDiv(vector4f x, vector4f y) { return x / y; }
static inline vector4f vector4fNormalize(vector4f x) { return simd_normalize((x)); }
static inline vector4f vector4fDot(vector4f x, vector4f y) { return simd_dot(x, y); }

static inline vector3f vector4f_xyz(vector4f x) { return x.xyz; }
static inline float vector4f_x(vector4f vector) { return vector.x; }
static inline float vector4f_y(vector4f vector) { return vector.y; }
static inline float vector4f_z(vector4f vector) { return vector.z; }
static inline float vector4f_w(vector4f vector) { return vector.w; }

#else

vector4f vector4fCreate(float x, float y, float z, float w);
float vector4fLen(vector4f x);
vector4f vector4fSumFloat(vector4f x, float y);
vector4f vector4fSubFloat(vector4f x, float y);
vector4f vector4fMulFloat(vector4f x, float y);
vector4f vector4fDivFloat(vector4f x, float y);
vector4f vector4fSum(vector4f x, vector4f y);
vector4f vector4fSub(vector4f x, vector4f y);
vector4f vector4fMul(vector4f x, vector4f y);
vector4f vector4fDiv(vector4f x, vector4f y);
vector4f vector4fNormalize(vector4f x);
vector4f vector4fDot(vector4f x, vector4f y);

vector3f vector4f_xyz(vector4f x);
float vector4f_x(vector4f vector);
float vector4f_y(vector4f vector);
float vector4f_z(vector4f vector);
float vector4f_w(vector4f vector);

#endif

static inline vector4f vector4fNull(void)
{
	return vector4fCreate(0.0f, 0.0f, 0.0f, 0.0f);
}

#endif /* vector4f_interface_h */
