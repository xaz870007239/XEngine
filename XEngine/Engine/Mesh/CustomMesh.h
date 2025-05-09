#pragma once

#include "Core/Mesh.h"

class CCustomMesh : public CMesh
{
	typedef CMesh Super;

public:

	virtual void Init() override;
	virtual void BuildMesh(const FMeshRenderData* InRenderingData) override;
	virtual void Draw(float DeltaTime) override;

	static CCustomMesh* CreateMesh(const string& InPath);
	static bool LoadObjFromBuffer(char* InBuff, uint32_t InBuffSize, FMeshRenderData& RenderData);
};