//
//  system_interface.h
//  Foundation
//
//  Created by Евгений Лютц on 18.01.2020.
//  Copyright © 2020 Eugene Lutz. All rights reserved.
//

#ifndef system_interface_h
#define system_interface_h

#include "foundation.h"

SYSTEM* systemCreateDefaultIfAvailable(void);
void systemRelease(SYSTEM* system);

void systemLog(SYSTEM* system, const char* message);

void systemGetPathForResourceWithName(SYSTEM* system, STRING* outPath, const char* name, const char* type, EXECUTE_RESULT* executeResult);

#endif /* system_interface_h */
