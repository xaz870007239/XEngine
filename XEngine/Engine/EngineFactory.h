#pragma once

#include "../Engine/Core/Engine.h"
#include "Platform/Windows/WinEngine.h"

class FEngineFactory
{

public:
	static CEngine* CreateEngine();
};
