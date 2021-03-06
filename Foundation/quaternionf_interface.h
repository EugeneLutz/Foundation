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

static inline quaternionf quaternionfSlerp(quaternionf q0, quaternionf q1, float t) { return simd_slerp(q0, q1, t); }
static inline quaternionf quaternionfCubicBezier(quaternionf q0, quaternionf q1, quaternionf q2, quaternionf q3, float t) { return simd_bezier(q0, q1, q2, q3, t); }

static inline quaternionf quaternionfMul(quaternionf q1, quaternionf q2) { return simd_mul(q1, q2); }
static inline matrix3f quaternionfMulMatrix3f(quaternionf q, matrix3f mat) { return simd_mul(simd_matrix3x3(q), mat); }
static inline matrix4f quaternionfMulMatrix4f(quaternionf q, matrix4f mat) { return simd_mul(simd_matrix4x4(q), mat); }
static inline quaternionf quaternionfNormalize(quaternionf q) { return simd_normalize(q); }
static inline vector4f vector4fFromQuaternionf(quaternionf q) { return q.vector; };

#else

quaternionf quaternionfCreate(float ix, float iy, float iz, float r);
quaternionf quaternionfFromVector4f(vector4f vector);
quaternionf quaternionfSlerp(quaternionf q0, quaternionf q1, float t);
quaternionf quaternionfCubicBezier(quaternionf q0, quaternionf q1, quaternionf q2, quaternionf q3, float t);
quaternionf quaternionfMul(quaternionf q1, quaternionf q2);
matrix3f quaternionfMulMatrix3f(quaternionf q, matrix3f mat);
matrix4f quaternionfMulMatrix4f(quaternionf q, matrix4f mat);
quaternionf quaternionfNormalize(quaternionf q);
vector4f vector4fFromQuaternionf(quaternionf q);

#endif

static inline quaternionf quaternionfNull(void)
{
	return quaternionfCreate(0.0f, 0.0f, 0.0f, 0.0f);
}

quaternionf quaternionfFromEulerXYZVector3f(vector3f euler_xyz);
quaternionf quaternionfFromEulerZXYVector3f(vector3f euler_zxy);

#endif /* quaternionf_interface_h */
