#include "Mesh.h"

void Mesh::Init()
{
}

void Mesh::BuildMesh(const FMeshRenderData* InRenderingData)
{
}

void Mesh::Draw(float DeltaTime)
{
}

Mesh* Mesh::CreateMesh(const FMeshRenderData* InRenderingData)
{
	Mesh* Result = new Mesh();
	Result->BuildMesh(InRenderingData);
	return Result;
}
