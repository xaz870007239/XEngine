#pragma once

struct FEngineRenderConfig
{
public:
	FEngineRenderConfig();

	int ScreenWidth;
	int ScreenHeight;
	int RefreshRate;
	int SwapChainCount;

	static FEngineRenderConfig* Get();
	static void Destroy();

private:

	static FEngineRenderConfig* Instance;
};