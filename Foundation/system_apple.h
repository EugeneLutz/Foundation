//
//  system_apple.h
//  Foundation
//
//  Created by Евгений Лютц on 10.03.2020.
//  Copyright © 2020 Eugene Lutz. All rights reserved.
//

#ifndef system_apple_h
#define system_apple_h

#include "private_interface.h"

SYSTEM* systemCreateDefaultApple(void);
void systemInitIOFunctionsApple(SYSTEM* system);
void systemInitThreadingFunctionsApple(SYSTEM* system);
void systemInitTimingFunctionsApple(SYSTEM* system);

void systemReleaseDefaultApple(SYSTEM* system);

#endif /* system_apple_h */
