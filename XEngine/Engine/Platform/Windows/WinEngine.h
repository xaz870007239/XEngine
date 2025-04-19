#pragma once

#include "../../Core/Engine.h"
#include "../../../Engine/EngineMinimal.h"

class FWinEngine : public FEngine
{
public:
	// Inherited via FEngine
	int PreInit(FWinMainCommandParameters Parameters) override;
	int Init() override;
	int PostInit() override;
	void Tick() override;
	int PreExit() override;
	int Exit() override;
	int PostExit() override;

	int InitWindows(FWinMainCommandParameters Parameters);
	int InitDirectX3D();

private:
	//ComPtr<>

	HWND WindowHandle;
};