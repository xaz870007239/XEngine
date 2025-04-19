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
	WindowsClass.cbSize = sizeof(WNDCLASSEX); //����ռ�ݶ���ڴ�
	WindowsClass.cbClsExtra = 0; //�Ƿ���Ҫ����ռ�
	WindowsClass.cbWndExtra = 0; //�Ƿ���Ҫ�����ڴ�
	WindowsClass.hbrBackground = nullptr; //����������Ǿ���GDI����
	WindowsClass.hCursor = LoadCursor(nullptr, IDC_ARROW); //���ü�ͷ���
	WindowsClass.hIcon = LoadIcon(nullptr, IDI_APPLICATION); //exeͼ��
	WindowsClass.hIconSm = nullptr; //win���Ͻ�ͼ��
	WindowsClass.hInstance = Parameters.HInstance; //����ʵ��
	WindowsClass.lpfnWndProc = EngineWindowProc;
	WindowsClass.lpszClassName = L"XEngine"; //��������
	WindowsClass.lpszMenuName = nullptr; //
	WindowsClass.style = CS_HREDRAW | CS_VREDRAW; //��ֱˮƽ���ƴ���

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
