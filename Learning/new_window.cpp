#include "new_window.h"

LRESULT CALLBACK NewWindowProc(HWND DictWindow, UINT Message,
	WPARAM wParam, LPARAM lParam);

NewWindow::NewWindow()
{

}

NewWindow::~NewWindow()
{

}

unsigned char 
NewWindow::Initialize(int SetWidth, int SetHeight, int XPos, 
	int YPos, HWND ToWindow, HINSTANCE Instance)
{
	BelongsToWindow = ToWindow;
	Width = SetWidth;
	Height = SetHeight;
	XPosition = XPos;
	YPosition = YPos;

	if (Window)
	{
		DestroyWindow(Window);
		Window = 0;
	}
	else
	{
		WNDCLASSEX WindowClassStruct;

		if (!GetClassInfoEx(Instance, "NewWindow", &WindowClassStruct))
		{
			WindowClassStruct.cbSize = sizeof(WNDCLASSEX);
			WindowClassStruct.style = CS_OWNDC;
			WindowClassStruct.lpfnWndProc = NewWindowProc;
			WindowClassStruct.cbClsExtra = 0;
			WindowClassStruct.cbWndExtra = 0;
			WindowClassStruct.hInstance = Instance;
			WindowClassStruct.hIcon = 0;
			WindowClassStruct.hCursor =
				LoadCursor(NULL, IDC_ARROW);
			WindowClassStruct.hbrBackground =
				(HBRUSH)(COLOR_WINDOW + 1);
			WindowClassStruct.lpszMenuName = NULL;
			WindowClassStruct.lpszClassName = "NewWindow";
			WindowClassStruct.hIconSm = 0;

			if (!RegisterClassEx(&WindowClassStruct))
			{
				MessageBox(NULL, "New Window Registration Failed!",
					"Error!", MB_ICONEXCLAMATION | MB_OK);
				return 1;
			}
		}

		Window = CreateWindowExW(WS_EX_CLIENTEDGE,
			L"NewWindow", L"NewWindow", WS_BORDER | WS_VISIBLE,
			XPosition, YPosition, Width, Height,
			BelongsToWindow, NULL, Instance, NULL);

		if (Window)
		{
			UpdateWindow(Window);
			ShowWindow(Window, SW_SHOW);
		}
		else
		{
			MessageBox(NULL, "New Window Did Not Create.",
				"Error!", MB_ICONEXCLAMATION | MB_OK);
			return 1;
		}
	}

	return 0;
}

void 
NewWindow::Clean()
{
	if (Window)
	{
		DestroyWindow(Window);
		Window = 0;
	}
}


LRESULT CALLBACK NewWindowProc(HWND DictWindow, UINT Message,
	WPARAM wParam, LPARAM lParam)
{
	switch (Message)
	{
	case WM_CREATE:
		break;
	case WM_CLOSE:
		break;
	case WM_COMMAND:
	{
	} break;
	case WM_DESTROY:
		break;
	default:
		return DefWindowProc(DictWindow, Message, wParam, lParam);
	}

	return 0;
}