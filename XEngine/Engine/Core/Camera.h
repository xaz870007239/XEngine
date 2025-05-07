#pragma once

#include "Viewport.h"
#include "CoreObject/CoreMinimalObject.h"
#include "../CodeReflection/CodeReflectionMacroTag.h"

class CTransformComponent;
class CInputComponent;

class CCamera : public CCoreMinimalObject, public FViewport
{
public:
	CCamera();
	~CCamera();

	CVARIABLE()
	CTransformComponent* TransformComponent;

	CVARIABLE()
	CInputComponent* InputComponent;
};