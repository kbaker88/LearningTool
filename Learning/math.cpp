#include "math.h"

void MathState::Initialize(HWND window, State *SaveState)
{
	Save = SaveState;
	Window = window;
	DeviceContext = GetWindowDC(Window);
	if (!EditA)
	{
		EditA = CreateWindowExW(
			0, L"EDIT", NULL,
			WS_CHILD | WS_VISIBLE | WS_DLGFRAME |
			ES_LEFT | ES_READONLY,
			70, 150, 50, 30, Window, (HMENU)112,
			(HINSTANCE)GetWindowLong(Window,
				GWL_HINSTANCE), NULL);
	}

	if (!EditB)
	{
		EditB = CreateWindowExW(
			0, L"EDIT", NULL,
			WS_CHILD | WS_VISIBLE | WS_DLGFRAME |
			ES_LEFT | ES_READONLY,
			150, 150, 50, 30, Window, (HMENU)113,
			(HINSTANCE)GetWindowLong(Window,
				GWL_HINSTANCE), NULL);
	}

	if (!EditC)
	{
		EditC = CreateWindowExW(
			0, L"EDIT", NULL,
			WS_CHILD | WS_VISIBLE | WS_DLGFRAME |
			ES_LEFT,
			230, 150, 50, 30, Window, (HMENU)114,
			(HINSTANCE)GetWindowLong(Window, 
				GWL_HINSTANCE), NULL);
	}

	if (!CheckButton)
	{
		CheckButton = CreateWindow("BUTTON",
			"Check",
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
			235, 210, 100, 40, Window, (HMENU)103,
			(HINSTANCE)GetWindowLong(Window,
				GWL_HINSTANCE), NULL);
	}

	if (Save->MathSet)
	{
		A = Save->Numbers[0];
		B = Save->Numbers[1];
		ProblemState = Save->Numbers[2];
		Display(3);
	}
	else
	{
		Display(0);
		Save->MathSet = true;
		Save->Numbers[0] = A;
		Save->Numbers[1] = B;
		Save->Numbers[2] = ProblemState;
	}
}

void MathState::Loop()
{
}

void MathState::Display(unsigned int SolutionState)
{
	if ((SolutionState != 2) && (SolutionState != 3))
	{
		ProblemState = ((unsigned int)rand() % 4);
	}
	//////////////////////////////////////////////////////////////////
	std::string CorrectNumber = std::to_string(CorrectCount);
	std::string InCorrectNumber = std::to_string(WrongCount);
	char* CorrectScore = "Correct: ";
	char* WrongScore = "Incorrect: ";

	if (DeviceContext)
	{
		switch (ProblemState)
		{
		case 0:
		{
			if ((SolutionState != 2) && (SolutionState != 3))
			{
				A = (rand() % 101);
				B = (rand() % 101);
			}
			TextOut(DeviceContext, 140, 190, "+  ", 3);
			TextOut(DeviceContext, 220, 190, "=", 1);
		} break;
		case 1:
		{
			if ((SolutionState != 2) && (SolutionState != 3))
			{
				A = (rand() % 101);
				B = (rand() % 101);
			}
			TextOut(DeviceContext, 140, 190, " - ", 3);
			TextOut(DeviceContext, 220, 190, "=", 1);
		} break;
		case 2:
		{
			if ((SolutionState != 2) && (SolutionState != 3))
			{
				A = (rand() % 13);
				B = (rand() % 13);
			}
			TextOut(DeviceContext, 140, 190, "x  ", 3);
			TextOut(DeviceContext, 220, 190, "=", 1);
		} break;
		case 3:
		{
			if ((SolutionState != 2) && (SolutionState != 3))
			{
				B = (rand() % 13);
				if (B == 0)
				{
					B = 1;
				}

				A = B * ((unsigned int)rand() % 13);
			}
			TextOut(DeviceContext, 140, 190, "%", 1);
			TextOut(DeviceContext, 220, 190, "=", 1);
		} break;
		default: break;
		}

		std::string CorrectNumber = std::to_string(CorrectCount);
		std::string InCorrectNumber = std::to_string(WrongCount);
		char* CorrectScore = "Correct: ";
		char* WrongScore = "Incorrect: ";
		TextOut(DeviceContext, 29, 243, CorrectScore, 9);
		TextOut(DeviceContext, 29, 263, WrongScore, 11);
		TextOut(DeviceContext, 94, 243, CorrectNumber.c_str(),
			CorrectNumber.length());
		TextOut(DeviceContext, 94, 263, InCorrectNumber.c_str(),
			InCorrectNumber.length());
	}
	else
	{
		MessageBox(0, "Device Context Not Found", 0, 0);
	}


	unsigned short BufferA[16] = {};
	unsigned short BufferB[16] = {};
	Utility_IntToChar(A, BufferA);
	Utility_IntToChar(B, BufferB);
	SendMessageW(EditA,
		WM_SETTEXT, 0, (LPARAM)BufferA);
	SendMessageW(EditB,
		WM_SETTEXT, 0, (LPARAM)BufferB);

	SendMessageW(EditC, WM_SETTEXT, 0,
		(LPARAM)"");

	SetFocus(EditC);
}

void MathState::Commands(unsigned short Command)
{
	if (Command == 103)
	{
		CheckAnswer();
	}
}

void MathState::CheckAnswer()
{
	const unsigned int BufferSize = 16;
	char BufferA[BufferSize] = {};
	char BufferB[BufferSize] = {};
	char BufferC[BufferSize] = {};
	GetWindowText(EditA, BufferA, BufferSize);
	A = atoi(BufferA);
	GetWindowText(EditB, BufferB, BufferSize);
	B = atoi(BufferB);
	GetWindowText(EditC, BufferC, BufferSize);
	int UserC = atoi(BufferC);
	int C = 0;

	switch (ProblemState)
	{
	case 0:
	{
		C = A + B;
	} break;
	case 1:
	{
		C = A - B;
	} break;
	case 2:
	{
		C = A * B;
	} break;
	case 3:
	{
		if (B == 0)
		{
			C = 1; //TODO: Error
		}
		else
		{
			C = A / B;
		}
	} break;
	default: break;
	}

	if (C == UserC)
	{
		CorrectCount++;
		Display(1);
		Save->Numbers[0] = A;
		Save->Numbers[1] = B;
		Save->Numbers[2] = ProblemState;
	}
	else
	{
		WrongCount++;
		Display(2);
	}
}

void MathState::CleanUp()
{
	if (Save)
	{
		Save->MathSet = true;
		Save->Numbers[0] = A;
		Save->Numbers[1] = B;
		Save->Numbers[2] = ProblemState;
	}

	if (CheckButton)
	{
		DestroyWindow(CheckButton);
		CheckButton = 0;
	}
	if (EditA)
	{
		DestroyWindow(EditA);
		EditA = 0;
	}
	if (EditB)
	{
		DestroyWindow(EditB);
		EditB = 0;
	}
	if (EditC)
	{
		DestroyWindow(EditC);
		EditC = 0;
	}
	if (DeviceContext)
	{
		std::string ClearLine = "                       ";
		TextOut(DeviceContext, 29, 243, ClearLine.c_str(), 23);
		TextOut(DeviceContext, 29, 263, ClearLine.c_str(), 23);

		ReleaseDC(Window, DeviceContext);
		DeviceContext = 0;
	}
}