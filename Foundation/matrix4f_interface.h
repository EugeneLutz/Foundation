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
static inline matrix4f matrix4fIdentity(void) { return matrix_identity_float4x4; }
static inline matrix4f matrix4fMul(matrix4f x, matrix4f y) { return simd_mul(x, y); }
static inline vector4f matrix4fMulVector4f(matrix4f mat, vector4f vec) { return simd_mul(mat, vec); }

#else

matrix4f matrix4fCreateWithColumns(vector4f c0, vector4f c1, vector4f c2, vector4f c3);
static inline matrix4f matrix4fIdentity(void) {
	return matrix4fCreateWithColumns(vector4fCreate(1.0f, 0.0f, 0.0f, 0.0f),
									 vector4fCreate(0.0f, 1.0f, 0.0f, 0.0f),
									 vector4fCreate(0.0f, 0.0f, 1.0f, 0.0f),
									 vector4fCreate(0.0f, 0.0f, 0.0f, 1.0f));
}
matrix4f matrix4fMul(matrix4f x, matrix4f y);
vector4f matrix4fMulVector4f(matrix4f mat, vector4f vec);

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

matrix4f matrix4fRotation(float radians, vector3f axis);
matrix4f matrix4fEulerTransform(float head, float pitch, float roll);
matrix4f matrix4fFromQuaternionf(quaternionf q1);

matrix4f matrix4fFromAxesVectors3f(vector3f x, vector3f y, vector3f z);

#endif /* matrix4f_interface_h */
