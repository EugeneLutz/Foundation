//
//  vector2f.c
//  Foundation
//
//  Created by Евгений Лютц on 25.12.20.
//  Copyright © 2020 Eugene Lutz. All rights reserved.
//

#include "private_interface.h"

vector2f vector2fNormalizedFromRadians(float radians)
{
	float x = cosf(radians);
	float y = sinf(radians);
	return vector2fCreate(x, y);
}
