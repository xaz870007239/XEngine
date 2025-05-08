#pragma once

#include "../EngineMinimal.h"

enum EInputStatus
{
	Press,
	Release
};

struct FInputKey
{
	FInputKey();

	string KeyName;
	EInputStatus InputStatus;
};