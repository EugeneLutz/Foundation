//
//  matrix4f_interface.h
//  Foundation
//
//  Created by Евгений Лютц on 25.12.20.
//  Copyright © 2020 Eugene Lutz. All rights reserved.
//

#ifndef matrix4f_interface_h
#define matrix4f_interface_h

#include "foundation.h"

#if defined(__APPLE__) && __APPLE__

static inline matrix4f matrix4fCreateWithColumns(vector4f c0, vector4f c1, vector4f c2, vector4f c3) { return simd_matrix(c0, c1, c2, c3); }
static inline matrix4f matrix4fFromQuaternionf(quaternionf quaternion) { return simd_matrix4x4(quaternion); }
static inline matrix4f matrix4fInvert(matrix4f matrix) { return simd_inverse(matrix); }
static inline matrix4f matrix4fIdentity(void) { return matrix_identity_float4x4; }
static inline matrix4f matrix4fMul(matrix4f x, matrix4f y) { return simd_mul(x, y); }
static inline vector4f matrix4fMulVector4f(matrix4f mat, vector4f vec) { return simd_mul(mat, vec); }
static inline matrix4f matrix4fMulQuaternionf(matrix4f mat, quaternionf q) { return simd_mul(mat, simd_matrix4x4(q)); }
static inline vector4f matrix4fGetColumn0(matrix4f mat) { return mat.columns[0]; }
static inline vector4f matrix4fGetColumn1(matrix4f mat) { return mat.columns[1]; }
static inline vector4f matrix4fGetColumn2(matrix4f mat) { return mat.columns[2]; }
static inline vector4f matrix4fGetColumn3(matrix4f mat) { return mat.columns[3]; }

static inline float matrix4f_v00(matrix4f mat) { return mat.columns[0][0]; }
static inline float matrix4f_v01(matrix4f mat) { return mat.columns[1][0]; }
static inline float matrix4f_v02(matrix4f mat) { return mat.columns[2][0]; }
static inline float matrix4f_v03(matrix4f mat) { return mat.columns[3][0]; }

static inline float matrix4f_v10(matrix4f mat) { return mat.columns[0][1]; }
static inline float matrix4f_v11(matrix4f mat) { return mat.columns[1][1]; }
static inline float matrix4f_v12(matrix4f mat) { return mat.columns[2][1]; }
static inline float matrix4f_v13(matrix4f mat) { return mat.columns[3][1]; }

static inline float matrix4f_v20(matrix4f mat) { return mat.columns[0][2]; }
static inline float matrix4f_v21(matrix4f mat) { return mat.columns[1][2]; }
static inline float matrix4f_v22(matrix4f mat) { return mat.columns[2][2]; }
static inline float matrix4f_v23(matrix4f mat) { return mat.columns[3][2]; }

static inline float matrix4f_v30(matrix4f mat) { return mat.columns[0][3]; }
static inline float matrix4f_v31(matrix4f mat) { return mat.columns[1][3]; }
static inline float matrix4f_v32(matrix4f mat) { return mat.columns[2][3]; }
static inline float matrix4f_v33(matrix4f mat) { return mat.columns[3][3]; }

#else

matrix4f matrix4fCreateWithColumns(vector4f c0, vector4f c1, vector4f c2, vector4f c3);
matrix4f matrix4fFromQuaternionf(quaternionf quaternion);
matrix4f matrix4fInvert(matrix4f matrix);
static inline matrix4f matrix4fIdentity(void) {
	return matrix4fCreateWithColumns(vector4fCreate(1.0f, 0.0f, 0.0f, 0.0f),
									 vector4fCreate(0.0f, 1.0f, 0.0f, 0.0f),
									 vector4fCreate(0.0f, 0.0f, 1.0f, 0.0f),
									 vector4fCreate(0.0f, 0.0f, 0.0f, 1.0f));
}
matrix4f matrix4fMul(matrix4f x, matrix4f y);
vector4f matrix4fMulVector4f(matrix4f mat, vector4f vec);
matrix4f matrix4fMulQuaternionf(matrix4f mat, quaternionf q);
vector4f matrix4fGetColumn0(matrix4f mat);
vector4f matrix4fGetColumn1(matrix4f mat);
vector4f matrix4fGetColumn2(matrix4f mat);
vector4f matrix4fGetColumn3(matrix4f mat);

#endif

/**
 @discussion Each component is @b mxy, where @b x is row and @b y is column.
 */
static inline matrix4f matrix4fCreateWithColumnComponents(float m00, float m10, float m20, float m30,
														  float m01, float m11, float m21, float m31,
														  float m02, float m12, float m22, float m32,
														  float m03, float m13, float m23, float m33)
{
	return matrix4fCreateWithColumns(vector4fCreate(m00, m10, m20, m30),
									 vector4fCreate(m01, m11, m21, m31),
									 vector4fCreate(m02, m12, m22, m32),
									 vector4fCreate(m03, m13, m23, m33));
}

/**
 @discussion Each component is @b mxy, where @b x is row and @b y is column.
 */
static inline matrix4f matrix4fCreateWithRowComponents(float m00, float m01, float m02, float m03,
													   float m10, float m11, float m12, float m13,
													   float m20, float m21, float m22, float m23,
													   float m30, float m31, float m32, float m33)
{
	return matrix4fCreateWithColumnComponents(m00, m10, m20, m30,
											  m01, m11, m21, m31,
											  m02, m12, m22, m32,
											  m03, m13, m23, m33);
}

/*!
 @abstract Creates a translation matrix
 */
matrix4f matrix4fTranslation(float tx, float ty, float tz);
matrix4f matrix4fTranslationFromVector3f(vector3f vector);

matrix4f matrix4fPerspectiveLeftHand_MetalNDC(float fovyRadians, float aspect, float nearZ, float farZ);
matrix4f matrix4fPerspectiveRightHand_MetalNDC(float fovyRadians, float aspect, float nearZ, float farZ);

matrix4f matrix4fOrthogonalLeftHand_MetalNDC(float left, float top, float right, float bottom, float near, float far);
matrix4f matrix4fOrthogonalRightHand_MetalNDC(float left, float top, float right, float bottom, float near, float far);

matrix4f matrix4fLookAtLeftHand(vector3f eye, vector3f target, vector3f up);
matrix4f matrix4fLookAtRightHand(vector3f eye, vector3f target, vector3f up);

matrix4f matrix4fRotation(float radians, float x, float y, float z);
matrix4f matrix4fRotationX(float radians);
matrix4f matrix4fRotationY(float radians);
matrix4f matrix4fRotationZ(float radians);
matrix4f matrix4fRotationFromVector3f(float radians, vector3f axis);
matrix4f matrix4fEulerTransform(float head, float pitch, float roll);

matrix4f matrix4fFromAxesVectors3f(vector3f x, vector3f y, vector3f z);

#endif /* matrix4f_interface_h */
