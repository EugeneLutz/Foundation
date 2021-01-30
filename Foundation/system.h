//
//  system.h
//  Foundation
//
//  Created by Евгений Лютц on 18.01.2020.
//  Copyright © 2020 Eugene Lutz. All rights reserved.
//

#ifndef system_h
#define system_h

#include "private_interface.h"

typedef struct SYSTEM
{
	int callbacksCreatedByDefault;
	
	// MARK: - Other
	
	SYSTEM_LOG_FUNC logFunc;
	
	
	// MARK: - IO
	
	SISTEM_IO_GET_FILE_PATH_WITH_NAME_AND_TYPE_FUNC getPathForResourceWithNameAndTypeFunc;
	
	/// Open file delegate function.
	FILE_OPEN_READ_FUNC fileOpenReadFunc;
	
	//FILE_OPEN_WRITE_FUNC fileOpenWriteFunc;
	
	/// Close file delegate function.
	FILE_CLOSE_FUNC fileCloseFunc;
	
	/// Get file size delegate function.
	FILE_GET_SIZE_FUNC fileGetSizeFunc;
	
	/// Set tile handle position delegate function.
	FILE_SET_POSITION_FUNC fileSetPositionFunc;
	
	/// Read data from file delegate function.
	FILE_READ_DATA_FUNC fileReadDataFunc;
	
	
	// MARK: - Threading
	
	SEMAPHORE_CREATE_FUNC semaphoreCreateFunc;
	SEMAPHORE_RELEASE_FUNC semaphoreReleaseFunc;
	SEMAPHORE_ENTER_FUNC semaphoreEnterFunc;
	SEMAPHORE_LEAVE_FUNC semaphoreLeaveFunc;
	THREAD_DISPATCH_FUNC threadDispatchFunc;
	
	
	// MARK: - Timing
	
	TIMING_GET_CURRENT_TIME_FUNC getCurrentTimeFunc;
	
	
	/// Custom information. Convenient thing, use it as you want. It is sent as a parameter in delegate functions of this structure. Can be NULL.
	void* userInfo;
}
SYSTEM;

#endif /* system_h */
