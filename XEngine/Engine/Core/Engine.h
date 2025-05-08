#pragma once

#include "CoreObject/CoreMinimalObject.h"

#if defined (_WIN32) || defined(_WIN64)

#include "WinMainCommandParameters.h"

#elif

#endif

class CEngine : public CCoreMinimalObject
{
public:
	CEngine();
	virtual ~CEngine();

	virtual int PreInit() = 0;
	virtual int Init(
#if defined (_WIN32) || defined(_WIN64)
		FWinMainCommandParameters Parameters
#elif
#endif
	) = 0;
	virtual int PostInit() = 0;

	virtual void Tick(float DeltaTime) {}

	virtual int PreExit() = 0;
	virtual int Exit() = 0;
	virtual int PostExit() = 0;
};