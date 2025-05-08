#include "EngineFactory.h"

CEngine* FEngineFactory::CreateEngine()
{
#if defined(_WIN32) || defined(_WIN64)
	return new CWinEngine{};
#elif

#endif

	return nullptr;
}
