#include "EngineMinimal.h"
#include "Core/Engine.h"
#include "EngineFactory.h"

int Init(CEngine* InEngine
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

#if defined(_WIN32) || defined(_WIN64)
	FWinMainCommandParameters Parameters{ hInstance, prevInstance, cmdLine, showCmd };
#endif

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

void Tick(CEngine* InEngine)
{
	if (InEngine)
	{
		float Timer = 0.03f;
		InEngine->Tick(Timer);
		Sleep(30);
	}
}

int Exit(CEngine* InEngine)
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

CEngine* Engine = nullptr;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, PSTR cmdLine, int showCmd)
{
	Engine = FEngineFactory::CreateEngine();
	if (!Engine)
	{
		return -1;
	}

#if defined (_WIN32) || defined(_WIN64)
	Init(Engine, hInstance, prevInstance, cmdLine, showCmd);

	MSG EngineMsg{0};
	while (EngineMsg.message != WM_QUIT)
	{
		if (PeekMessage(&EngineMsg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&EngineMsg);
			DispatchMessage(&EngineMsg);
		}
		else
		{
			Tick(Engine);
		}
	}

#elif 
	Init(Engine);
	Tick(Engine);
#endif
	Exit(Engine);
	
	return 0;
}