#include "Mesh.h"

Mesh::Mesh() :
	CPUVertexBufferPtr(nullptr),
	CPUIndexBufferPtr(nullptr), 
	GPUVertexBufferPtr(nullptr),
	GPUIndexBufferPtr(nullptr),
	VertexBufferTmpPtr(nullptr),
	IndexBufferTmpPtr(nullptr),
	VertexSizeInBytes(0),
	IndexSizeInBytes(0),
	Format(DXGI_FORMAT_R16_UINT)
{}

Mesh::~Mesh()
{
}

void Mesh::Init()
{
}

void Mesh::BuildMesh(const FMeshRenderData* InRenderingData)
{
	D3D12_DESCRIPTOR_HEAP_DESC CBVHeapDesc{};
	CBVHeapDesc.NumDescriptors = 1;
	CBVHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	CBVHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
	CBVHeapDesc.NodeMask = 0;
	GetDXDevice()->CreateDescriptorHeap(
		&CBVHeapDesc,
		IID_PPV_ARGS(&CBVHeap)
	);

	ObjectConstants = make_shared<FRenderingResourcesUpdate>();
	ObjectConstants->Init(GetDXDevice().Get(),sizeof(FTransformation), 1);
	D3D12_GPU_VIRTUAL_ADDRESS GPUVirtualAddress = ObjectConstants.get()->GetBuffer()->GetGPUVirtualAddress();

	D3D12_CONSTANT_BUFFER_VIEW_DESC CBVDesc{};
	CBVDesc.BufferLocation = GPUVirtualAddress;
	CBVDesc.SizeInBytes = ObjectConstants->GetConstantBufferByteSize();

	GetDXDevice()->CreateConstantBufferView(
		&CBVDesc,
		CBVHeap->GetCPUDescriptorHandleForHeapStart()
	);

	VertexSizeInBytes = InRenderingData->VertexData.size() * sizeof(FVector);
	IndexSizeInBytes = InRenderingData->IndexData.size() * sizeof(uint16_t);

	ANALYSIS_HRESULT(D3DCreateBlob(VertexSizeInBytes, &CPUVertexBufferPtr));
	memcpy(CPUVertexBufferPtr->GetBufferPointer(), InRenderingData->VertexData.data(), VertexSizeInBytes);

	ANALYSIS_HRESULT(D3DCreateBlob(IndexSizeInBytes, &CPUIndexBufferPtr));
	memcpy(CPUIndexBufferPtr->GetBufferPointer(), InRenderingData->IndexData.data(), IndexSizeInBytes);

	GPUVertexBufferPtr = ConstructDefaultBuffer(
		VertexBufferTmpPtr,
		InRenderingData->VertexData.data(),
		VertexSizeInBytes);

	GPUIndexBufferPtr = ConstructDefaultBuffer(
		IndexBufferTmpPtr,
		InRenderingData->IndexData.data(),
		IndexSizeInBytes);
}

void Mesh::Draw(float DeltaTime)
{
	auto VBV = GetVertexBufferView();
	GetCommandList()->IASetVertexBuffers(0, 1, &VBV);
	auto IBV = GetIndexBufferView();
	GetCommandList()->IASetIndexBuffer(&IBV);
	//GetCommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	GetCommandList()->DrawIndexedInstanced(IndexSizeInBytes / sizeof(uint16_t), 1, 0, 0, 0);
}

Mesh* Mesh::CreateMesh(const FMeshRenderData* InRenderingData)
{
	Mesh* Result = new Mesh();
	Result->BuildMesh(InRenderingData);
	return Result;
}

D3D12_VERTEX_BUFFER_VIEW Mesh::GetVertexBufferView() const
{
	D3D12_VERTEX_BUFFER_VIEW VertexBufferView;
	VertexBufferView.BufferLocation = GPUVertexBufferPtr->GetGPUVirtualAddress();
	VertexBufferView.StrideInBytes = sizeof(FVector);
	VertexBufferView.SizeInBytes = sizeof(FVector) * VertexSizeInBytes;
	return VertexBufferView;
}

D3D12_INDEX_BUFFER_VIEW Mesh::GetIndexBufferView() const
{
	D3D12_INDEX_BUFFER_VIEW IndexBufferView;
	IndexBufferView.BufferLocation = GPUIndexBufferPtr->GetGPUVirtualAddress();
	IndexBufferView.Format = DXGI_FORMAT_R16_UINT;
	IndexBufferView.SizeInBytes = sizeof(uint16_t) * IndexSizeInBytes;
	return IndexBufferView;
}
