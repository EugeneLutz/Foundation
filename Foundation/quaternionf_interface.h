//
//  quaternionf_interface.h
//  Foundation
//
//  Created by Евгений Лютц on 25.12.20.
//  Copyright © 2020 Eugene Lutz. All rights reserved.
//

#ifndef quaternionf_interface_h
#define quaternionf_interface_h

#include "foundation.h"

#if defined(__APPLE__) && __APPLE__

static inline quaternionf quaternionfCreate(float ix, float iy, float iz, float r) { return simd_quaternion(ix, iy, iz, r); }
static inline quaternionf quaternionfFromVector4f(vector4f vector) { return simd_quaternion(vector); };

static inline quaternionf quaternionfCubicBezier(quaternionf q0, quaternionf q1, quaternionf q2, quaternionf q3, float t) { return simd_bezier(q0, q1, q2, q3, t); }

static inline quaternionf quaternionfMul(quaternionf q1, quaternionf q2) { return simd_mul(q1, q2); }
static inline vector4f vector4fFromQuaternionf(quaternionf q) { return q.vector; };

#else

quaternionf quaternionfCreate(float ix, float iy, float iz, float r);
quaternionf quaternionfFromVector4f(vector4f vector);
quaternionf quaternionfCubicBezier(quaternionf q0, quaternionf q1, quaternionf q2, quaternionf q3, float t);
quaternionf quaternionfMul(quaternionf q1, quaternionf q2);
vector4f vector4fFromQuaternionf(quaternionf q);

#endif

static inline quaternionf quaternionfNull(void)
{
	return quaternionfCreate(0.0f, 0.0f, 0.0f, 0.0f);
}

quaternionf quaternionfFromEulerVector3f(vector3f euler);

#endif /* quaternionf_interface_h */
