#pragma once

#include "Core/Mesh.h"

class CBoxMesh : public CMesh 
{
public:

	typedef CMesh Super;

	virtual void GameInit() override;
	virtual void BuildMesh(const FMeshRenderData* InRenderingData) override;
	virtual void Draw(float DeltaTime) override;

	static CBoxMesh* CreateMesh();
};