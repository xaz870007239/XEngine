#pragma once

#define ANALYSIS_HRESULT(InValue)\
{\
	HRESULT HandleResult = InValue;\
	if (FAILED(HandleResult))\
	{\
		/*XLog_Error("Error = %i",(int)HandleResult);*/\
		assert(0);\
	}\
	else if (SUCCEEDED(HandleResult))\
	{\
		/*XLog_Success("Success");*/\
	}\
}
