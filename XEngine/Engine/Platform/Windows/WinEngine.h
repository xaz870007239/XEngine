#pragma once

#include "../../Core/Engine.h"
#include "../../../Engine/EngineMinimal.h"

class FWinEngine : public FEngine
{
public:

	FWinEngine();
	~FWinEngine();

	// Inherited via FEngine
	int PreInit() override;
	int Init(FWinMainCommandParameters Parameters) override;
	int PostInit() override;
	void Tick(float DeltaTime) override;
	int PreExit() override;
	int Exit() override;
	int PostExit() override;

	int InitWindows(FWinMainCommandParameters Parameters);
	int InitDirectX3D();

	ID3D12Resource* GetCurrentSwapBuffer();
	D3D12_CPU_DESCRIPTOR_HANDLE GetCurrentSwapBufferView();
	D3D12_CPU_DESCRIPTOR_HANDLE GetCurrentDepthStencilView();

	void WaitGPUCommandQueueComplete();

	ComPtr<ID3D12Device> GetDXDevice() const { return Device; }
	ComPtr<ID3D12GraphicsCommandList> GetCommandList() const { return CommandList; }

protected:

	D3D12_VIEWPORT ViewPortInfo;
	D3D12_RECT ViewPortRect;

	ComPtr<IDXGIFactory4> Factory;
	ComPtr<ID3D12Device> Device;
	ComPtr<ID3D12Fence> Fence;

	ComPtr<ID3D12CommandQueue> CommandQueue;
	ComPtr<ID3D12CommandAllocator> CommandAllocator;
	ComPtr<ID3D12GraphicsCommandList> CommandList;

	ComPtr<IDXGISwapChain> SwapChain;

	ComPtr<ID3D12DescriptorHeap> RTVHeap;
	ComPtr<ID3D12DescriptorHeap> DSVHeap;

	vector<ComPtr<ID3D12Resource>> SwapChainBuffer;
	ComPtr<ID3D12Resource> DepthStencilBuffer;

protected:

	UINT64 CurrentFenceIdx;

	int CurrentSwapBufferIdx;

	HWND WindowHandle;
	UINT M4XQualityLevel;
	bool bMSAA4XEnabled;
	UINT RTVDescriptorSize;

	DXGI_FORMAT BackBufferFormat;
	DXGI_FORMAT DepthStencilFormat;

};