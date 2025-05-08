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

	virtual void GameInit() override;
	virtual void Tick(float DeltaTime) override;

	virtual void OnMouseButtonDown(int x, int y);
	virtual void OnMouseButtonUp(int x, int y);
	virtual void OnMouseMove(int x, int y);

	FORCEINLINE CTransformComponent* GetTransformComponent() const { return TransformComponent; }
	FORCEINLINE CInputComponent* GetInputComponent() const { return InputComponent; }

	void ExecuteKeyboard(const FInputKey& InputKey);

protected:

	CVARIABLE()
	CTransformComponent* TransformComponent;

	CVARIABLE()
	CInputComponent* InputComponent;

	POINT LastMousePos;
};