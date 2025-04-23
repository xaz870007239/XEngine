#pragma once

#include "../../EngineMinimal.h"

class FShader
{
public:
	void BuildShaders(const wstring& InFileName, const string& InEntryFunName, const string& InShaderVersion);

private:
	ComPtr<ID3DBlob> ShaderCode;
};