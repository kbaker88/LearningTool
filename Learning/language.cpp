#include "Language.h"

LanguageState Temporary;

LRESULT CALLBACK DictionaryProc(HWND DictWindow, UINT Message,
	WPARAM wParam, LPARAM lParam);

void Language_Initialize(HWND Window)
{
	if (Temporary.TotalWordCount)
	{
		Temporary.Window = Window;
		Temporary.DeviceContext = GetWindowDC(Window);

		if (!Temporary.CheckButton)
		{
			Temporary.CheckButton = CreateWindow("BUTTON",
				"Check",
				WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
				235, 210, 100, 40, Temporary.Window, (HMENU)102,
				(HINSTANCE)GetWindowLong(Temporary.Window,
					GWL_HINSTANCE), NULL);
		}

		if (!Temporary.DictionaryButton)
		{
			Temporary.DictionaryButton = CreateWindow("BUTTON",
				"Dictionary >>",
				WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
				460, 230, 100, 20, Temporary.Window, (HMENU)104,
				(HINSTANCE)GetWindowLong(Temporary.Window,
					GWL_HINSTANCE), NULL);
		}

		if (!Temporary.EditWindowInput)
		{
			Temporary.EditWindowInput = CreateWindowExW(
				0, L"EDIT", NULL,
				WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_DLGFRAME |
				ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL,
				20, 150, 250, 50, Temporary.Window, (HMENU)110,
				(HINSTANCE)GetWindowLong(Temporary.Window,
					GWL_HINSTANCE), NULL);
		}

		if (!Temporary.EditWindowOutput)
		{
			Temporary.EditWindowOutput = CreateWindowExW(
				0, L"EDIT", NULL,
				WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_DLGFRAME |
				ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL,
				310, 150, 250, 50, Temporary.Window, (HMENU)111,
				(HINSTANCE)GetWindowLong(Temporary.Window,
					GWL_HINSTANCE), NULL);
		}

		if (Temporary.TotalWordCount > 0)
		{
			Temporary.CurrentWordChoice =
				(unsigned int)(rand() % Temporary.TotalWordCount);
		}
		SendMessageW(Temporary.EditWindowOutput, WM_SETTEXT, 0,
			(LPARAM)Temporary.Words[Temporary.CurrentWordChoice].Russian);
	}
	else
	{
		MessageBox(0, "Load Word Library First",0 ,0); //Error
	}
}

bool Language_LoadDatabase(char* FileName)
{
	std::string line;
	std::ifstream myfile(FileName);
	unsigned int WordUnitIndex = 0;
	unsigned int WordIndex = 0;
	bool StartRead = false;
	if (myfile.is_open())
	{
		bool Russian = false;
		while (std::getline(myfile, line))
		{
			for (unsigned int i = 0; i < (line.length() - 4); i = i + 2)
			{
				if (StartRead)
				{
					if (line[i + 1] == 0x7E) // ~ Russian Part
					{
						Russian = true;
						WordIndex = 0;
					}
					else if (line[i + 1] == 0x7C) // | New Word
					{
						Russian = false;
						WordUnitIndex++;
						Temporary.TotalWordCount++;
						WordIndex = 0;
					}
					else
					{
						if (Russian)
						{
							Temporary.Words[WordUnitIndex].Russian[WordIndex] =
								(line[i] << 8) | line[i + 1];
							Temporary.Words[WordUnitIndex].RussianLength++;
							WordIndex++;
						}
						else
						{
							Temporary.Words[WordUnitIndex].English[WordIndex] = 
								(line[i] << 8) | line[i + 1];
							Temporary.Words[WordUnitIndex].EnglishLength++;
							WordIndex++;
						}
					}
				}
				else if (line[i + 1] == 0x2A)
				{
					StartRead = true;
				}
			}
			StartRead = false;
		}
		myfile.close();
		return 0;
	}
	else
	{
		return 1;
	}
}

void Language_Loop()
{
	if (Temporary.CheckButton)
	{
		Language_Display();
	}
}

void Language_Display()
{
	std::string CorrectNumber = std::to_string(Temporary.CorrectCount);
	std::string InCorrectNumber = std::to_string(Temporary.WrongCount);
	char* CorrectScore = "Correct: ";
	char* WrongScore = "Incorrect: ";

	if (Temporary.DeviceContext)
	{
		TextOut(Temporary.DeviceContext, 29, 243, CorrectScore, 9);
		TextOut(Temporary.DeviceContext, 29, 263, WrongScore, 11);
		TextOut(Temporary.DeviceContext, 94, 243, CorrectNumber.c_str(),
			CorrectNumber.length());
		TextOut(Temporary.DeviceContext, 94, 263, InCorrectNumber.c_str(),
			InCorrectNumber.length());
	}
}

bool Language_CompareStrings()
{
	const unsigned int BufferSize = 256;
	char StringBuffer1[BufferSize];

	GetWindowText(Temporary.EditWindowInput, StringBuffer1, BufferSize);

	unsigned int Index = 0;
	if (StringBuffer1[Index] == '\0')
	{
		return 0;
	}
	while (StringBuffer1[Index] != '\0')
	{
		if (Temporary.Words[Temporary.CurrentWordChoice].English[Index])
		{
			if (StringBuffer1[Index] != 
				Temporary.Words[Temporary.CurrentWordChoice].English[Index])
			{
				return 0;
			}
			Index++;
		}
		else
		{
			return 0;
		}
	}
	return 1;
}

void Language_CheckClickStates(unsigned short Command)
{

	switch (Command)
	{
	case 102:
	{
		if (Language_CompareStrings()) // correct
		{
			Temporary.CorrectCount++;
			if (Temporary.TotalWordCount > 0)
			{
				Temporary.CurrentWordChoice = 
					(unsigned int)(rand() % Temporary.TotalWordCount);
			}
			SendMessageW(Temporary.EditWindowOutput, WM_SETTEXT, 0, 
				(LPARAM)Temporary.Words[Temporary.CurrentWordChoice].Russian);
			SendMessageW(Temporary.EditWindowInput,
				WM_SETTEXT, 0, (LPARAM)"");
		}
		else
		{
			Temporary.WrongCount++;
			SendMessageW(Temporary.EditWindowOutput, WM_SETTEXT, 0, 
				(LPARAM)Temporary.Words[Temporary.CurrentWordChoice].Russian);
			SendMessageW(Temporary.EditWindowInput,
				WM_SETTEXT, 0, (LPARAM)"");
		}
	} break;
	case 104:
	{
		Language_DisplayDictionary();
	}
	default: break;
	}
}

void Language_DisplayDictionary()
{
	if (Temporary.Dictionary)
	{
		DestroyWindow(Temporary.Dictionary);
		Temporary.Dictionary = 0;
	}
	else
	{
		WNDCLASSEX DictWindowClassStruct;
		HINSTANCE Instance = (HINSTANCE)GetWindowLong(Temporary.Window, GWL_HINSTANCE);
		
		if (!GetClassInfoEx(Instance, "Dictionary", &DictWindowClassStruct))
		{
			DictWindowClassStruct.cbSize = sizeof(WNDCLASSEX);
			DictWindowClassStruct.style = CS_OWNDC;
			DictWindowClassStruct.lpfnWndProc = DictionaryProc;
			DictWindowClassStruct.cbClsExtra = 0;
			DictWindowClassStruct.cbWndExtra = 0;
			DictWindowClassStruct.hInstance = Instance;
			DictWindowClassStruct.hIcon = 0;
			DictWindowClassStruct.hCursor = LoadCursor(NULL, IDC_ARROW);
			DictWindowClassStruct.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
			DictWindowClassStruct.lpszMenuName = NULL;
			DictWindowClassStruct.lpszClassName = "Dictionary";
			DictWindowClassStruct.hIconSm = 0;

			if (!RegisterClassEx(&DictWindowClassStruct))
			{
				MessageBox(NULL, "Dictionary Window Registration Failed!",
					"Error!", MB_ICONEXCLAMATION | MB_OK);
			}
		}

		Temporary.Dictionary = CreateWindowEx(
			WS_EX_CLIENTEDGE,
			(const char*)"Dictionary",
			"Dictionary",
			WS_OVERLAPPEDWINDOW | WS_BORDER | WS_VISIBLE,
			CW_USEDEFAULT, CW_USEDEFAULT, 300, 300,
			Temporary.Window, NULL, Instance, NULL);

		if (Temporary.Dictionary)
		{
			UpdateWindow(Temporary.Dictionary);
			ShowWindow(Temporary.Dictionary, SW_SHOW);
		}
		else
		{
			unsigned long Error = GetLastError();
			MessageBox(NULL, "Dictionary Window Did Not Create.",
				"Error!", MB_ICONEXCLAMATION | MB_OK);
		}
	}
}

bool Language_ChangeBackground()
{

	return 0;
}

void Language_CleanUp()
{
	if (Temporary.CheckButton)
	{
		DestroyWindow(Temporary.CheckButton);
		Temporary.CheckButton = 0;
	}

	if (Temporary.DictionaryButton)
	{
		DestroyWindow(Temporary.DictionaryButton);
		Temporary.DictionaryButton = 0;
	}

	if (Temporary.Dictionary)
	{
		DestroyWindow(Temporary.Dictionary);
		Temporary.Dictionary = 0;
	}

	if (Temporary.EditWindowInput)
	{
		DestroyWindow(Temporary.EditWindowInput);
		Temporary.EditWindowInput = 0;
	}

	if (Temporary.EditWindowOutput)
	{
		DestroyWindow(Temporary.EditWindowOutput);
		Temporary.EditWindowOutput = 0;
	}

	if (Temporary.DeviceContext)
	{
		std::string ClearLine = "                    ";
		TextOut(Temporary.DeviceContext, 29, 243, ClearLine.c_str(), 20);
		TextOut(Temporary.DeviceContext, 29, 263, ClearLine.c_str(), 20);

		ReleaseDC(Temporary.Window, Temporary.DeviceContext);
		Temporary.DeviceContext = 0;
	}
}

LRESULT CALLBACK DictionaryProc(HWND DictWindow, UINT Message,
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
		switch (LOWORD(wParam))
		{
		default: break;
		}
	} break;
	case WM_DESTROY:
		break;
	default:
		return DefWindowProc(DictWindow, Message, wParam, lParam);
	}

	return 0;
}