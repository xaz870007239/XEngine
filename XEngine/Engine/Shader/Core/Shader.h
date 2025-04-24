#pragma once

#include "../../EngineMinimal.h"

class FShader
{
public:
	LPVOID GetBufferPointer() const { return ShaderCode->GetBufferPointer(); }
	SIZE_T GetBufferSize() const { return ShaderCode->GetBufferSize(); }
	void BuildShaders(const wstring& InFileName, const string& InEntryFunName, const string& InShaderVersion);

private:
	ComPtr<ID3DBlob> ShaderCode;
};