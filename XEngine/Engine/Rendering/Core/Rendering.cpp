#include "Rendering.h"
#include "../../EngineDebug/EngineDebug.h"
#include "../../Platform/Windows/WinEngine.h"

vector<FRenderingInterface*> FRenderingInterface::RenderingInterfaces;

FRenderingInterface::FRenderingInterface()
{
	create_guid(&GUID);
	RenderingInterfaces.push_back(this);
}

FRenderingInterface::~FRenderingInterface()
{
	for (vector<FRenderingInterface*>::const_iterator Iter = RenderingInterfaces.begin();
		Iter != RenderingInterfaces.end(); ++Iter)
	{
		if (*Iter == this)
		{
			RenderingInterfaces.erase(Iter);
			break;
		}
	}
}

void FRenderingInterface::Init()
{
}

void FRenderingInterface::Draw(float DeltaTime)
{
	
}

ComPtr<ID3D12Device> FRenderingInterface::GetDXDevice() const
{
	if (FWinEngine* WinEngine = dynamic_cast<FWinEngine*>(Engine))
	{
		return WinEngine->GetDXDevice();
	}

	return nullptr;
}

ComPtr<ID3D12GraphicsCommandList> FRenderingInterface::GetCommandList() const
{
	if (FWinEngine* WinEngine = dynamic_cast<FWinEngine*>(Engine))
	{
		return WinEngine->GetCommandList();
	}

	return nullptr;
}

ComPtr<ID3D12Resource> FRenderingInterface::ConstructDefaultBuffer(ComPtr<ID3D12Resource>& OutTmpBuffer, const void* InData, UINT64 InDataSize)
{
	ComPtr<ID3D12Resource> Buffer;

	CD3DX12_RESOURCE_DESC BufferResourceDESC = CD3DX12_RESOURCE_DESC::Buffer(InDataSize);
	CD3DX12_HEAP_PROPERTIES BufferProperties = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT);
	ANALYSIS_HRESULT(GetDXDevice()->CreateCommittedResource(
		&BufferProperties,
		D3D12_HEAP_FLAG_NONE,
		&BufferResourceDESC,
		D3D12_RESOURCE_STATE_COMMON,
		NULL, 
		IID_PPV_ARGS(Buffer.GetAddressOf()))
	);

	CD3DX12_HEAP_PROPERTIES UpdateBufferProperties = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
	ANALYSIS_HRESULT(GetDXDevice()->CreateCommittedResource(
		&UpdateBufferProperties,
		D3D12_HEAP_FLAG_NONE,
		&BufferResourceDESC,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		NULL, 
		IID_PPV_ARGS(OutTmpBuffer.GetAddressOf()))
	);

	D3D12_SUBRESOURCE_DATA SubResourceData = {};
	SubResourceData.pData = InData;
	SubResourceData.RowPitch = InDataSize;
	SubResourceData.SlicePitch = SubResourceData.RowPitch;

	CD3DX12_RESOURCE_BARRIER CopyDestBarrier = CD3DX12_RESOURCE_BARRIER::Transition(Buffer.Get(),
		D3D12_RESOURCE_STATE_COMMON,
		D3D12_RESOURCE_STATE_COPY_DEST);

	GetCommandList()->ResourceBarrier(1, &CopyDestBarrier);

	UpdateSubresources<1>(
		GetCommandList().Get(),
		Buffer.Get(),
		OutTmpBuffer.Get(),
		0,//0 -> D3D12_REQ_SUBRESOURCES
		0,//0 -> D3D12_REQ_SUBRESOURCES
		1,
		&SubResourceData);

	CD3DX12_RESOURCE_BARRIER ReadDestBarrier = CD3DX12_RESOURCE_BARRIER::Transition(Buffer.Get(),
		D3D12_RESOURCE_STATE_COPY_DEST,
		D3D12_RESOURCE_STATE_GENERIC_READ);

	return Buffer;
}

FRenderingResourcesUpdate::FRenderingResourcesUpdate()
{
}

FRenderingResourcesUpdate::~FRenderingResourcesUpdate()
{
	if (UploadBuffer)
	{
		UploadBuffer->Unmap(0, nullptr);
		UploadBuffer = nullptr;
	}
}

void FRenderingResourcesUpdate::Init(ID3D12Device* InDevice, UINT InElementSize, UINT InElementCount)
{
	assert(InDevice);

	ElementSize = InElementSize;

	CD3DX12_HEAP_PROPERTIES UploadProperties = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
	CD3DX12_RESOURCE_DESC ResourceDesc = CD3DX12_RESOURCE_DESC::Buffer(InElementSize * InElementCount);
	InDevice->CreateCommittedResource(
		&UploadProperties,
		D3D12_HEAP_FLAG_NONE,
		&ResourceDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&UploadBuffer)
	);

	UploadBuffer->Map(0, nullptr, reinterpret_cast<void**>(&Data));
}

void FRenderingResourcesUpdate::Update(int Index, const void* InData)
{
	memcpy(&Data[Index * ElementSize], InData, ElementSize);
}

UINT FRenderingResourcesUpdate::GetConstantBufferByteSize(UINT InTypeSize)
{
	return (InTypeSize + 255) & ~255;
}

UINT FRenderingResourcesUpdate::GetConstantBufferByteSize()
{
	return GetConstantBufferByteSize(ElementSize);
}
