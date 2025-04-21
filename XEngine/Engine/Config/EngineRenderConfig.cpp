#include "EngineRenderConfig.h"

FEngineRenderConfig* FEngineRenderConfig::Instance = nullptr;

FEngineRenderConfig::FEngineRenderConfig() :
	ScreenWidth(1280),
	ScreenHeight(720),
	RefreshRate(60),
	SwapChainCount(2)
{
}

FEngineRenderConfig* FEngineRenderConfig::Get()
{
	if (!Instance)
	{
		Instance = new FEngineRenderConfig{};
		return Instance;
	}

	return Instance;
}

void FEngineRenderConfig::Destroy()
{
	if (Instance)
	{
		delete Instance;
		Instance = nullptr;
	}
}
