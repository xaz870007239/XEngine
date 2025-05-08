#include "Camera.h"
#include "../Component/TransformComponent.h"
#include "../Component/InputComponent.h"

CCamera::CCamera()
{
	TransformComponent = CreateObject<CTransformComponent>(new CTransformComponent());
	InputComponent = CreateObject<CInputComponent>(new CInputComponent());
}

CCamera::~CCamera()
{
}

void CCamera::GameInit()
{
	InputComponent->KeyInputDelegate.Bind(this, &CCamera::ExecuteKeyboard);
}

void CCamera::Tick(float DeltaTime)
{
}

void CCamera::ExecuteKeyboard(const FInputKey& InputKey)
{
}
