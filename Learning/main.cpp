#include "Language.h"

LRESULT CALLBACK WndProc(HWND Window, UINT Message, 
	WPARAM wParam, LPARAM lParam);

LanguageState RussianToEnglish;
MathState Math;
static State SaveState;

int WINAPI WinMain(HINSTANCE Instance, HINSTANCE PrevInstance,
	LPSTR CommandLine, int CommandShow)
{
	unsigned int WindowWidth = 600, WindowHeight = 300;
	srand((unsigned int)time(NULL));

	WNDCLASSEX WindowsClassStructure;
	WindowsClassStructure.cbSize = sizeof(WNDCLASSEX);
	WindowsClassStructure.style = CS_OWNDC;
	WindowsClassStructure.lpfnWndProc = WndProc;
	WindowsClassStructure.cbClsExtra = 0;
	WindowsClassStructure.cbWndExtra = 0;
	WindowsClassStructure.hInstance = Instance;
	WindowsClassStructure.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WindowsClassStructure.hCursor = LoadCursor(NULL, IDC_ARROW);
	WindowsClassStructure.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	WindowsClassStructure.lpszMenuName = NULL;
	WindowsClassStructure.lpszClassName = (const char*)"LanguageLearning";
	WindowsClassStructure.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassEx(&WindowsClassStructure))
	{
		MessageBox(NULL, "Window Registration Failed!", "Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 1;
	}

	HWND Window = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		(const char*)"LanguageLearning",
		"Language Learning",
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX,
		CW_USEDEFAULT, CW_USEDEFAULT, WindowWidth, WindowHeight,
		NULL, NULL, Instance, NULL);

	if (!Window)
	{
		MessageBox(NULL, "Window Creation Failed!", "Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 1;
	}

	HWND EnglishButton = CreateWindow("BUTTON",
		"English",
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
		10, 10, 100, 30, Window, (HMENU)100,
		(HINSTANCE)GetWindowLong(Window, GWL_HINSTANCE), NULL);

	HWND MathButton = CreateWindow("BUTTON",
		"Mathematics",
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
		120, 10, 100, 30, Window, (HMENU)101,
		(HINSTANCE)GetWindowLong(Window, GWL_HINSTANCE), NULL);

	if (RussianToEnglish.LoadDatabase("wordlist.txt"))
	{
		MessageBox(0, "No word list", 0, 0);
		return 1;
	}

	RussianToEnglish.Initialize(Window, &SaveState);

	UpdateWindow(Window);
	ShowWindow(Window, CommandShow);

	MSG Message = {};

	while (Message.message != WM_QUIT)
	{
		if (PeekMessage(&Message, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}
		if (SaveState.ActiveModule == 1)
		{
			RussianToEnglish.Loop();
		}
		else if (SaveState.ActiveModule == 2)
		{
			Math.Loop();
		}
	}
	return 0;
}

LRESULT CALLBACK WndProc(HWND Window, UINT Message, 
	WPARAM wParam, LPARAM lParam)
{
	switch (Message)
	{
	case WM_CREATE:
		break;
	case WM_CLOSE:
		PostQuitMessage(0);
		break;
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case 100:
		{
			Math.CleanUp();
			RussianToEnglish.Initialize(Window, &SaveState);
		} break;
		case 101:
		{
			RussianToEnglish.CleanUp();
			Math.Initialize(Window, &SaveState);
		} break;
		default: break;
		}

		unsigned short Command = LOWORD(wParam);
		RussianToEnglish.UpdateStates(wParam);
		Math.UpdateStates(wParam);
		
	} break;
	case WM_KEYDOWN:
	{
		switch (wParam)
		{
		case VK_RIGHT:
		{
			RussianToEnglish.UpdateStates(wParam);
			Math.UpdateStates(wParam);
		} break;
		}
	} break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(Window, Message, wParam, lParam);
	}

	return 0;
}