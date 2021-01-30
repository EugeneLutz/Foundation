//
//  segment_interface.h
//  Foundation
//
//  Created by Евгений Лютц on 29.01.2020.
//  Copyright © 2020 Eugene Lutz. All rights reserved.
//

#ifndef segment_interface_h
#define segment_interface_h

#include "foundation.h"

static inline SEGMENT segmentFromPoints(vector3f start, vector3f end)
{
	SEGMENT segment;
	segment.start = start;
	segment.end = end;
	return segment;
}

SEGMENT segmentFromPerspectiveFrustumRightHand(vector2f viewportSize, vector2f position2d, vector3f eyePosition, vector3f eyeRotation, float fovyRadians, float nearPlane, float farPlane);
SEGMENT segmentFromOrthogonalProjectionRightHand(vector2f viewportSize, vector2f position2d, vector3f eyePosition, vector3f eyeRotation, float fovyRadians, float eyeDistance, float nearPlane, float farPlane);

#endif /* segment_interface_h */
