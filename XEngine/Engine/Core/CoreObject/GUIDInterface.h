#pragma once

#include "../../EngineMinimal.h"

class IGUIDInterface
{
public:
	IGUIDInterface();
	virtual ~IGUIDInterface();

	bool operator==(const IGUIDInterface& InOther)
	{
		return guid_equal(&InOther.GUID, &this->GUID);
	}

	simple_c_guid GetGUID() const { return GUID; }

protected:

	simple_c_guid GUID;
};