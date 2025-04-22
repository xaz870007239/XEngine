#pragma once

#include "../../Rendering/Core/Rendering.h"
#include "MeshType.h"

class Mesh : public FRenderingInterface
{
public:

	virtual void Init() override;
	virtual void BuildMesh(const FMeshRenderData* InRenderingData);
	virtual void Draw(float DeltaTime) override;

	static Mesh* CreateMesh(const FMeshRenderData* InRenderingData);

protected:

	ComPtr<ID3DBlob> CPUVertexBufferPtr;
	ComPtr<ID3DBlob> CPUIndexBufferPtr;

	ComPtr<ID3D12Resource> GPUVertexBufferPtr;
	ComPtr<ID3D12Resource> GPUIndexBufferPtr;

	ComPtr<ID3D12Resource> VertexBufferTmpPtr;
	ComPtr<ID3D12Resource> IndexBufferTmpPtr;
};