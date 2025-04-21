#pragma once

#include "../../EngineMinimal.h"

#if defined(_WIN32) || defined(_WIN64)

//#define XLog(format,...) log_log(format,__VA_ARGS__)
//#define XLog_Success(format,...) log_success(format,__VA_ARGS__)
//#define XLog_Warning(format,...) log_warning(format,__VA_ARGS__)
//#define XLog_Error(format,...) log_error(format,__VA_ARGS__)

#define XLog(format,...)
#define XLog_Success(format,...)
#define XLog_Warning(format,...)
#define XLog_Error(format,...)

#elif

#endif