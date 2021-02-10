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
static inline matrix3f matrix3fInvert(matrix3f matrix) { return simd_inverse(matrix); }
static inline matrix3f matrix3fIdentity(void) { return matrix_identity_float3x3; }
static inline matrix3f matrix3fMul(matrix3f x, matrix3f y) { return simd_mul(x, y); }
static inline vector3f matrix3fMulVector3f(matrix3f mat, vector3f vec) { return simd_mul(mat, vec); }

#else

matrix3f matrix3fCreateWithColumns(vector4f c0, vector4f c1, vector4f c2);
matrix3f matrix3fInvert(matrix3f matrix);
matrix3f matrix3fIdentity(void);
matrix3f matrix3fMul(matrix3f x, matrix3f y);
vector3f matrix3fMulVector3f(matrix3f mat, vector3f vec);

#endif

matrix3f matrix3fFromMatrix4f(matrix4f matrix);
matrix3f matrix3fTranslation(float tx, float ty);
matrix3f matrix3fRotation(float radians, vector3f axis);
matrix3f matrix3fOrthogonalRightHand(float width, float height);

#endif /* matrix3f_interface_h */
