#pragma once

#include "../EngineMinimal.h"

class FWinMainCommandParameters
{
public:
	FWinMainCommandParameters(HINSTANCE hInstance, HINSTANCE prevInstance, PSTR cmdLine, int showCmd) :
		HInstance(hInstance),
		PrevInstance(prevInstance),
		CmdLine(cmdLine),
		ShowCmd(showCmd)
	{
	}

	HINSTANCE HInstance;
	HINSTANCE PrevInstance;
	PSTR CmdLine;
	int ShowCmd;
};

