#pragma once

#include "GUIDInterface.h"
#include "../../Platform/Windows/WindowsPlatform.h"
#include "../../CodeReflection/CodeReflectionMacroTag.h"

extern vector<class CCoreMinimalObject*> GObjects;

class CCoreMinimalObject : public IGUIDInterface
{
public:
	CCoreMinimalObject();
	virtual ~CCoreMinimalObject();

	virtual void GameInit() {}
	virtual void Tick(float DeltaTime) {}

	template<class T>
	static T* CreateObject(CCoreMinimalObject* NewObject)
	{
		return dynamic_cast<T*>(NewObject);
	}

	bool CanTick() const { return bCanTick; }

protected:

	bool bCanTick;
};
