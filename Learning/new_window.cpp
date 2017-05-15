#include "new_window.h"

LRESULT CALLBACK NewWindowProc(HWND DictWindow, UINT Message,
	WPARAM wParam, LPARAM lParam);

NewWindow::
NewWindow()
{

}

NewWindow::
~NewWindow()
{

}

unsigned char NewWindow::
Initialize(int SetWidth, int SetHeight, int XPos, 
	int YPos, HWND ToWindow, HINSTANCE Instance)
{
	if (!Window)
	{
		BelongsToWindow = ToWindow;
		Width = SetWidth;
		Height = SetHeight;
		XPosition = XPos;
		YPosition = YPos;

		WNDCLASSEX NewWindowClassStruct;

		if (!GetClassInfoEx(Instance, "NewWindow", &NewWindowClassStruct))
		{
			NewWindowClassStruct.cbSize = sizeof(WNDCLASSEX);
			NewWindowClassStruct.style = CS_OWNDC;
			NewWindowClassStruct.lpfnWndProc = NewWindowProc;
			NewWindowClassStruct.cbClsExtra = 0;
			NewWindowClassStruct.cbWndExtra = 0;
			NewWindowClassStruct.hInstance = Instance;
			NewWindowClassStruct.hIcon = 0;
			NewWindowClassStruct.hCursor =
				LoadCursor(NULL, IDC_ARROW);
			NewWindowClassStruct.hbrBackground =
				(HBRUSH)(COLOR_WINDOW + 1);
			NewWindowClassStruct.lpszMenuName = NULL;
			NewWindowClassStruct.lpszClassName = "NewWindow";
			NewWindowClassStruct.hIconSm = 0;

			if (!RegisterClassEx(&NewWindowClassStruct))
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
		State = 1;
	}
	else
	{
		Clean();
	}

	return 0;
}

unsigned char NewWindow::
GetState()
{
	return State;
}

void NewWindow::
Clean()
{
	if (Window)
	{
		DestroyWindow(Window);
		Window = 0;
		State = 0;
	}
}

void NewWindow::
SetCommand(WPARAM wParam)
{
	Command = wParam;
}

void NewWindow::
ClearCommand()
{
	Command = 0;
}

//void Window_UpdateStates(NewWindow* Window)
//{
//
//}

LRESULT CALLBACK 
NewWindowProc(HWND DictWindow, UINT Message,
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
		//SetCommand(wParam);
	} break;
	case WM_DESTROY:
		break;
	default:
		return DefWindowProc(DictWindow, Message, wParam, lParam);
	}

	return 0;
}