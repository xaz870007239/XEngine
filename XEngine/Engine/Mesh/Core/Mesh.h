#pragma once

#include "../../Rendering/Core/Rendering.h"
#include "MeshType.h"

class Mesh : public FRenderingInterface
{
public:
	
	Mesh();
	~Mesh();

	virtual void Init() override;
	virtual void BuildMesh(const FMeshRenderData* InRenderingData);
	virtual void Draw(float DeltaTime) override;

	static Mesh* CreateMesh(const FMeshRenderData* InRenderingData);

	D3D12_VERTEX_BUFFER_VIEW GetVertexBufferView() const;
	D3D12_INDEX_BUFFER_VIEW GetIndexBufferView() const;

protected:

	ComPtr<ID3DBlob> CPUVertexBufferPtr;
	ComPtr<ID3DBlob> CPUIndexBufferPtr;

	ComPtr<ID3D12Resource> GPUVertexBufferPtr;
	ComPtr<ID3D12Resource> GPUIndexBufferPtr;

	ComPtr<ID3D12Resource> VertexBufferTmpPtr;
	ComPtr<ID3D12Resource> IndexBufferTmpPtr;

	int VertexSizeInBytes;
	int IndexSizeInBytes;

	DXGI_FORMAT Format;
};