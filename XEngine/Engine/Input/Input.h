#pragma once

#include "../Core/Engine.h"

DEFINITION_MULTICAST_SINGLE_DELEGATE(FMouseInputDelegate, void, int, int);

extern FMouseInputDelegate MoustDownDelegate;
extern FMouseInputDelegate MoustUpDelegate;
extern FMouseInputDelegate MoustMoveDelegate;
