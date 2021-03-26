//
//  matrix3f_interface.h
//  Foundation
//
//  Created by Евгений Лютц on 25.12.20.
//  Copyright © 2020 Eugene Lutz. All rights reserved.
//

#ifndef matrix3f_interface_h
#define matrix3f_interface_h

#include "foundation.h"

#if defined(__APPLE__) && __APPLE__

static inline matrix3f matrix3fCreateWithColumns(vector3f c0, vector3f c1, vector3f c2) { return simd_matrix(c0, c1, c2); }
static inline matrix3f matrix3fFromQuaternionf(quaternionf quaternion) { return simd_matrix3x3(quaternion); }
static inline matrix3f matrix3fInvert(matrix3f matrix) { return simd_inverse(matrix); }
static inline matrix3f matrix3fIdentity(void) { return matrix_identity_float3x3; }
static inline matrix3f matrix3fMul(matrix3f x, matrix3f y) { return simd_mul(x, y); }
static inline vector3f matrix3fMulVector3f(matrix3f mat, vector3f vec) { return simd_mul(mat, vec); }
static inline matrix3f matrix3fMulQuaternionf(matrix3f mat, quaternionf q) { return simd_mul(mat, simd_matrix3x3(q)); }

static inline float matrix3f_v00(matrix3f mat) { return mat.columns[0][0]; }
static inline float matrix3f_v01(matrix3f mat) { return mat.columns[1][0]; }
static inline float matrix3f_v02(matrix3f mat) { return mat.columns[2][0]; }

static inline float matrix3f_v10(matrix3f mat) { return mat.columns[0][1]; }
static inline float matrix3f_v11(matrix3f mat) { return mat.columns[1][1]; }
static inline float matrix3f_v12(matrix3f mat) { return mat.columns[2][1]; }

static inline float matrix3f_v20(matrix3f mat) { return mat.columns[0][2]; }
static inline float matrix3f_v21(matrix3f mat) { return mat.columns[1][2]; }
static inline float matrix3f_v22(matrix3f mat) { return mat.columns[2][2]; }

#else

matrix3f matrix3fCreateWithColumns(vector4f c0, vector4f c1, vector4f c2);
matrix3f matrix3fFromQuaternionf(quaternionf quaternion);
matrix3f matrix3fInvert(matrix3f matrix);
matrix3f matrix3fIdentity(void);
matrix3f matrix3fMul(matrix3f x, matrix3f y);
vector3f matrix3fMulVector3f(matrix3f mat, vector3f vec);
matrix3f matrix3fMulQuaternionf(matrix3f mat, quaternionf q);

#endif

/**
 @discussion Each component is @b mxy, where @b x is row and @b y is column.
 */
static inline matrix3f matrix3fCreateWithColumnComponents(float m00, float m10, float m20,
														  float m01, float m11, float m21,
														  float m02, float m12, float m22)
{
	return matrix3fCreateWithColumns(vector3fCreate(m00, m10, m20),
									 vector3fCreate(m01, m11, m21),
									 vector3fCreate(m02, m12, m22));
}

/**
 @discussion Each component is @b mxy, where @b x is row and @b y is column.
 */
static inline matrix3f matrix3fCreateWithRowComponents(float m00, float m01, float m02,
													   float m10, float m11, float m12,
													   float m20, float m21, float m22)
{
	return matrix3fCreateWithColumnComponents(m00, m10, m20,
											  m01, m11, m21,
											  m02, m12, m22);
}

matrix3f matrix3fFromMatrix4f(matrix4f matrix);
matrix3f matrix3fTranslation(float tx, float ty);
matrix3f matrix3fRotation(float radians, vector3f axis);
matrix3f matrix3fFromAxesVectors3f(vector3f x, vector3f y, vector3f z);

matrix3f matrix3fOrthogonalRightHand(float width, float height);

#endif /* matrix3f_interface_h */
