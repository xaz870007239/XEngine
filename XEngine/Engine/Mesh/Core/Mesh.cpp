#include "Mesh.h"

void Mesh::Init()
{
}

void Mesh::BuildMesh(const FMeshRenderData* InRenderingData)
{
	UINT VertexSize = InRenderingData->VertexData.size() * sizeof(FVector);
	UINT IndexSize = InRenderingData->IndexData.size() * sizeof(uint16_t);

	ANALYSIS_HRESULT(D3DCreateBlob(VertexSize, &CPUVertexBufferPtr));
	memcpy(CPUVertexBufferPtr->GetBufferPointer(), InRenderingData->VertexData.data(), VertexSize);

	ANALYSIS_HRESULT(D3DCreateBlob(IndexSize, &CPUIndexBufferPtr));
	memcpy(CPUIndexBufferPtr->GetBufferPointer(), InRenderingData->IndexData.data(), IndexSize);

	GPUVertexBufferPtr = ConstructDefaultBuffer(
		VertexBufferTmpPtr,
		InRenderingData->VertexData.data(),
		VertexSize);

	GPUIndexBufferPtr = ConstructDefaultBuffer(
		IndexBufferTmpPtr,
		InRenderingData->IndexData.data(),
		IndexSize);
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
