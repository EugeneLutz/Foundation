//
//  vector2f_interface.h
//  Foundation
//
//  Created by Евгений Лютц on 25.12.20.
//  Copyright © 2020 Eugene Lutz. All rights reserved.
//

#ifndef vector2f_interface_h
#define vector2f_interface_h

#include "foundation.h"

#if defined(__APPLE__) && __APPLE__

static inline vector2f vector2fCreate(float x, float y) { return simd_make_float2(x, y); }
static inline float vector2fLen(vector2f x) { return simd_length(x); }
static inline vector2f vector2fSumFloat(vector2f x, float y) { return x + y; }
static inline vector2f vector2fSubFloat(vector2f x, float y) { return x - y; }
static inline vector2f vector2fMulFloat(vector2f x, float y) { return x * y; }
static inline vector2f vector2fDivFloat(vector2f x, float y) { return x / y; }
static inline vector2f vector2fSum(vector2f x, vector2f y) { return x + y; }
static inline vector2f vector2fSub(vector2f x, vector2f y) { return x - y; }
static inline vector2f vector2fMul(vector2f x, vector2f y) { return x * y; }
static inline vector2f vector2fDiv(vector2f x, vector2f y) { return x / y; }
static inline vector2f vector2fInvert(vector2f x) { return -x; }
static inline vector2f vector2fNormalize(vector2f x) { return simd_normalize(x); }
static inline vector2f vector2fDot(vector2f x, vector2f y) { return simd_dot(x, y); }

#else

vector2f vector2fCreate(float x, float y);
float vector2fLen(vector2f x);
vector2f vector2fSumFloat(vector2f x, float y);
vector2f vector2fSubFloat(vector2f x, float y);
vector2f vector2fMulFloat(vector2f x, float y);
vector2f vector2fDivFloat(vector2f x, float y);
vector2f vector2fSum(vector2f x, vector2f y);
vector2f vector2fSub(vector2f x, vector2f y);
vector2f vector2fMul(vector2f x, vector2f y);
vector2f vector2fDiv(vector2f x, vector2f y);
vector2f vector2fInvert(vector2f x);
vector2f vector2fNormalize(vector2f x);
vector2f vector2fDot(vector2f x, vector2f y);

#endif

static inline vector2f vector2fNull(void)
{
	return vector2fCreate(0.0f, 0.0f);
}

vector2f vector2fNormalizedFromRadians(float radians);

#endif /* vector2f_interface_h */
