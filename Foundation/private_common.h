//
//  private_common.h
//  Foundation
//
//  Created by Евгений Лютц on 02.01.21.
//  Copyright © 2021 Eugene Lutz. All rights reserved.
//

#ifndef private_common_h
#define private_common_h

#ifdef __cplusplus
extern "C" {
#endif

// MARK: - System headers

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdint.h>
#include <math.h>

// MARK: - Macros

#if defined(DEBUG) && DEBUG
#define debug_memset(data, value, dataSize) memset(data, value, dataSize)
#else
#define debug_memset(data, value, dataSize) /* do nothing */
//#define debug_memset(data, value, dataSize) memset(data, value, dataSize)
#endif

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* private_common_h */
