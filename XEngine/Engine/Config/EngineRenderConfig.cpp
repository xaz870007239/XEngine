#include "EngineRenderConfig.h"

FEngineRenderConfig* FEngineRenderConfig::Instance = nullptr;

FEngineRenderConfig::FEngineRenderConfig() :
	ScreenWidth(1280),
	ScreenHeight(720),
	RefreshRate(60),
	BuffCount(2)
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
