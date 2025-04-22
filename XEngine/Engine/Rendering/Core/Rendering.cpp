#include "Rendering.h"

vector<FRenderingInterface*> FRenderingInterface::RenderingInterfaces;

FRenderingInterface::FRenderingInterface()
{
	create_guid(&GUID);
	RenderingInterfaces.push_back(this);
}

FRenderingInterface::~FRenderingInterface()
{
	for (vector<FRenderingInterface*>::const_iterator Iter = RenderingInterfaces.begin();
		Iter != RenderingInterfaces.end(); ++Iter)
	{
		if (*Iter == this)
		{
			RenderingInterfaces.erase(Iter);
			break;
		}
	}
}

void FRenderingInterface::Draw(float DeltaTime)
{
	
}
