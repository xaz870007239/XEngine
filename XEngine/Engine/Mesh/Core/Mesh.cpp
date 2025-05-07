#include "Mesh.h"

CMesh::CMesh() :
	CPUVertexBufferPtr(nullptr),
	CPUIndexBufferPtr(nullptr), 
	GPUVertexBufferPtr(nullptr),
	GPUIndexBufferPtr(nullptr),
	VertexBufferTmpPtr(nullptr),
	IndexBufferTmpPtr(nullptr),
	VertexSizeInBytes(0),
	IndexSizeInBytes(0),
	Format(DXGI_FORMAT_R16_UINT),
	WorldMatrix(FTransformation::IdentityMatrix4x4()),
	ViewMatrix(FTransformation::IdentityMatrix4x4()),
	ProjectMatrix(FTransformation::IdentityMatrix4x4())
{}

CMesh::~CMesh()
{
}

void CMesh::Init()
{
	float AspectRatio = (float)FEngineRenderConfig::Get()->ScreenWidth / (float)FEngineRenderConfig::Get()->ScreenHeight;
	XMMATRIX Project = XMMatrixPerspectiveFovLH(
		0.25f * 3.1415926535f,
		AspectRatio,
		1.0f,
		1000.0f
	);

	XMStoreFloat4x4(&ProjectMatrix, Project);
}

void CMesh::BuildMesh(const FMeshRenderData* InRenderingData)
{
	D3D12_DESCRIPTOR_HEAP_DESC CBVHeapDesc{};
	CBVHeapDesc.NumDescriptors = 1;
	CBVHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	CBVHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
	CBVHeapDesc.NodeMask = 0;
	GetDevice()->CreateDescriptorHeap(
		&CBVHeapDesc,
		IID_PPV_ARGS(&CBVHeap)
	);

	ObjConstants = make_shared<FRenderingResourcesUpdate>();
	ObjConstants->Init(GetDevice().Get(),sizeof(FTransformation), 1);
	D3D12_GPU_VIRTUAL_ADDRESS GPUVirtualAddress = ObjConstants.get()->GetBuffer()->GetGPUVirtualAddress();

	D3D12_CONSTANT_BUFFER_VIEW_DESC CBVDesc{};
	CBVDesc.BufferLocation = GPUVirtualAddress;
	CBVDesc.SizeInBytes = ObjConstants->GetConstantBufferByteSize();

	GetDevice()->CreateConstantBufferView(
		&CBVDesc,
		CBVHeap->GetCPUDescriptorHandleForHeapStart()
	);

	CD3DX12_ROOT_PARAMETER RootParam[1];

	CD3DX12_DESCRIPTOR_RANGE DescriptorRangeCBV;
	DescriptorRangeCBV.Init(D3D12_DESCRIPTOR_RANGE_TYPE_CBV, 1, 0);

	RootParam[0].InitAsDescriptorTable(1, &DescriptorRangeCBV);

	//D3D12_STATIC_SAMPLER_DESC SampleDesc{};
	CD3DX12_ROOT_SIGNATURE_DESC RootSignatureDesc(1, RootParam, 0, nullptr, D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);

	ComPtr<ID3DBlob> SerializeRootSignature;
	ComPtr<ID3DBlob> ErrorBlob;
	D3D12SerializeRootSignature(
		&RootSignatureDesc,
		D3D_ROOT_SIGNATURE_VERSION_1,
		SerializeRootSignature.GetAddressOf(),
		ErrorBlob.GetAddressOf()
	);

	if (ErrorBlob) 
	{

	}

	GetDevice()->CreateRootSignature(
		0,
		SerializeRootSignature->GetBufferPointer(),
		SerializeRootSignature->GetBufferSize(),
		IID_PPV_ARGS(&RootSignature)
	);

	VShader.BuildShaders(L"../XEngine/Shader/Hello.hlsl", "VS_Main", "vs_5_0");
	PShader.BuildShaders(L"../XEngine/Shader/Hello.hlsl", "PS_Main", "ps_5_0");

	InputElemDesc =
	{
		{"POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,0},
		{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
	};

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

	D3D12_GRAPHICS_PIPELINE_STATE_DESC GPSDesc{};
	memset(&GPSDesc, 0, sizeof(D3D12_GRAPHICS_PIPELINE_STATE_DESC));
	GPSDesc.InputLayout.pInputElementDescs = InputElemDesc.data();
	GPSDesc.InputLayout.NumElements = (UINT)InputElemDesc.size();
	GPSDesc.pRootSignature = RootSignature.Get();
	GPSDesc.VS.pShaderBytecode = reinterpret_cast<BYTE*>(VShader.GetBufferPointer());
	GPSDesc.VS.BytecodeLength = VShader.GetBufferSize();
	GPSDesc.PS.pShaderBytecode = reinterpret_cast<BYTE*>(PShader.GetBufferPointer());
	GPSDesc.PS.BytecodeLength = PShader.GetBufferSize();
	GPSDesc.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
	GPSDesc.SampleMask = UINT_MAX;
	GPSDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
	GPSDesc.NumRenderTargets = 1;
	GPSDesc.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
	GPSDesc.DepthStencilState = CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT);
	GPSDesc.SampleDesc.Count = GetEngine()->GetDXGISampleCount();
	GPSDesc.SampleDesc.Quality = GetEngine()->GetDXGISampleQuality();
	GPSDesc.RTVFormats[0] = GetEngine()->GetBackBufferFormat();
	GPSDesc.DSVFormat = GetEngine()->GetDepthStencilFormat();

	ANALYSIS_HRESULT(GetDevice()->CreateGraphicsPipelineState(&GPSDesc, IID_PPV_ARGS(&PSO)));
}

void CMesh::PreDraw(float DeltaTime)
{
	ANALYSIS_HRESULT(GetCommandList()->Reset(GetCommandAllocator().Get(), PSO.Get()));
}

void CMesh::Draw(float DeltaTime)
{
	ID3D12DescriptorHeap* DestriptorHeaps[] = {CBVHeap.Get()};
	GetCommandList()->SetDescriptorHeaps(_countof(DestriptorHeaps), DestriptorHeaps);
	GetCommandList()->SetGraphicsRootSignature(RootSignature.Get());
	GetCommandList()->SetGraphicsRootDescriptorTable(0, CBVHeap->GetGPUDescriptorHandleForHeapStart());

	auto VBV = GetVertexBufferView();
	GetCommandList()->IASetVertexBuffers(0, 1, &VBV);
	auto IBV = GetIndexBufferView();
	GetCommandList()->IASetIndexBuffer(&IBV);
	//GetCommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	GetCommandList()->DrawIndexedInstanced(IndexSizeInBytes / sizeof(uint16_t), 1, 0, 0, 0);
}

void CMesh::PostDraw(float DeltaTime)
{
	XMUINT3 MeshPost = XMUINT3(5.0f, 5.0f, 5.0f);

	XMVECTOR Pos = XMVectorSet(MeshPost.x, MeshPost.y, MeshPost.z, 1.0f);
	XMVECTOR ViewTarget = XMVectorZero();
	XMVECTOR ViewUp = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	XMMATRIX ViewLookAt = XMMatrixLookAtLH(Pos, ViewTarget, ViewUp);
	XMStoreFloat4x4(&ViewMatrix, ViewLookAt);

	XMMATRIX AtrixWorld = XMLoadFloat4x4(&WorldMatrix);
	XMMATRIX AtrixProject = XMLoadFloat4x4(&ProjectMatrix);
	XMMATRIX WVP = AtrixWorld * ViewLookAt * AtrixProject;

	FTransformation ObjTransform;
	XMStoreFloat4x4(&ObjTransform.WorldMatrix, XMMatrixTranspose(WVP));
	ObjConstants->Update(0, &ObjTransform);
}

CMesh* CMesh::CreateMesh(const FMeshRenderData* InRenderingData)
{
	CMesh* Result = new CMesh();
	Result->BuildMesh(InRenderingData);
	return Result;
}

D3D12_VERTEX_BUFFER_VIEW CMesh::GetVertexBufferView() const
{
	D3D12_VERTEX_BUFFER_VIEW VertexBufferView;
	VertexBufferView.BufferLocation = GPUVertexBufferPtr->GetGPUVirtualAddress();
	VertexBufferView.StrideInBytes = sizeof(FVector);
	VertexBufferView.SizeInBytes = sizeof(FVector) * VertexSizeInBytes;
	return VertexBufferView;
}

D3D12_INDEX_BUFFER_VIEW CMesh::GetIndexBufferView() const
{
	D3D12_INDEX_BUFFER_VIEW IndexBufferView;
	IndexBufferView.BufferLocation = GPUIndexBufferPtr->GetGPUVirtualAddress();
	IndexBufferView.Format = DXGI_FORMAT_R16_UINT;
	IndexBufferView.SizeInBytes = sizeof(uint16_t) * IndexSizeInBytes;
	return IndexBufferView;
}

XMFLOAT4X4 FTransformation::IdentityMatrix4x4()
{
	return XMFLOAT4X4(
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 1);
}
