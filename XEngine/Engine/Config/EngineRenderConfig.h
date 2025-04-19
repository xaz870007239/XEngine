#pragma once

struct FEngineRenderConfig
{
public:
	FEngineRenderConfig();

	int ScreenWidth;
	int ScreenHeight;
	int RefreshRate;
	int BuffCount;

	static FEngineRenderConfig* Get();

private:

	static FEngineRenderConfig* Instance;
};