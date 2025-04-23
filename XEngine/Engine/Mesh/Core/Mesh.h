#pragma once

#include "../../Rendering/Core/Rendering.h"
#include "MeshType.h"

struct FTransformation
{
	FTransformation() :
		WorldMatrix(
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 0, 0,
			0, 0, 0, 1)
	{}

	XMFLOAT4X4 WorldMatrix;
};

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

	ComPtr<ID3D12RootSignature> RootSignature;
	ComPtr<ID3D12DescriptorHeap> CBVHeap;

	shared_ptr<FRenderingResourcesUpdate> ObjectConstants;

	int VertexSizeInBytes;
	int IndexSizeInBytes;

	DXGI_FORMAT Format;
};