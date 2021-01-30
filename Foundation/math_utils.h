//
//  math_utils.h
//  Foundation
//
//  Created by Евгений Лютц on 24.12.2019.
//  Copyright © 2019 Eugene Lutz. All rights reserved.
//

#ifndef math_utils_h
#define math_utils_h

#define _valInThreshold(vecX, vecY, component, threshold) ( ((vecX).component - (vecY).component) >= -threshold && ((vecX).component - (vecY).component) <= threshold )

#define vector3fNearlyEqual(vecX, vecY, threshold) ( _valInThreshold(vecX, vecY, x, threshold) && _valInThreshold(vecX, vecY, y, threshold) && _valInThreshold(vecX, vecY, z, threshold) )

#define vector2fIsInBox(vector, boxLocation, boxSize) \
	((vector).x >= (boxLocation).x && (vector).x <= ((boxLocation).x + (boxSize).x) && \
	(vector).y >= (boxLocation).y && (vector).y <= ((boxLocation).y + (boxSize).y))


#if __APPLE__

#include <simd/simd.h>

#define sf_clamp(value, min, max) simd_clamp((value), (min), (max))
static inline float floatClamp(float value, float min, float max) { return simd_clamp(value, min, max); }

#else

#define sf_clamp(value, min, max) ( (value) < (min) ? (min) : ( (value) > (max) ? (max) : (value) ) )
static inline float floatClamp(float value, float min, float max) { return value<min ? min:(value>max ? max:value); }

#endif


#endif /* math_utils_h */
