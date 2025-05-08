#include "InputComponent.h"

CInputComponent::CInputComponent()
{
}

CInputComponent::~CInputComponent()
{
}

void CInputComponent::GameInit()
{
}

void CInputComponent::Tick(float DeltaTime)
{
	if (KeyInputDelegate.IsBound())
	{
		FInputKey InputKey;
		KeyInputDelegate.Execute(InputKey);
	}
}
