#pragma once

#include "Core/Component.h"
#include "../Input/InputType.h"

DEFINITION_SIMPLE_SINGLE_DELEGATE(FKeyInputDelegate, void, const FInputKey&);

class CInputComponent : public CComponent
{
public:
	CInputComponent();
	~CInputComponent();

	virtual void Init() override;
	virtual void Tick(float DeltaTime) override;

	//CVARIABLE()
	FKeyInputDelegate KeyInputDelegate;
};