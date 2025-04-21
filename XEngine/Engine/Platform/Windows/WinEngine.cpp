#pragma once

#include "../../EngineMinimal.h"
#include "WinEngine.h"
#include "WindowsMessageProcessing.h"

FWinEngine::FWinEngine() :
	CurrentFenceIdx(0),
	CurrentSwapBufferIdx(0),
	M4XQualityLevel(0),
	bMSAA4XEnabled(false),
	BufferFormat(DXGI_FORMAT_R8G8B8A8_UNORM),
	DepthStencilFormat(DXGI_FORMAT_D24_UNORM_S8_UINT)
{
	for (int i = 0; i < FEngineRenderConfig::Get()->BuffCount; ++i)
	{
		SwapChainBuffer.push_back(ComPtr<ID3D12Resource>());
	}
}

int FWinEngine::PreInit()
{
	const char LogPath[] = "../log";
	init_log_system(LogPath);

	return 1;
}

int FWinEngine::Init(FWinMainCommandParameters Parameters)
{
	if (!InitWindows(Parameters))
	{
		return -1;
	}

	if (!InitDirectX3D())
	{
		return -1;
	}

	return 1;
}

int FWinEngine::PostInit()
{
	WaitGPUCommandQueueComplete();

	for (int i = 0; i < FEngineRenderConfig::Get()->BuffCount; ++i)
	{
		SwapChainBuffer[i].Reset();
	}

	DepthStencilBuffer.Reset();

	HRESULT SwapChainRes = SwapChain->ResizeBuffers(
		FEngineRenderConfig::Get()->BuffCount,
		FEngineRenderConfig::Get()->ScreenWidth,
		FEngineRenderConfig::Get()->ScreenHeight,
		BufferFormat,
		DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH
	);

	RTVDescriptorSize = Device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
	CD3DX12_CPU_DESCRIPTOR_HANDLE RTVHandle{ RTVHeap->GetCPUDescriptorHandleForHeapStart() };
	for (int i = 0; i < FEngineRenderConfig::Get()->BuffCount; ++i)
	{
		SwapChain->GetBuffer(i, IID_PPV_ARGS(&SwapChainBuffer[i]));
		Device->CreateRenderTargetView(SwapChainBuffer[i].Get(), nullptr, RTVHandle);
		RTVHandle.Offset(i, RTVDescriptorSize);
	}

	D3D12_RESOURCE_DESC ResourceDesc{};
	ResourceDesc.Width = FEngineRenderConfig::Get()->ScreenWidth;
	ResourceDesc.Height = FEngineRenderConfig::Get()->ScreenHeight;
	ResourceDesc.Alignment = 0;
	ResourceDesc.MipLevels = 1;
	ResourceDesc.DepthOrArraySize = 1;
	ResourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	ResourceDesc.SampleDesc.Count = bMSAA4XEnabled ? 4 : 1;
	ResourceDesc.SampleDesc.Quality = bMSAA4XEnabled ? (M4XQualityLevel - 1) : 0;
	ResourceDesc.Format = DXGI_FORMAT_R24G8_TYPELESS;
	ResourceDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;
	ResourceDesc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;

	D3D12_CLEAR_VALUE ClearValue;
	ClearValue.DepthStencil.Depth = 1.f;
	ClearValue.DepthStencil.Stencil = 0;
	ClearValue.Format = DepthStencilFormat;

	CD3DX12_HEAP_PROPERTIES Properties = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT);

	Device->CreateCommittedResource(
		&Properties,
		D3D12_HEAP_FLAG_NONE,
		&ResourceDesc,
		D3D12_RESOURCE_STATE_COMMON,
		&ClearValue,
		IID_PPV_ARGS(&DepthStencilBuffer)
	);

	D3D12_DEPTH_STENCIL_VIEW_DESC DSVDesc{};
	DSVDesc.Format = DepthStencilFormat;
	DSVDesc.Texture2D.MipSlice = 0;
	DSVDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
	DSVDesc.Flags = D3D12_DSV_FLAG_NONE;

	D3D12_CPU_DESCRIPTOR_HANDLE DSVHandle{ DSVHeap->GetCPUDescriptorHandleForHeapStart() };
	Device->CreateDepthStencilView(
		DepthStencilBuffer.Get(),
		&DSVDesc,
		DSVHandle
	);

	CD3DX12_RESOURCE_BARRIER Barrier = CD3DX12_RESOURCE_BARRIER::Transition(
		DepthStencilBuffer.Get(),
		D3D12_RESOURCE_STATE_COMMON,
		D3D12_RESOURCE_STATE_DEPTH_WRITE
	); 
	CommandList->ResourceBarrier(1, &Barrier);
	CommandList->Close();

	ID3D12CommandList* CommandLists[] = { CommandList.Get() };
	CommandQueue->ExecuteCommandLists(_countof(CommandLists), CommandLists);

	ViewPortInfo.TopLeftX = 0;
	ViewPortInfo.TopLeftY = 0;
	ViewPortInfo.MinDepth = 0;
	ViewPortInfo.MaxDepth = 1;
	ViewPortInfo.Width = FEngineRenderConfig::Get()->ScreenWidth;
	ViewPortInfo.Height = FEngineRenderConfig::Get()->ScreenHeight;

	ViewPortRect.left = 0;
	ViewPortRect.top = 0;
	ViewPortRect.right = FEngineRenderConfig::Get()->ScreenWidth;
	ViewPortRect.bottom = FEngineRenderConfig::Get()->ScreenHeight;

	WaitGPUCommandQueueComplete();

	return 1;
}

void FWinEngine::Tick(float DeltaTime)
{
	CommandAllocator->Reset();
	CommandList->Reset(CommandAllocator.Get(), nullptr);

	 
	CD3DX12_RESOURCE_BARRIER ResourceBarrierPresent = CD3DX12_RESOURCE_BARRIER::Transition(
		GetCurrentSwapBuffer(),
		D3D12_RESOURCE_STATE_RENDER_TARGET,
		D3D12_RESOURCE_STATE_RENDER_TARGET
	);
	CommandList->ResourceBarrier(1, &ResourceBarrierPresent);

	CommandList->RSSetViewports(1, &ViewPortInfo);
	CommandList->RSSetScissorRects(1, &ViewPortRect);

	CommandList->ClearRenderTargetView(
		GetCurrentSwapBufferView(),
		DirectX::Colors::Red,
		0,
		nullptr
	);

	CommandList->ClearDepthStencilView(
		GetCurrentDepthStencilView(),
		D3D12_CLEAR_FLAG_DEPTH | D3D12_CLEAR_FLAG_STENCIL,
		1.0f,
		0.0f,
		0.0f,
		nullptr
	);

	D3D12_CPU_DESCRIPTOR_HANDLE SBV = GetCurrentSwapBufferView();
	D3D12_CPU_DESCRIPTOR_HANDLE DSV = GetCurrentDepthStencilView();
	CommandList->OMSetRenderTargets(
		RTVDescriptorSize,
		&SBV,
		true,
		&DSV
	);

	CD3DX12_RESOURCE_BARRIER ResourceBarrierCurr = CD3DX12_RESOURCE_BARRIER::Transition(
		GetCurrentSwapBuffer(),
		D3D12_RESOURCE_STATE_RENDER_TARGET,
		D3D12_RESOURCE_STATE_RENDER_TARGET
	);
	CommandList->ResourceBarrier(1, &ResourceBarrierCurr);

	CommandList->Close();

	ID3D12CommandList* CommandLists[] = { CommandList.Get() };
	CommandQueue->ExecuteCommandLists(_countof(CommandLists), CommandLists);

	SwapChain->Present(0, 0);
	CurrentSwapBufferIdx = CurrentSwapBufferIdx == 0 ? 1 : 0;

	WaitGPUCommandQueueComplete();
}

int FWinEngine::PreExit()
{
	return 1;
}

int FWinEngine::Exit()
{
	return 1;
}

int FWinEngine::PostExit()
{
	return 1;
}

int FWinEngine::InitWindows(FWinMainCommandParameters Parameters)
{
	WNDCLASSEX WindowsClass;
	WindowsClass.cbSize = sizeof(WNDCLASSEX);
	WindowsClass.cbClsExtra = 0; 
	WindowsClass.cbWndExtra = 0;
	WindowsClass.hbrBackground = nullptr;
	WindowsClass.hCursor = LoadCursor(nullptr, IDC_ARROW); 
	WindowsClass.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	WindowsClass.hIconSm = nullptr; 
	WindowsClass.hInstance = Parameters.HInstance; 
	WindowsClass.lpfnWndProc = EngineWindowProc;
	WindowsClass.lpszClassName = L"XEngine"; 
	WindowsClass.lpszMenuName = nullptr; 
	WindowsClass.style = CS_HREDRAW | CS_VREDRAW; 

	ATOM RegisterAtom = RegisterClassEx(&WindowsClass);
	if (!RegisterAtom)
	{
		return -1;
	}

	RECT Rest{ 0, 0, FEngineRenderConfig::Get()->ScreenWidth, FEngineRenderConfig::Get()->ScreenHeight };
	AdjustWindowRect(&Rest, WS_OVERLAPPEDWINDOW, NULL);

	WindowHandle = CreateWindowEx(
		0,
		L"XEngine",
		L"XEngine",
		WS_OVERLAPPEDWINDOW,
		100, 
		100,
		Rest.right - Rest.left,
		Rest.bottom - Rest.top,
		nullptr,
		nullptr,
		Parameters.HInstance,
		NULL
	);

	ShowWindow(WindowHandle, SW_SHOW);
	UpdateWindow(WindowHandle);

	return 1;
}

int FWinEngine::InitDirectX3D()
{
	ComPtr<ID3D12Debug> D3D12Debug;
	if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&D3D12Debug))))
	{
		D3D12Debug->EnableDebugLayer();
	}

	CreateDXGIFactory1(IID_PPV_ARGS(&Factory));

	HRESULT D3dDeviceResult = D3D12CreateDevice(
		nullptr,
		D3D_FEATURE_LEVEL_11_0,
		IID_PPV_ARGS(&Device)
	);

	if (FAILED(D3dDeviceResult))
	{
		ComPtr<IDXGIAdapter> WARPAdapter;
		Factory->EnumWarpAdapter(IID_PPV_ARGS(&WARPAdapter));
		D3D12CreateDevice(WARPAdapter.Get(),
			D3D_FEATURE_LEVEL_11_0,
			IID_PPV_ARGS(&Device)
		);
	}

	Device->CreateFence(
		0,
		D3D12_FENCE_FLAG_NONE,
		IID_PPV_ARGS(&Fence)
	);

	D3D12_COMMAND_QUEUE_DESC QueueDesc = {};
	QueueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
	QueueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
	Device->CreateCommandQueue(
		&QueueDesc, 
		IID_PPV_ARGS(&CommandQueue)
	);

	Device->CreateCommandAllocator(
		D3D12_COMMAND_LIST_TYPE_DIRECT,
		IID_PPV_ARGS(CommandAllocator.GetAddressOf()) //GetAddressOf?
	);

	Device->CreateCommandList(
		0,
		D3D12_COMMAND_LIST_TYPE_DIRECT,
		CommandAllocator.Get(),
		nullptr,
		IID_PPV_ARGS(CommandList.GetAddressOf()) //GetAddressOf?
	);

	CommandList->Close();

	D3D12_FEATURE_DATA_MULTISAMPLE_QUALITY_LEVELS QualityLevels{};
	QualityLevels.SampleCount = 4;
	QualityLevels.Flags = D3D12_MULTISAMPLE_QUALITY_LEVELS_FLAG_NONE;
	QualityLevels.NumQualityLevels = 0;
	Device->CheckFeatureSupport(
		D3D12_FEATURE_MULTISAMPLE_QUALITY_LEVELS,
		&QualityLevels,
		sizeof(QualityLevels)
	);

	M4XQualityLevel = QualityLevels.NumQualityLevels;

	SwapChain.Reset();
	DXGI_SWAP_CHAIN_DESC SwapChainDesc = {};
	SwapChainDesc.BufferDesc.Width = FEngineRenderConfig::Get()->ScreenWidth;
	SwapChainDesc.BufferDesc.Height = FEngineRenderConfig::Get()->ScreenHeight;
	SwapChainDesc.BufferDesc.RefreshRate.Numerator = FEngineRenderConfig::Get()->RefreshRate;
	SwapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	SwapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	SwapChainDesc.BufferDesc.Format = BufferFormat;
	SwapChainDesc.BufferCount = FEngineRenderConfig::Get()->BuffCount;
	SwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	SwapChainDesc.OutputWindow = WindowHandle;
	SwapChainDesc.Windowed = true;
	SwapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	SwapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	SwapChainDesc.SampleDesc.Count = bMSAA4XEnabled ? 4 : 1;
	SwapChainDesc.SampleDesc.Quality = bMSAA4XEnabled ? (M4XQualityLevel - 1) : 0;
	Factory->CreateSwapChain(
		CommandQueue.Get(),
		&SwapChainDesc,
		SwapChain.GetAddressOf()
	);

	D3D12_DESCRIPTOR_HEAP_DESC RTVHeapDesc{};
	RTVHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
	RTVHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
	RTVHeapDesc.NodeMask = 0;
	RTVHeapDesc.NumDescriptors = 2;
	Device->CreateDescriptorHeap(
		&RTVHeapDesc,
		IID_PPV_ARGS(RTVHeap.GetAddressOf())
	);

	D3D12_DESCRIPTOR_HEAP_DESC DSVHeapDesc{};
	DSVHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
	DSVHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
	DSVHeapDesc.NodeMask = 0;
	DSVHeapDesc.NumDescriptors = 1;
	Device->CreateDescriptorHeap(
		&DSVHeapDesc,
		IID_PPV_ARGS(DSVHeap.GetAddressOf())
	);

	return 1;
}

ID3D12Resource* FWinEngine::GetCurrentSwapBuffer()
{
	return SwapChainBuffer[CurrentSwapBufferIdx].Get();
}

D3D12_CPU_DESCRIPTOR_HANDLE FWinEngine::GetCurrentSwapBufferView()
{
	return CD3DX12_CPU_DESCRIPTOR_HANDLE{
		RTVHeap->GetCPUDescriptorHandleForHeapStart(),
		CurrentSwapBufferIdx,
		RTVDescriptorSize
	};
}

D3D12_CPU_DESCRIPTOR_HANDLE FWinEngine::GetCurrentDepthStencilView()
{
	return CD3DX12_CPU_DESCRIPTOR_HANDLE{DSVHeap->GetCPUDescriptorHandleForHeapStart()};
}

void FWinEngine::WaitGPUCommandQueueComplete()
{
	CurrentFenceIdx++;
	CommandQueue->Signal(Fence.Get(), CurrentFenceIdx);
	if (Fence->GetCompletedValue() < CurrentFenceIdx)
	{
		HANDLE EventHandle = CreateEventEx(nullptr, nullptr, 0, EVENT_ALL_ACCESS);
		Fence->SetEventOnCompletion(CurrentFenceIdx, EventHandle);

		WaitForSingleObject(EventHandle, INFINITE);

		CloseHandle(EventHandle);
	}
}
