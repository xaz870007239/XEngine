#pragma once

#if defined (_WIN32) || defined (_WIN64)

#include "../EngineMinimal.h"

#define ANALYSIS_HRESULT(InValue) \
{ \
	HRESULT Result = InValue; \
	if (FAILED(Result)) \
	{ \
		XLog("Failed: %i", (int)InValue); \
		assert(0); \
	} \
	else if (SUCCEEDED(Result)) \
	{ \
		XLog_Error("Failed: %i", (int)InValue); \
	} \
}

#elif
#endif