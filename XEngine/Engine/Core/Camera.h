#pragma once

#include "Viewport.h"
#include "CoreObject/CoreMinimalObject.h"
#include "../CodeReflection/CodeReflectionMacroTag.h"

class CTransformComponent;
class CInputComponent;
struct FInputKey;

class CCamera : public CCoreMinimalObject, public FViewport
{
public:
	CCamera();
	~CCamera();

	virtual void Init() override;
	virtual void Tick(float DeltaTime) override;

	FORCEINLINE CTransformComponent* GetTransformComponent() const { return TransformComponent; }
	FORCEINLINE CInputComponent* GetInputComponent() const { return InputComponent; }

	void ExecuteKeyboard(const FInputKey& InputKey);

protected:

	CVARIABLE()
	CTransformComponent* TransformComponent;

	CVARIABLE()
	CInputComponent* InputComponent;
};