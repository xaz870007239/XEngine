#include "EngineMinimal.h"
#include "Core/Engine.h"
#include "EngineFactory.h"

int Init(FEngine* InEngine
#if defined(_WIN32) || defined(_WIN64)
	, HINSTANCE hInstance, HINSTANCE prevInstance, PSTR cmdLine, int showCmd)
#elif
)
#endif
{
	int Result = 0;
	if (!InEngine)
	{
		return -1;
	}

	FWinMainCommandParameters Parameters{ hInstance, prevInstance, cmdLine, showCmd };

	Result = InEngine->PreInit();
	if (!Result)
	{
		return Result;
	}

	Result = InEngine->Init(
#if defined(_WIN32) || defined(_WIN64)
		Parameters
#endif
	);
	if (!Result)
	{
		return Result;
	}

	Result = InEngine->PostInit();
	if (!Result)
	{
		return Result;
	}

	return 0;
}

void Tick(FEngine* InEngine)
{
	if (InEngine)
	{
		InEngine->Tick();
	}
}

int Exit(FEngine* InEngine)
{
	int Result = 0;
	if (!InEngine)
	{
		return -1;
	}

	Result = InEngine->PreExit();
	if (!Result)
	{
		return Result;
	}

	Result = InEngine->Exit();
	if (!Result)
	{
		return Result;
	}

	Result = InEngine->PostExit();
	if (!Result)
	{
		return Result;
	}

	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, PSTR cmdLine, int showCmd)
{
	FEngine* Engine = FEngineFactory::CreateEngine();
	if (!Engine)
	{
		return -1;
	}

#if defined (_WIN32) || defined(_WIN64)
	Init(Engine, hInstance, prevInstance, cmdLine, showCmd);
#elif
	Init(Engine);
#endif

	while (true)
	{
		Tick(Engine);
	}

	Exit(Engine);
	
	return 0;
}