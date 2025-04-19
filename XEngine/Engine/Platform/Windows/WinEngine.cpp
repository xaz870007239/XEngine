#pragma once

#include "../../EngineMinimal.h"
#include "WinEngine.h"
#include "WindowsMessageProcessing.h"

int FWinEngine::PreInit(FWinMainCommandParameters Parameters)
{
	const char LogPath[] = "../log";
	init_log_system(LogPath);

	if (!InitWindows(Parameters))
	{
		return -1;
	}

	if (!InitDirectX3D())
	{
		return -1;
	}

	return 0;
}

int FWinEngine::Init()
{
	return 0;
}

int FWinEngine::PostInit()
{
	return 0;
}

void FWinEngine::Tick()
{
}

int FWinEngine::PreExit()
{
	return 0;
}

int FWinEngine::Exit()
{
	return 0;
}

int FWinEngine::PostExit()
{
	return 0;
}

int FWinEngine::InitWindows(FWinMainCommandParameters Parameters)
{
	WNDCLASSEX WindowsClass;
	WindowsClass.cbSize = sizeof(WNDCLASSEX); //对象占据多大内存
	WindowsClass.cbClsExtra = 0; //是否需要额外空间
	WindowsClass.cbWndExtra = 0; //是否需要额外内存
	WindowsClass.hbrBackground = nullptr; //如果有设置那就是GDI擦除
	WindowsClass.hCursor = LoadCursor(nullptr, IDC_ARROW); //设置箭头光标
	WindowsClass.hIcon = LoadIcon(nullptr, IDI_APPLICATION); //exe图标
	WindowsClass.hIconSm = nullptr; //win左上角图标
	WindowsClass.hInstance = Parameters.HInstance; //窗口实例
	WindowsClass.lpfnWndProc = EngineWindowProc;
	WindowsClass.lpszClassName = L"XEngine"; //窗口名字
	WindowsClass.lpszMenuName = nullptr; //
	WindowsClass.style = CS_HREDRAW | CS_VREDRAW; //垂直水平绘制窗口

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

	return 0;
}

int FWinEngine::InitDirectX3D()
{
	
	return 0;
}
