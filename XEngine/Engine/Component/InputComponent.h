#pragma once

#include "Core/Component.h"
#include "../Input/InputType.h"

DEFINITION_SIMPLE_SINGLE_DELEGATE(FKeyBindDelegate, void, const FInputKey&);
DEFINITION_SIMPLE_SINGLE_DELEGATE(FMouseBindDelegate, void, int, int);

class CInputComponent : public CComponent
{
public:
	CInputComponent();
	~CInputComponent();

	virtual void GameInit() override;
	virtual void Tick(float DeltaTime) override;

	virtual void OnMouseButtonDown(int x, int y);
	virtual void OnMouseButtonUp(int x, int y);
	virtual void OnMouseMove(int x, int y);

	CVARIABLE()
	FKeyBindDelegate KeyDelegate;

	CVARIABLE()
	FMouseBindDelegate MouseButtonDownDelegate;

	CVARIABLE()
	FMouseBindDelegate MouseButtonUpDelegate;

	CVARIABLE()
	FMouseBindDelegate MouseMoveDelegate;
};