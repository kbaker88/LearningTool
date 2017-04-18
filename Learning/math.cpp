#include "math.h"

MathState Temporary;

void Math_Initialize(HWND Window)
{
	Temporary.Window = Window;
	Temporary.DeviceContext = GetWindowDC(Window);
	if (!Temporary.EditA)
	{
		Temporary.EditA = CreateWindowExW(
			0, L"EDIT", NULL,
			WS_CHILD | WS_VISIBLE | WS_DLGFRAME |
			ES_LEFT,
			70, 150, 50, 30, Temporary.Window, (HMENU)112,
			(HINSTANCE)GetWindowLong(Temporary.Window,
				GWL_HINSTANCE), NULL);
	}

	if (!Temporary.EditB)
	{
		Temporary.EditB = CreateWindowExW(
			0, L"EDIT", NULL,
			WS_CHILD | WS_VISIBLE | WS_DLGFRAME |
			ES_LEFT,
			150, 150, 50, 30, Temporary.Window, (HMENU)113,
			(HINSTANCE)GetWindowLong(Temporary.Window,
				GWL_HINSTANCE), NULL);
	}

	if (!Temporary.EditC)
	{
		Temporary.EditC = CreateWindowExW(
			0, L"EDIT", NULL,
			WS_CHILD | WS_VISIBLE | WS_DLGFRAME |
			ES_LEFT,
			230, 150, 50, 30, Temporary.Window, (HMENU)114,
			(HINSTANCE)GetWindowLong(Temporary.Window, 
				GWL_HINSTANCE), NULL);
	}

	if (!Temporary.CheckButton)
	{
		Temporary.CheckButton = CreateWindow("BUTTON",
			"Check",
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
			235, 210, 100, 40, Temporary.Window, (HMENU)103,
			(HINSTANCE)GetWindowLong(Temporary.Window,
				GWL_HINSTANCE), NULL);
	}

	Math_Display(0);
}

void Math_Loop()
{
}

void Math_AdditionDisplay()
{
	std::string CorrectNumber = std::to_string(Temporary.CorrectCount);
	std::string InCorrectNumber = std::to_string(Temporary.WrongCount);
	char* CorrectScore = "Correct: ";
	char* WrongScore = "Incorrect: ";

	if (Temporary.DeviceContext)
	{
		TextOut(Temporary.DeviceContext, 140, 190, "+  ", 3);
		TextOut(Temporary.DeviceContext, 220, 190, "=", 1);

		TextOut(Temporary.DeviceContext, 29, 243, CorrectScore, 9);
		TextOut(Temporary.DeviceContext, 29, 263, WrongScore, 11);
		TextOut(Temporary.DeviceContext, 94, 243, CorrectNumber.c_str(),
			CorrectNumber.length());
		TextOut(Temporary.DeviceContext, 94, 263, InCorrectNumber.c_str(),
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
	Math_IntToChar(NewA, BufferA);
	Math_IntToChar(NewB, BufferB);
	SendMessageW(Temporary.EditA,
		WM_SETTEXT, 0, (LPARAM)BufferA);
	SendMessageW(Temporary.EditB,
		WM_SETTEXT, 0, (LPARAM)BufferB);

	SendMessageW(Temporary.EditC, WM_SETTEXT, 0,
		(LPARAM)"");
}

void Math_AdditionTest()
{
	const unsigned int BufferSize = 16;
	char BufferA[BufferSize] = {};
	char BufferB[BufferSize] = {};
	char BufferC[BufferSize] = {};
	GetWindowText(Temporary.EditA, BufferA, BufferSize);
	int A = atoi(BufferA);
	GetWindowText(Temporary.EditB, BufferB, BufferSize);
	int B = atoi(BufferB);
	GetWindowText(Temporary.EditC, BufferC, BufferSize);
	int UserC = atoi(BufferC);

	int C = A + B;

	if (C == UserC)
	{
		Temporary.CorrectCount++;
		Math_Display(1);
	}
	else
	{
		Temporary.WrongCount++;
		Math_Display(2);
	}
}

void Math_SubtractionDisplay()
{
	std::string CorrectNumber = std::to_string(Temporary.CorrectCount);
	std::string InCorrectNumber = std::to_string(Temporary.WrongCount);
	char* CorrectScore = "Correct: ";
	char* WrongScore = "Incorrect: ";

	if (Temporary.DeviceContext)
	{
		TextOut(Temporary.DeviceContext, 140, 190, " - ", 3);
		TextOut(Temporary.DeviceContext, 220, 190, "=", 1);

		TextOut(Temporary.DeviceContext, 29, 243, CorrectScore, 9);
		TextOut(Temporary.DeviceContext, 29, 263, WrongScore, 11);
		TextOut(Temporary.DeviceContext, 94, 243, CorrectNumber.c_str(),
			CorrectNumber.length());
		TextOut(Temporary.DeviceContext, 94, 263, InCorrectNumber.c_str(),
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
	Math_IntToChar(NewA, BufferA);
	Math_IntToChar(NewB, BufferB);
	SendMessageW(Temporary.EditA,
		WM_SETTEXT, 0, (LPARAM)BufferA);
	SendMessageW(Temporary.EditB,
		WM_SETTEXT, 0, (LPARAM)BufferB);

	SendMessageW(Temporary.EditC, WM_SETTEXT, 0,
		(LPARAM)"");
}

void Math_SubtractionTest()
{
	const unsigned int BufferSize = 16;
	char BufferA[BufferSize] = {};
	char BufferB[BufferSize] = {};
	char BufferC[BufferSize] = {};
	GetWindowText(Temporary.EditA, BufferA, BufferSize);
	int A = atoi(BufferA);
	GetWindowText(Temporary.EditB, BufferB, BufferSize);
	int B = atoi(BufferB);
	GetWindowText(Temporary.EditC, BufferC, BufferSize);
	int UserC = atoi(BufferC);

	int C = A - B;

	if (C == UserC)
	{
		Temporary.CorrectCount++;
		Math_Display(1);
	}
	else
	{
		Temporary.WrongCount++;
		Math_Display(2);
	}
}

void Math_MultiplicationDisplay()
{
	std::string CorrectNumber = std::to_string(Temporary.CorrectCount);
	std::string InCorrectNumber = std::to_string(Temporary.WrongCount);
	char* CorrectScore = "Correct: ";
	char* WrongScore = "Incorrect: ";

	if (Temporary.DeviceContext)
	{
		TextOut(Temporary.DeviceContext, 140, 190, "x  ", 3);
		TextOut(Temporary.DeviceContext, 220, 190, "=", 1);

		TextOut(Temporary.DeviceContext, 29, 243, CorrectScore, 9);
		TextOut(Temporary.DeviceContext, 29, 263, WrongScore, 11);
		TextOut(Temporary.DeviceContext, 94, 243, CorrectNumber.c_str(),
			CorrectNumber.length());
		TextOut(Temporary.DeviceContext, 94, 263, InCorrectNumber.c_str(),
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
	Math_IntToChar(NewA, BufferA);
	Math_IntToChar(NewB, BufferB);
	SendMessageW(Temporary.EditA,
		WM_SETTEXT, 0, (LPARAM)BufferA);
	SendMessageW(Temporary.EditB,
		WM_SETTEXT, 0, (LPARAM)BufferB);

	SendMessageW(Temporary.EditC, WM_SETTEXT, 0,
		(LPARAM)"");
}

void Math_MultiplicationTest()
{
	const unsigned int BufferSize = 16;
	char BufferA[BufferSize] = {};
	char BufferB[BufferSize] = {};
	char BufferC[BufferSize] = {};
	GetWindowText(Temporary.EditA, BufferA, BufferSize);
	int A = atoi(BufferA);
	GetWindowText(Temporary.EditB, BufferB, BufferSize);
	int B = atoi(BufferB);
	GetWindowText(Temporary.EditC, BufferC, BufferSize);
	int UserC = atoi(BufferC);

	int C = A * B;

	if (C == UserC)
	{
		Temporary.CorrectCount++;
		Math_Display(1);
	}
	else
	{
		Temporary.WrongCount++;
		Math_Display(2);
	}
}

void Math_DivisonDisplay()
{
	std::string CorrectNumber = std::to_string(Temporary.CorrectCount);
	std::string InCorrectNumber = std::to_string(Temporary.WrongCount);
	char* CorrectScore = "Correct: ";
	char* WrongScore = "Incorrect: ";

	if (Temporary.DeviceContext)
	{
		TextOut(Temporary.DeviceContext, 140, 190, "%", 1);
		TextOut(Temporary.DeviceContext, 220, 190, "=", 1);

		TextOut(Temporary.DeviceContext, 29, 243, CorrectScore, 9);
		TextOut(Temporary.DeviceContext, 29, 263, WrongScore, 11);
		TextOut(Temporary.DeviceContext, 94, 243, CorrectNumber.c_str(),
			CorrectNumber.length());
		TextOut(Temporary.DeviceContext, 94, 263, InCorrectNumber.c_str(),
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
	Math_IntToChar(NewA, BufferA);
	Math_IntToChar(NewB, BufferB);
	SendMessageW(Temporary.EditA,
		WM_SETTEXT, 0, (LPARAM)BufferA);
	SendMessageW(Temporary.EditB,
		WM_SETTEXT, 0, (LPARAM)BufferB);

	SendMessageW(Temporary.EditC, WM_SETTEXT, 0,
		(LPARAM)"");
}

void Math_DivisionTest()
{
	const unsigned int BufferSize = 16;
	char BufferA[BufferSize] = {};
	char BufferB[BufferSize] = {};
	char BufferC[BufferSize] = {};
	GetWindowText(Temporary.EditA, BufferA, BufferSize);
	int A = atoi(BufferA);
	GetWindowText(Temporary.EditB, BufferB, BufferSize);
	int B = atoi(BufferB);
	GetWindowText(Temporary.EditC, BufferC, BufferSize);
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
		Temporary.CorrectCount++;
		Math_Display(1);
	}
	else
	{
		Temporary.WrongCount++;
		Math_Display(2);
	}
}

void Math_Display(unsigned int SolutionState)
{
	if (SolutionState != 2)
	{
		Temporary.ProblemState = ((unsigned int)rand() % 4);
	}

	switch (Temporary.ProblemState)
	{
	case 0:
	{
		if (SolutionState == 2)
		{
			SendMessageW(Temporary.EditC, WM_SETTEXT, 0,
				(LPARAM)"");
		
			std::string InCorrectNumber = std::to_string(Temporary.WrongCount);
			TextOut(Temporary.DeviceContext, 94, 263, InCorrectNumber.c_str(),
				InCorrectNumber.length());
		}
		else
		{
			Math_AdditionDisplay();
		}
	} break;
	case 1:
	{
		if (SolutionState == 2)
		{
			SendMessageW(Temporary.EditC, WM_SETTEXT, 0,
				(LPARAM)"");

			std::string InCorrectNumber = std::to_string(Temporary.WrongCount);
			TextOut(Temporary.DeviceContext, 94, 263, InCorrectNumber.c_str(),
				InCorrectNumber.length());
		}
		else
		{
			Math_SubtractionDisplay();
		}
	} break;
	case 2:
	{
		if (SolutionState == 2)
		{
			SendMessageW(Temporary.EditC, WM_SETTEXT, 0,
				(LPARAM)"");
		
			std::string InCorrectNumber = std::to_string(Temporary.WrongCount);
			TextOut(Temporary.DeviceContext, 94, 263, InCorrectNumber.c_str(),
				InCorrectNumber.length());
		}
		else
		{
			Math_MultiplicationDisplay();
		}
	} break;
	case 3:
	{
		if (SolutionState == 2)
		{
			SendMessageW(Temporary.EditC, WM_SETTEXT, 0,
				(LPARAM)"");
		
			std::string InCorrectNumber = std::to_string(Temporary.WrongCount);
			TextOut(Temporary.DeviceContext, 94, 263, InCorrectNumber.c_str(),
				InCorrectNumber.length());
		}
		else
		{
			Math_DivisonDisplay();
		}
	} break;
	default: break;
	}
}

void Math_CheckAnswer(unsigned short Command)
{
	if (Command == 103)
	{
		switch (Temporary.ProblemState)
		{
		case 0:
		{
			Math_AdditionTest();
		} break;
		case 1:
		{
			Math_SubtractionTest();
		} break;
		case 2:
		{
			Math_MultiplicationTest();
		} break;
		case 3:
		{
			Math_DivisionTest();
		} break;
		default: break;
		}

	} 
}

void Math_IntToChar(int Number, unsigned short* CharBuffer)
{
	unsigned short Buffer[16] = {};
	unsigned int Index = 0;
	unsigned int Length = 0;

	if (Number != 0)
	{
		while (Number > 0)
		{
			char Hold = (Number % 10) + 48;
			Number = Number / 10;
			Buffer[Index] = Hold;
			Length++;
			Index++;
		}
	}
	else
	{
		Buffer[Index] = 48;
	}

	Index = 0;
	if (Length > 1)
	{
		for (int i = Length - 1; i >= 0; i--)
		{
			CharBuffer[Index] = Buffer[i];
			Index++;
		}
	}
	else
	{
		CharBuffer[0] = Buffer[0];
	}
}


void Math_CleanUp()
{
	if (Temporary.CheckButton)
	{
		DestroyWindow(Temporary.CheckButton);
		Temporary.CheckButton = 0;
	}
	if (Temporary.EditA)
	{
		DestroyWindow(Temporary.EditA);
		Temporary.EditA = 0;
	}
	if (Temporary.EditB)
	{
		DestroyWindow(Temporary.EditB);
		Temporary.EditB = 0;
	}
	if (Temporary.EditC)
	{
		DestroyWindow(Temporary.EditC);
		Temporary.EditC = 0;
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