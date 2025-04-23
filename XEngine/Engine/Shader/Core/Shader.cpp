#include "Shader.h"

void FShader::BuildShaders(const wstring& InFileName, const string& InEntryFunName, const string& InShaderVersion)
{
	ComPtr<ID3DBlob> ErrorShaderMsg;
	HRESULT ShaderRes = D3DCompileFromFile(InFileName.c_str(),
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		InEntryFunName.c_str(),
		InShaderVersion.c_str(),
#if _DEBUG
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION,
#else
		0,
#endif
		0,
		&ShaderCode,
		&ErrorShaderMsg
	);

	if (ErrorShaderMsg)
	{
		XLog_Error("%s", (char*)ErrorShaderMsg->GetBufferPointer());
	}

	ANALYSIS_HRESULT(ShaderRes);
}
