#include "DirectXDeviceInterface.h"

ComPtr<ID3D12Fence> IDirectXDeviceInterface::GetFence() const
{
	return ComPtr<ID3D12Fence>();
}

ComPtr<ID3D12Device> IDirectXDeviceInterface::GetDevice() const
{
	return ComPtr<ID3D12Device>();
}

ComPtr<ID3D12GraphicsCommandList> IDirectXDeviceInterface::GetCommandList() const
{
	return ComPtr<ID3D12GraphicsCommandList>();
}

ComPtr<ID3D12CommandAllocator> IDirectXDeviceInterface::GetCommandAllocator() const
{
	return ComPtr<ID3D12CommandAllocator>();
}

ComPtr<ID3D12CommandQueue> IDirectXDeviceInterface::GetCommandQueue() const
{
	return ComPtr<ID3D12CommandQueue>();
}

UINT64 IDirectXDeviceInterface::GetCurrentFenceIndex() const
{
	return UINT64();
}

HWND IDirectXDeviceInterface::GetMainWindowsHandle() const
{
	return HWND();
}

ComPtr<ID3D12Fence> IStrDirectXDeviceInterface::GetFence() const
{
	return DirectXDeviceInterface.GetFence();
}

ComPtr<ID3D12Device> IStrDirectXDeviceInterface::GetDevice() const
{
	return DirectXDeviceInterface.GetDevice();
}

ComPtr<ID3D12GraphicsCommandList> IStrDirectXDeviceInterface::GetCommandList() const
{
	return DirectXDeviceInterface.GetCommandList();
}

ComPtr<ID3D12CommandAllocator> IStrDirectXDeviceInterface::GetCommandAllocator() const
{
	return DirectXDeviceInterface.GetCommandAllocator();
}

ComPtr<ID3D12CommandQueue> IStrDirectXDeviceInterface::GetCommandQueue() const
{
	return DirectXDeviceInterface.GetCommandQueue();
}

UINT64 IStrDirectXDeviceInterface::GetCurrentFenceIndex() const
{
	return DirectXDeviceInterface.GetCurrentFenceIndex();
}

HWND IStrDirectXDeviceInterface::GetMainWindowsHandle() const
{
	return DirectXDeviceInterface.GetMainWindowsHandle();
}
