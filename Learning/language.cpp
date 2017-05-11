#include "Language.h"

LRESULT CALLBACK DictionaryProc(HWND DictWindow, UINT Message,
	WPARAM wParam, LPARAM lParam);

void LanguageState::Initialize(HWND window, State* SaveState)
{
	Save = SaveState;
	SaveState->ActiveModule = 1;

	if (TotalWordCount)
	{
		Window = window;
		DeviceContext = GetWindowDC(Window);
		Instance = (HINSTANCE)GetWindowLong(Window, GWL_HINSTANCE);

		unsigned char Error = 0;
		
		Error = Check.Initialize("Check", (HMENU)102, 100, 40,
			235, 210, Window);
		Error = Dictionary.Initialize("Dictionary >>", (HMENU)104, 100, 20,
			460, 230, Window);
		Error = InputWindow.Initialize((HMENU)110, 250, 50,
			20, 150, Window, 0X50400000);
		Error = OutputWindow.Initialize((HMENU)111, 250, 50,
			310, 150, Window, 0x50400800);

		if (Save->EnglishSet)
		{
			CurrentWordChoice = Save->Words[0];
			SendMessageW(OutputWindow.Window, WM_SETTEXT, 0,
				(LPARAM)Words[CurrentWordChoice].Russian);
		}
		else
		{
			if (TotalWordCount > 0)
			{
				CurrentWordChoice =
					(unsigned int)(rand() % TotalWordCount);
				Save->EnglishSet = true;
				Save->Words[0] = CurrentWordChoice;
			}
			SendMessageW(OutputWindow.Window, WM_SETTEXT, 0,
				(LPARAM)Words[CurrentWordChoice].Russian);
		}

		SetFocus(InputWindow.Window);
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
				// NOTE: * to skip the wide char line symbols
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
	if (Check.GetState() == 1)
	{
		const unsigned int BufferSize = 256;
		unsigned short StringBuffer1[BufferSize];

		GetWindowTextW(InputWindow.Window, (LPWSTR)StringBuffer1, 
			BufferSize);

		if (Utility_CompareCharString(Words[CurrentWordChoice].English, 
			StringBuffer1, Words[CurrentWordChoice].EnglishLength))
		{ 
			CorrectCount++;
			if (TotalWordCount > 0)
			{
				CurrentWordChoice =
					(unsigned int)(rand() % TotalWordCount);
				Save->Words[0] = CurrentWordChoice;
			}
			SetWindowTextW(OutputWindow.Window,
				(LPCWSTR)Words[CurrentWordChoice].Russian);
			SetWindowText(InputWindow.Window, "");
		}
		else
		{
			WrongCount++;
			SetWindowTextW(OutputWindow.Window,
				(LPCWSTR)Words[CurrentWordChoice].Russian);
			SetWindowText(InputWindow.Window, "");
		}
		SetFocus(InputWindow.Window);
	}
	if (Dictionary.GetState() == 1)
	{
		DisplayDictionary();
	}
	Display();
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

void LanguageState::UpdateStates(WPARAM Command)
{
	Check.UpdateState(Command);
	Dictionary.UpdateState(Command);
}

void LanguageState::DisplayDictionary()
{
	if (DictionaryWindow)
	{
		DestroyWindow(DictionaryList);
		DictionaryList = 0;
		DestroyWindow(DictionaryWindow);
		DictionaryWindow = 0;
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
			DictWindowClassStruct.hCursor = 
				LoadCursor(NULL, IDC_ARROW);
			DictWindowClassStruct.hbrBackground = 
				(HBRUSH)(COLOR_WINDOW + 1);
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
		MapWindowPoints(Window, GetParent(Window), 
			(LPPOINT)&WindowRect, 2);

		DictionaryWindow = CreateWindowExW( WS_EX_CLIENTEDGE,
			L"Dictionary", L"Dictionary", WS_BORDER | WS_VISIBLE,
			WindowRect.right - 8, WindowRect.top - 33, 300, 300,
			Window, NULL, Instance, NULL);

		if (DictionaryWindow)
		{
			UpdateWindow(DictionaryWindow);
			ShowWindow(DictionaryWindow, SW_SHOW);

			if (!DictionaryList)
			{
				DictionaryList = CreateWindowExW(
					0, L"LISTBOX", NULL,
					WS_CHILD | WS_VISIBLE | WS_DLGFRAME |
					ES_LEFT | ES_AUTOVSCROLL | WS_VSCROLL,
					10, 10, 260, 245, DictionaryWindow, (HMENU)210,
					Instance, NULL);

				HFONT hFont = CreateFont(13, 0, 0, 0, FW_DONTCARE, FALSE,
					FALSE, FALSE, ANSI_CHARSET, OUT_TT_PRECIS, 
					CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | 
					FF_DONTCARE, TEXT("Tahoma"));

				SendMessage(DictionaryList, WM_SETFONT, (WPARAM)hFont, TRUE);
					
				// LB_INITSTORAGE Initializing storage later to speed it up
				for (unsigned int Word = 0; Word < TotalWordCount; Word++)
				{
					unsigned short Buffer[64] = {};
					unsigned int Index = 0;
					for (unsigned int i = 0;
						i < Words[Word].EnglishLength;
						i++)
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
					for (unsigned int i = 0; 
						i < Words[Word].RussianLength; 
						i++)
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
	Check.Clean();
	Dictionary.Clean();

	if (DictionaryList)
	{
		DestroyWindow(DictionaryList);
		DictionaryList = 0;
	}

	if (DictionaryWindow)
	{
		DestroyWindow(DictionaryWindow);
		DictionaryWindow = 0;
	}

	InputWindow.Clean();
	OutputWindow.Clean();

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