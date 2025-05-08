#include "InputComponent.h"
#include "../Input/Input.h"

CInputComponent::CInputComponent()
{
	MoustDownDelegate.AddFunction(this, &CInputComponent::OnMouseButtonDown);
	MoustUpDelegate.AddFunction(this, &CInputComponent::OnMouseButtonUp);
	MoustMoveDelegate.AddFunction(this, &CInputComponent::OnMouseMove);
}

CInputComponent::~CInputComponent()
{
}

void CInputComponent::GameInit()
{
}

void CInputComponent::Tick(float DeltaTime)
{
	if (KeyDelegate.IsBound())
	{
		FInputKey InputKey;
		KeyDelegate.Execute(InputKey);
	}
}

void CInputComponent::OnMouseButtonDown(int x, int y)
{
	if (MouseButtonDownDelegate.IsBound())
	{
		MouseButtonDownDelegate.Execute(x, y);
	}
}

void CInputComponent::OnMouseButtonUp(int x, int y)
{
	if (MouseButtonUpDelegate.IsBound())
	{
		MouseButtonUpDelegate.Execute(x, y);
	}
}

void CInputComponent::OnMouseMove(int x, int y)
{
	if (MouseMoveDelegate.IsBound())
	{
		MouseMoveDelegate.Execute(x, y);
	}
}
