#include "WindowsMessageProcessing.h"
#include "../../Input/Input.h"
#include <WindowsX.h>

LRESULT EngineWindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		case WM_CLOSE:
		{
			PostQuitMessage(0);
			return 0;
		}
		case WM_RBUTTONDOWN:
		{
			MoustDownDelegate.Broadcast(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
			return 0;
		}
		case WM_RBUTTONUP:
		{
			MoustUpDelegate.Broadcast(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
			return 0;
		}
		case WM_MOUSEMOVE:
		{
			MoustMoveDelegate.Broadcast(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
			return 0;
		}
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}
