#include "Language.h"

LRESULT CALLBACK DictionaryProc(HWND DictWindow, UINT Message,
	WPARAM wParam, LPARAM lParam);

void LanguageState::Initialize(HWND window, State* SaveState)
{
	Save = SaveState;

	if (TotalWordCount)
	{
		Window = window;
		DeviceContext = GetWindowDC(Window);
		Instance = (HINSTANCE)GetWindowLong(Window, GWL_HINSTANCE);

		if (!CheckButton)
		{
			CheckButton = CreateWindow("BUTTON",
				"Check",
				WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
				235, 210, 100, 40, Window, (HMENU)102,
				(HINSTANCE)GetWindowLong(Window,
					GWL_HINSTANCE), NULL);
		}

		if (!DictionaryButton)
		{
			DictionaryButton = CreateWindow("BUTTON",
				"Dictionary >>",
				WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
				460, 230, 100, 20, Window, (HMENU)104,
				(HINSTANCE)GetWindowLong(Window,
					GWL_HINSTANCE), NULL);
		}

		if (!EditWindowInput)
		{
			EditWindowInput = CreateWindowExW(
				0, L"EDIT", NULL,
				WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_DLGFRAME |
				ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL,
				20, 150, 250, 50, Window, (HMENU)110,
				(HINSTANCE)GetWindowLong(Window,
					GWL_HINSTANCE), NULL);
		}

		if (!EditWindowOutput)
		{
			EditWindowOutput = CreateWindowExW(
				0, L"EDIT", NULL,
				WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_DLGFRAME |
				ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL,
				310, 150, 250, 50, Window, (HMENU)111,
				(HINSTANCE)GetWindowLong(Window,
					GWL_HINSTANCE), NULL);
		}

		if (Save->Set)
		{
			CurrentWordChoice = Save->Words[0];
			SendMessageW(EditWindowOutput, WM_SETTEXT, 0,
				(LPARAM)Words[CurrentWordChoice].Russian);
		}
		else
		{
			if (TotalWordCount > 0)
			{
				CurrentWordChoice =
					(unsigned int)(rand() % TotalWordCount);
				Save->Set = true;
				Save->Words[0] = CurrentWordChoice;
			}
			SendMessageW(EditWindowOutput, WM_SETTEXT, 0,
				(LPARAM)Words[CurrentWordChoice].Russian);
		}

		SetFocus(EditWindowInput);
	}
	else
	{
		MessageBox(0, "Load Word Library First",0 ,0); //Error
	}
}

bool LanguageState::LoadDatabase(char* FileName)
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
						TotalWordCount++;
						WordIndex = 0;
					}
					else
					{
						if (Russian)
						{
							Words[WordUnitIndex].Russian[WordIndex] =
								(line[i] << 8) | line[i + 1];
							Words[WordUnitIndex].RussianLength++;
							WordIndex++;
						}
						else
						{
							Words[WordUnitIndex].English[WordIndex] = 
								(line[i] << 8) | line[i + 1];
							Words[WordUnitIndex].EnglishLength++;
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

void LanguageState::Loop()
{
	if (CheckButton)
	{
		Display();
	}
}

void LanguageState::Display()
{
	std::string CorrectNumber = std::to_string(CorrectCount);
	std::string InCorrectNumber = std::to_string(WrongCount);
	char* CorrectScore = "Correct: ";
	char* WrongScore = "Incorrect: ";

	if (DeviceContext)
	{
		TextOut(DeviceContext, 29, 243, CorrectScore, 9);
		TextOut(DeviceContext, 29, 263, WrongScore, 11);
		TextOut(DeviceContext, 94, 243, CorrectNumber.c_str(),
			CorrectNumber.length());
		TextOut(DeviceContext, 94, 263, InCorrectNumber.c_str(),
			InCorrectNumber.length());
	}
}

bool LanguageState::CompareStrings()
{
	const unsigned int BufferSize = 256;
	char StringBuffer1[BufferSize];

	GetWindowText(EditWindowInput, StringBuffer1, BufferSize);

	unsigned int Index = 0;
	if (StringBuffer1[Index] == '\0')
	{
		return 0;
	}
	while (StringBuffer1[Index] != '\0')
	{
		if (Words[CurrentWordChoice].English[Index])
		{
			if (StringBuffer1[Index] != 
				Words[CurrentWordChoice].English[Index])
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

void LanguageState::CheckClickStates(unsigned short Command)
{

	switch (Command)
	{
	case 102:
	{
		if (CompareStrings()) // correct
		{
			CorrectCount++;
			if (TotalWordCount > 0)
			{
				CurrentWordChoice = 
					(unsigned int)(rand() % TotalWordCount);
				Save->Words[0] = CurrentWordChoice;
			}
			SendMessageW(EditWindowOutput, WM_SETTEXT, 0, 
				(LPARAM)Words[CurrentWordChoice].Russian);
			SendMessageW(EditWindowInput,
				WM_SETTEXT, 0, (LPARAM)"");
		}
		else
		{
			WrongCount++;
			SendMessageW(EditWindowOutput, WM_SETTEXT, 0, 
				(LPARAM)Words[CurrentWordChoice].Russian);
			SendMessageW(EditWindowInput,
				WM_SETTEXT, 0, (LPARAM)"");
		}
		SetFocus(EditWindowInput);
	} break;
	case 104:
	{
		DisplayDictionary();
	}
	default: break;
	}
}

void LanguageState::DisplayDictionary()
{
	if (Dictionary)
	{
		DestroyWindow(DictionaryList);
		DictionaryList = 0;
		DestroyWindow(Dictionary);
		Dictionary = 0;
	}
	else
	{
		WNDCLASSEX DictWindowClassStruct;
		
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

		RECT WindowRect = {};
		GetClientRect(Window, &WindowRect);
		MapWindowPoints(Window, GetParent(Window), (LPPOINT)&WindowRect, 2);


		Dictionary = CreateWindowExW(
			WS_EX_CLIENTEDGE,
			L"Dictionary",
			L"Dictionary",
			WS_BORDER | WS_VISIBLE,
			WindowRect.right - 8, WindowRect.top - 33, 300, 300,
			Window, NULL, Instance, NULL);

		if (Dictionary)
		{
			UpdateWindow(Dictionary);
			ShowWindow(Dictionary, SW_SHOW);

			if (!DictionaryList)
			{
				DictionaryList = CreateWindowExW(
					0, L"LISTBOX", NULL,
					WS_CHILD | WS_VISIBLE | WS_DLGFRAME |
					ES_LEFT | ES_AUTOVSCROLL | WS_VSCROLL,
					10, 10, 260, 245, Dictionary, (HMENU)210,
					Instance, NULL);

				HFONT hFont = CreateFont(13, 0, 0, 0, FW_DONTCARE, FALSE,
					FALSE, FALSE, ANSI_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS,
					DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, TEXT("Tahoma"));

				SendMessage(DictionaryList, WM_SETFONT, (WPARAM)hFont, TRUE);
					
				// LB_INITSTORAGE Initializing storage later to speed it up
				for (unsigned int Word = 0; Word < TotalWordCount; Word++)
				{
					unsigned short Buffer[64] = {};
					unsigned int Index = 0;
					for (unsigned int i = 0; i < Words[Word].EnglishLength; i++)
					{
						Buffer[i] = Words[Word].English[i];
						Index++;
					}
					Buffer[Index] = 32;
					Index++;
					Buffer[Index] = 124;
					Index++;
					Buffer[Index] = 32;
					Index++;
					for (unsigned int i = 0; i < Words[Word].RussianLength; i++)
					{
						Buffer[i + Index] = Words[Word].Russian[i];
					}

					SendMessageW(DictionaryList, LB_INSERTSTRING, 0,
						(LPARAM)Buffer);
				}
			}
		}
		else
		{
			MessageBox(NULL, "Dictionary Window Did Not Create.",
				"Error!", MB_ICONEXCLAMATION | MB_OK);
		}
	}
}

bool LanguageState::ChangeBackground()
{
	return 0;
}

void LanguageState::CleanUp()
{
	if (CheckButton)
	{
		DestroyWindow(CheckButton);
		CheckButton = 0;
	}

	if (DictionaryButton)
	{
		DestroyWindow(DictionaryButton);
		DictionaryButton = 0;
	}

	if (DictionaryList)
	{
		DestroyWindow(DictionaryList);
		DictionaryList = 0;
	}

	if (Dictionary)
	{
		DestroyWindow(Dictionary);
		Dictionary = 0;
	}

	if (EditWindowInput)
	{
		DestroyWindow(EditWindowInput);
		EditWindowInput = 0;
	}

	if (EditWindowOutput)
	{
		DestroyWindow(EditWindowOutput);
		EditWindowOutput = 0;
	}

	if (DeviceContext)
	{
		std::string ClearLine = "                         ";
		TextOut(DeviceContext, 29, 243, ClearLine.c_str(), 23);
		TextOut(DeviceContext, 29, 263, ClearLine.c_str(), 23);

		ReleaseDC(Window, DeviceContext);
		DeviceContext = 0;
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
	} break;
	case WM_DESTROY:
		break;
	default:
		return DefWindowProc(DictWindow, Message, wParam, lParam);
	}

	return 0;
}