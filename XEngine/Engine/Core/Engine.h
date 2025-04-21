#pragma once

#if defined (_WIN32) || defined(_WIN64)

#include "WinMainCommandParameters.h"

#elif

#endif

class FEngine
{
public:
	virtual int PreInit() = 0;
	virtual int Init(
#if defined (_WIN32) || defined(_WIN64)
		FWinMainCommandParameters Parameters
#elif
#endif
	) = 0;
	virtual int PostInit() = 0;

	virtual void Tick(float DeltaTime) = 0;

	virtual int PreExit() = 0;
	virtual int Exit() = 0;
	virtual int PostExit() = 0;
};