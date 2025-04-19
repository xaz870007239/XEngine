#include "EngineFactory.h"

FEngine* FEngineFactory::CreateEngine()
{
#if defined(_WIN32) || defined(_WIN64)
	return new FWinEngine{};
#elif

#endif

	return nullptr;
}
