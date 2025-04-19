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
	static void Destroy();

private:

	static FEngineRenderConfig* Instance;
};