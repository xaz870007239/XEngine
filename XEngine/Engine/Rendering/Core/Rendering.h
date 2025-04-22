#pragma once

#include "../../EngineMinimal.h"

class FRenderingInterface
{
public:
	friend class FWinEngine;

	FRenderingInterface();
	~FRenderingInterface();

	virtual void Init();
	virtual void Draw(float DeltaTime);

	bool operator==(const FRenderingInterface& Other)
	{
		return guid_equal(&Other.GUID, &GUID);
	}

protected:
	static vector<FRenderingInterface*> RenderingInterfaces;
	simple_c_guid GUID;
};