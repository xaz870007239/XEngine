#include "CoreMinimalObject.h"

vector<CCoreMinimalObject*> GObjects;

CCoreMinimalObject::CCoreMinimalObject() :
	bCanTick(true)
{
	GObjects.emplace_back(this);
}

CCoreMinimalObject::~CCoreMinimalObject()
{
	for (vector<CCoreMinimalObject*>::const_iterator Iter = GObjects.begin();
		Iter != GObjects.end(); ++Iter)
	{
		if (*Iter == this)
		{
			GObjects.erase(Iter);
			break;
		}
	}
}
