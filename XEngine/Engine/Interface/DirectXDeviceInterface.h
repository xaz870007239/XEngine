#pragma once

#include "../Platform/Windows/WinEngine.h"

class IDirectXDeviceInterface
{
public:

#if defined(_WIN32)
	CWinEngine* GetEngine() const;
#else
	FEngine* GetEngine() const { return Engine; }
#endif

	ComPtr<ID3D12Fence> GetFence() const;
	ComPtr<ID3D12Device> GetDevice() const;

	ComPtr<ID3D12GraphicsCommandList> GetCommandList() const;
	ComPtr<ID3D12CommandAllocator> GetCommandAllocator() const;
	ComPtr<ID3D12CommandQueue> GetCommandQueue() const;

	UINT64 GetCurrentFenceIndex() const;
	HWND GetMainWindowsHandle() const;

};

struct IStrDirectXDeviceInterface
{
public:

#if defined(_WIN32)
	CWinEngine* GetEngine() const;
#else
	FEngine* GetEngine() const { return Engine; }
#endif

	ComPtr<ID3D12Fence> GetFence() const;
	ComPtr<ID3D12Device> GetDevice() const;

	ComPtr<ID3D12GraphicsCommandList> GetCommandList() const;
	ComPtr<ID3D12CommandAllocator> GetCommandAllocator() const;
	ComPtr<ID3D12CommandQueue> GetCommandQueue() const;

	UINT64 GetCurrentFenceIndex() const;
	HWND GetMainWindowsHandle() const;

	IDirectXDeviceInterface DirectXDeviceInterface;
};