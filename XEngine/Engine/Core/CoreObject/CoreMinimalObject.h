#pragma once

#include "../../Platform/Windows/WindowsPlatform.h"

class CCoreMinimalObject
{
public:
	CCoreMinimalObject();
	~CCoreMinimalObject();

	virtual void Init() {}
	virtual void Tick(float DeltaTime) {}

	template<class T>
	static T* CreateObject(CCoreMinimalObject* NewObject)
	{
		return dynamic_cast<T*>(NewObject);
	}
};