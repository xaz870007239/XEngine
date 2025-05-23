#pragma once

#include "../../EngineMinimal.h"

#if defined(_WIN32)
#include "../../Platform/Windows/WinEngine.h"
#else
#endif

class FRenderingInterface : public IGUIDInterface
{
public:
	friend class CWinEngine;

	FRenderingInterface();
	~FRenderingInterface();

	virtual void Init();
	virtual void PreDraw(float DeltaTime);
	virtual void Draw(float DeltaTime);
	virtual void PostDraw(float DeltaTime);

#if defined(_WIN32)
	CWinEngine* GetEngine() const;
#else
	FEngine* GetEngine() const { return Engine; }
#endif
	ComPtr<ID3D12Device> GetDevice() const;
	ComPtr<ID3D12GraphicsCommandList> GetCommandList() const;
	ComPtr<ID3D12CommandAllocator> GetCommandAllocator() const;

	ComPtr<ID3D12Resource> ConstructDefaultBuffer(ComPtr<ID3D12Resource>& OutTmpBuffer, const void* InData, UINT64 InDataSize);

protected:
	static vector<FRenderingInterface*> RenderingInterfaces;
};

class FRenderingResourcesUpdate : public enable_shared_from_this<FRenderingResourcesUpdate>
{
public:

	FRenderingResourcesUpdate();
	~FRenderingResourcesUpdate();

	void Init(ID3D12Device* InDevice, UINT InElementSize, UINT InElementCount);
	void Update(int Index, const void* InData);
	UINT GetConstantBufferByteSize(UINT InTypeSize);
	UINT GetConstantBufferByteSize();
	ID3D12Resource* GetBuffer() { return UploadBuffer.Get(); }

private:
	
	ComPtr<ID3D12Resource> UploadBuffer;
	UINT ElementSize;
	BYTE* Data;
};