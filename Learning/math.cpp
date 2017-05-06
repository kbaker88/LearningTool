#include "math.h"

#define C_WIDTH 100
#define C_HEIGHT 30

void 
MathState::Initialize(HWND window, State *SaveState)
{
	Instance = (HINSTANCE)GetWindowLong(Window, GWL_HINSTANCE);

	Save = SaveState;
	SaveState->ActiveModule = 2;
	Window = window;
	DeviceContext = GetWindowDC(Window);

	TextA.Initialize((HMENU)112, 50, C_HEIGHT, 70, 150, Window, 0x50400800);
	TextB.Initialize((HMENU)113, 50, C_HEIGHT, 150, 150, Window, 0x50400800);
	TextC.Initialize((HMENU)114, C_WIDTH, C_HEIGHT, 230, 150, Window, 0x50400000);

	Check.Initialize("Check", (HMENU)103, 100, 40, 235, 210, Window);
	ScratchPad.Initialize("Scratch Pad", (HMENU)105, 100, 20, 460, 230, Window);

	if (Save->MathSet)
	{
		A = Save->Numbers[0];
		B = Save->Numbers[1];
		ProblemState = Save->Numbers[2];
		SolutionState = 3;
		Display();
	}
	else
	{
		SolutionState = 0;
		Display();
		Save->MathSet = true;
		Save->Numbers[0] = A;
		Save->Numbers[1] = B;
		Save->Numbers[2] = ProblemState;
	}
}

void 
MathState::Loop() 
{
	if (Check.GetState() == 1)
	{
		CheckAnswer();
	}

	if (ScratchPad.GetState() == 1)
	{
		RECT WindowRect = {};
		GetClientRect(Window, &WindowRect);
		MapWindowPoints(Window, GetParent(Window),
			(LPPOINT)&WindowRect, 2);

		ScratchWindow.Initialize(WindowRect.right - 8, 
			WindowRect.top - 33, 0, 0, Window, Instance);
	}
}

void 
MathState::Display()
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
			Display_Addition();
		} break;
		case 1:
		{
			Display_Subtraction();
		} break;
		case 2:
		{
			Display_Multiplication();
		} break;
		case 3:
		{
			Display_Division();
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
	SendMessageW(TextA.Window,
		WM_SETTEXT, 0, (LPARAM)BufferA);
	SendMessageW(TextB.Window,
		WM_SETTEXT, 0, (LPARAM)BufferB);

	SetWindowText(TextC.Window, "");

	SetFocus(TextC.Window);
}

void 
MathState::InitEditGroupOne()
{


}

void 
MathState::Display_Addition()
{
	TextA.Initialize((HMENU)112, 50, C_HEIGHT, 70, 150, Window, 0x50400800);
	TextB.Initialize((HMENU)113, 50, C_HEIGHT, 150, 150, Window, 0x50400800);
	TextC.Initialize((HMENU)114, C_WIDTH, C_HEIGHT, 230, 150, Window, 0x50400000);

	TextOut(DeviceContext, 140, 190, "+  ", 3);
	TextOut(DeviceContext, 220, 190, "=", 1);

	if ((SolutionState != 2) && (SolutionState != 3))
	{
		A = (rand() % 9999);
		B = (rand() % 9999);
	}
}

void 
MathState::Display_Subtraction()
{
	TextOut(DeviceContext, 140, 190, " - ", 3);
	TextOut(DeviceContext, 220, 190, "=", 1);

	if ((SolutionState != 2) && (SolutionState != 3))
	{
		A = (rand() % 9999);
		B = (rand() % 9999);
	}
}

void
MathState::Display_Multiplication()
{
	TextOut(DeviceContext, 140, 190, "x  ", 3);
	TextOut(DeviceContext, 220, 190, "=", 1);

	if ((SolutionState != 2) && (SolutionState != 3))
	{
		A = (rand() % 9999);
		B = (rand() % 10);
	}
}

void 
MathState::Display_Division()
{
	TextOut(DeviceContext, 140, 190, "%", 1);
	TextOut(DeviceContext, 220, 190, "=", 1);

	if ((SolutionState != 2) && (SolutionState != 3))
	{
		B = (rand() % 13);
		if (B == 0)
		{
			B = 1;
		}
		A = B * ((unsigned int)rand() % 13);
	}
}


void 
MathState::UpdateStates(unsigned short Command)
{
	Check.UpdateState(Command);
	ScratchPad.UpdateState(Command);
}

void
MathState::CheckAnswer()
{
	const unsigned int BufferSize = 16;
	char BufferA[BufferSize] = {};
	char BufferB[BufferSize] = {};
	char BufferC[BufferSize] = {};
	GetWindowText(TextA.Window, BufferA, BufferSize);
	A = atoi(BufferA);
	GetWindowText(TextB.Window, BufferB, BufferSize);
	B = atoi(BufferB);
	GetWindowText(TextC.Window, BufferC, BufferSize);
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
		SolutionState = 1;
		Display();
		Save->Numbers[0] = A;
		Save->Numbers[1] = B;
		Save->Numbers[2] = ProblemState;
	}
	else
	{
		WrongCount++;
		SolutionState = 2;
		Display();
	}
}

void
MathState::CleanUp()
{
	if (Save)
	{
		Save->MathSet = true;
		Save->Numbers[0] = A;
		Save->Numbers[1] = B;
		Save->Numbers[2] = ProblemState;
	}

	ScratchWindow.Clean();
	Check.Clean();
	ScratchPad.Clean();

	TextA.Clean();
	TextB.Clean();
	TextC.Clean();

	if (DeviceContext)
	{
		std::string ClearLine = "                       ";
		TextOut(DeviceContext, 29, 243, ClearLine.c_str(), 23);
		TextOut(DeviceContext, 29, 263, ClearLine.c_str(), 23);

		ReleaseDC(Window, DeviceContext);
		DeviceContext = 0;
	}
}