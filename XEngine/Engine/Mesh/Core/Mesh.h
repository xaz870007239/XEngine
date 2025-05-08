#pragma once

#include "../../Rendering/Core/Rendering.h"
#include "MeshType.h"
#include "../../Shader/Core/Shader.h"
#include "../../Core/CoreObject/CoreMinimalObject.h"

struct FTransformation
{
	FTransformation() :
		WorldMatrix(FTransformation::IdentityMatrix4x4())
	{}

	XMFLOAT4X4 WorldMatrix;

	static XMFLOAT4X4 IdentityMatrix4x4();
};

class CMesh : public CCoreMinimalObject , public FRenderingInterface
{
public:
	
	CMesh();
	~CMesh();

	virtual void GameInit() override;
	virtual void BuildMesh(const FMeshRenderData* InRenderingData);
	virtual void PreDraw(float DeltaTime) override;
	virtual void Draw(float DeltaTime) override;
	virtual void PostDraw(float DeltaTime) override;

	static CMesh* CreateMesh(const FMeshRenderData* InRenderingData);

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

	ComPtr<ID3D12PipelineState> PSO;

	shared_ptr<FRenderingResourcesUpdate> ObjConstants;

	FShader VShader;
	FShader PShader;

	vector<D3D12_INPUT_ELEMENT_DESC> InputElemDesc;

	int VertexSizeInBytes;
	int IndexSizeInBytes;

	DXGI_FORMAT Format;

	XMFLOAT4X4 WorldMatrix;
	XMFLOAT4X4 ViewMatrix;
	XMFLOAT4X4 ProjectMatrix;
};