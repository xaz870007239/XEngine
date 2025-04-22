#pragma once

#include "Core/Mesh.h"

class FBoxMesh : public Mesh 
{
public:

	typedef Mesh Super;

	virtual void Init() override;
	virtual void BuildMesh(const FMeshRenderData* InRenderingData) override;
	virtual void Draw(float DeltaTime) override;

	static FBoxMesh* CreateMesh();
};