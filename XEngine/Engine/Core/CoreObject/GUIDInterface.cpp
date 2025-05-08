#include "GUIDInterface.h"

IGUIDInterface::IGUIDInterface()
{
	create_guid(&GUID);
}

IGUIDInterface::~IGUIDInterface()
{
}
