//
//  ray_interface.h
//  Foundation
//
//  Created by Евгений Лютц on 02.01.21.
//  Copyright © 2021 Eugene Lutz. All rights reserved.
//

#ifndef ray_interface_h
#define ray_interface_h

#include "foundation.h"

RAY rayFromPoints(vector3f position, vector3f secondPoint);
RAY rayFromFrustum(vector2f viewportSize, vector2f position2d, vector3f eyePosition, vector3f eyeRotation, float fovyRadians, float nearPlane, float farPlane);

#endif /* ray_interface_h */
