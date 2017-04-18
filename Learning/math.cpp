#include "math.h"

void MathState::Initialize(HWND Window)
{
	Window = Window;
	DeviceContext = GetWindowDC(Window);
	if (!EditA)
	{
		EditA = CreateWindowExW(
			0, L"EDIT", NULL,
			WS_CHILD | WS_VISIBLE | WS_DLGFRAME |
			ES_LEFT,
			70, 150, 50, 30, Window, (HMENU)112,
			(HINSTANCE)GetWindowLong(Window,
				GWL_HINSTANCE), NULL);
	}

	if (!EditB)
	{
		EditB = CreateWindowExW(
			0, L"EDIT", NULL,
			WS_CHILD | WS_VISIBLE | WS_DLGFRAME |
			ES_LEFT,
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

	Display(0);
}

void MathState::Loop()
{
}

void MathState::AdditionDisplay()
{
	std::string CorrectNumber = std::to_string(CorrectCount);
	std::string InCorrectNumber = std::to_string(WrongCount);
	char* CorrectScore = "Correct: ";
	char* WrongScore = "Incorrect: ";

	if (DeviceContext)
	{
		TextOut(DeviceContext, 140, 190, "+  ", 3);
		TextOut(DeviceContext, 220, 190, "=", 1);

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

	unsigned int NewA = (rand() % 101);
	unsigned int NewB = (rand() % 101);

	unsigned short BufferA[16] = {};
	unsigned short BufferB[16] = {};
	Utility_IntToChar(NewA, BufferA);
	Utility_IntToChar(NewB, BufferB);
	SendMessageW(EditA,
		WM_SETTEXT, 0, (LPARAM)BufferA);
	SendMessageW(EditB,
		WM_SETTEXT, 0, (LPARAM)BufferB);

	SendMessageW(EditC, WM_SETTEXT, 0,
		(LPARAM)"");
}

void MathState::AdditionTest()
{
	const unsigned int BufferSize = 16;
	char BufferA[BufferSize] = {};
	char BufferB[BufferSize] = {};
	char BufferC[BufferSize] = {};
	GetWindowText(EditA, BufferA, BufferSize);
	int A = atoi(BufferA);
	GetWindowText(EditB, BufferB, BufferSize);
	int B = atoi(BufferB);
	GetWindowText(EditC, BufferC, BufferSize);
	int UserC = atoi(BufferC);

	int C = A + B;

	if (C == UserC)
	{
		CorrectCount++;
		Display(1);
	}
	else
	{
		WrongCount++;
		Display(2);
	}
}

void MathState::SubtractionDisplay()
{
	std::string CorrectNumber = std::to_string(CorrectCount);
	std::string InCorrectNumber = std::to_string(WrongCount);
	char* CorrectScore = "Correct: ";
	char* WrongScore = "Incorrect: ";

	if (DeviceContext)
	{
		TextOut(DeviceContext, 140, 190, " - ", 3);
		TextOut(DeviceContext, 220, 190, "=", 1);

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

	unsigned int NewA = (rand() % 101);
	unsigned int NewB = (rand() % 101);

	unsigned short BufferA[16] = {};
	unsigned short BufferB[16] = {};
	Utility_IntToChar(NewA, BufferA);
	Utility_IntToChar(NewB, BufferB);
	SendMessageW(EditA,
		WM_SETTEXT, 0, (LPARAM)BufferA);
	SendMessageW(EditB,
		WM_SETTEXT, 0, (LPARAM)BufferB);

	SendMessageW(EditC, WM_SETTEXT, 0,
		(LPARAM)"");
}

void MathState::SubtractionTest()
{
	const unsigned int BufferSize = 16;
	char BufferA[BufferSize] = {};
	char BufferB[BufferSize] = {};
	char BufferC[BufferSize] = {};
	GetWindowText(EditA, BufferA, BufferSize);
	int A = atoi(BufferA);
	GetWindowText(EditB, BufferB, BufferSize);
	int B = atoi(BufferB);
	GetWindowText(EditC, BufferC, BufferSize);
	int UserC = atoi(BufferC);

	int C = A - B;

	if (C == UserC)
	{
		CorrectCount++;
		Display(1);
	}
	else
	{
		WrongCount++;
		Display(2);
	}
}

void MathState::MultiplicationDisplay()
{
	std::string CorrectNumber = std::to_string(CorrectCount);
	std::string InCorrectNumber = std::to_string(WrongCount);
	char* CorrectScore = "Correct: ";
	char* WrongScore = "Incorrect: ";

	if (DeviceContext)
	{
		TextOut(DeviceContext, 140, 190, "x  ", 3);
		TextOut(DeviceContext, 220, 190, "=", 1);

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

	unsigned int NewA = (rand() % 13);
	unsigned int NewB = (rand() % 13);

	unsigned short BufferA[16] = {};
	unsigned short BufferB[16] = {};
	Utility_IntToChar(NewA, BufferA);
	Utility_IntToChar(NewB, BufferB);
	SendMessageW(EditA,
		WM_SETTEXT, 0, (LPARAM)BufferA);
	SendMessageW(EditB,
		WM_SETTEXT, 0, (LPARAM)BufferB);

	SendMessageW(EditC, WM_SETTEXT, 0,
		(LPARAM)"");
}

void MathState::MultiplicationTest()
{
	const unsigned int BufferSize = 16;
	char BufferA[BufferSize] = {};
	char BufferB[BufferSize] = {};
	char BufferC[BufferSize] = {};
	GetWindowText(EditA, BufferA, BufferSize);
	int A = atoi(BufferA);
	GetWindowText(EditB, BufferB, BufferSize);
	int B = atoi(BufferB);
	GetWindowText(EditC, BufferC, BufferSize);
	int UserC = atoi(BufferC);

	int C = A * B;

	if (C == UserC)
	{
		CorrectCount++;
		Display(1);
	}
	else
	{
		WrongCount++;
		Display(2);
	}
}

void MathState::DivisonDisplay()
{
	std::string CorrectNumber = std::to_string(CorrectCount);
	std::string InCorrectNumber = std::to_string(WrongCount);
	char* CorrectScore = "Correct: ";
	char* WrongScore = "Incorrect: ";

	if (DeviceContext)
	{
		TextOut(DeviceContext, 140, 190, "%", 1);
		TextOut(DeviceContext, 220, 190, "=", 1);

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

	unsigned int NewB = (rand() % 13);
	if (NewB == 0)
	{
		NewB = 1;
	}

	unsigned int NewA = NewB * ((unsigned int)rand() % 13);

	unsigned short BufferA[16] = {};
	unsigned short BufferB[16] = {};
	Utility_IntToChar(NewA, BufferA);
	Utility_IntToChar(NewB, BufferB);
	SendMessageW(EditA,
		WM_SETTEXT, 0, (LPARAM)BufferA);
	SendMessageW(EditB,
		WM_SETTEXT, 0, (LPARAM)BufferB);

	SendMessageW(EditC, WM_SETTEXT, 0,
		(LPARAM)"");
}

void MathState::DivisionTest()
{
	const unsigned int BufferSize = 16;
	char BufferA[BufferSize] = {};
	char BufferB[BufferSize] = {};
	char BufferC[BufferSize] = {};
	GetWindowText(EditA, BufferA, BufferSize);
	int A = atoi(BufferA);
	GetWindowText(EditB, BufferB, BufferSize);
	int B = atoi(BufferB);
	GetWindowText(EditC, BufferC, BufferSize);
	int UserC = atoi(BufferC);

	int C;
	if (B == 0)
	{
		C = 1; //TODO: Error
	}
	else
	{
		C = A / B;
	}

	if (C == UserC)
	{
		CorrectCount++;
		Display(1);
	}
	else
	{
		WrongCount++;
		Display(2);
	}
}

void MathState::Display(unsigned int SolutionState)
{
	if (SolutionState != 2)
	{
		ProblemState = ((unsigned int)rand() % 4);
	}

	switch (ProblemState)
	{
	case 0:
	{
		if (SolutionState == 2)
		{
			SendMessageW(EditC, WM_SETTEXT, 0,
				(LPARAM)"");
		
			std::string InCorrectNumber = std::to_string(WrongCount);
			TextOut(DeviceContext, 94, 263, InCorrectNumber.c_str(),
				InCorrectNumber.length());
		}
		else
		{
			AdditionDisplay();
		}
	} break;
	case 1:
	{
		if (SolutionState == 2)
		{
			SendMessageW(EditC, WM_SETTEXT, 0,
				(LPARAM)"");

			std::string InCorrectNumber = std::to_string(WrongCount);
			TextOut(DeviceContext, 94, 263, InCorrectNumber.c_str(),
				InCorrectNumber.length());
		}
		else
		{
			SubtractionDisplay();
		}
	} break;
	case 2:
	{
		if (SolutionState == 2)
		{
			SendMessageW(EditC, WM_SETTEXT, 0,
				(LPARAM)"");
		
			std::string InCorrectNumber = std::to_string(WrongCount);
			TextOut(DeviceContext, 94, 263, InCorrectNumber.c_str(),
				InCorrectNumber.length());
		}
		else
		{
			MultiplicationDisplay();
		}
	} break;
	case 3:
	{
		if (SolutionState == 2)
		{
			SendMessageW(EditC, WM_SETTEXT, 0,
				(LPARAM)"");
		
			std::string InCorrectNumber = std::to_string(WrongCount);
			TextOut(DeviceContext, 94, 263, InCorrectNumber.c_str(),
				InCorrectNumber.length());
		}
		else
		{
			DivisonDisplay();
		}
	} break;
	default: break;
	}
}

void MathState::CheckAnswer(unsigned short Command)
{
	if (Command == 103)
	{
		switch (ProblemState)
		{
		case 0:
		{
			AdditionTest();
		} break;
		case 1:
		{
			SubtractionTest();
		} break;
		case 2:
		{
			MultiplicationTest();
		} break;
		case 3:
		{
			DivisionTest();
		} break;
		default: break;
		}

	}
}

void MathState::CleanUp()
{
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