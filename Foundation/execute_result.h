//
//  execute_result.h
//  Foundation
//
//  Created by Евгений Лютц on 24.12.2019.
//  Copyright © 2019 Eugene Lutz. All rights reserved.
//

#ifndef execute_result_h
#define execute_result_h

#include "foundation.h"

typedef struct EXECUTE_RESULT
{
	int succeeded;
	int code;
	char message[2048];
	char comment[2048];
}
EXECUTE_RESULT;

#endif /* execute_result_h */
