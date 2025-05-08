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
	InputComponent->KeyDelegate.Bind(this, &CCamera::ExecuteKeyboard);
	InputComponent->MouseButtonDownDelegate.Bind(this, &CCamera::OnMouseButtonDown);
	InputComponent->MouseButtonUpDelegate.Bind(this, &CCamera::OnMouseButtonUp);
	InputComponent->MouseMoveDelegate.Bind(this, &CCamera::OnMouseMove);
}

void CCamera::Tick(float DeltaTime)
{
}

void CCamera::OnMouseButtonDown(int x, int y)
{
	LastMousePos.x = x;
	LastMousePos.y = y;
}

void CCamera::OnMouseButtonUp(int x, int y)
{
	LastMousePos.x = x;
	LastMousePos.y = y;
}

void CCamera::OnMouseMove(int x, int y)
{	
	LastMousePos.x = x;
	LastMousePos.y = y;
}

void CCamera::ExecuteKeyboard(const FInputKey& InputKey)
{
}
