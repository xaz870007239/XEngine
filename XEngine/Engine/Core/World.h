#pragma once

#include "CoreObject/CoreMinimalObject.h"
#include "../CodeReflection/CodeReflectionMacroTag.h"

class CTransformComponent;
class CInputComponent;
class CCamera;
struct FInputKey;

class CWorld : public CCoreMinimalObject
{
public:

	CWorld();
	~CWorld();

	FORCEINLINE CCamera* GetCamera() const { return Camera; }

protected:

	CVARIABLE()
	CCamera* Camera;
};