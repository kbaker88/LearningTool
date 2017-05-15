#ifndef MATH_H
#define MATH_H

#include "utility.h"

class MathState
{
public:
	MathState() : Window(0), DeviceContext(0), CorrectCount(0),
	WrongCount(0), ProblemState(0), SolutionState(0),
	A(0), B(0), Save(0), EditDivA(0), EditDivB(0), EditDivC(0),
	Instance(0) {}

	void Initialize(HWND window, State *SaveState);
	void Loop();
	void UpdateStates(unsigned short Command);
	void Display();
	void Display_Addition();
	void Display_Subtraction();
	void Display_Multiplication();
	void Display_Division();
	void InitEditGroupOne();
	void CheckAnswer();
	void CleanUp();

private:
	State* Save;
	NewWindow ScratchWindow;
	Button Check, ScratchPad, CleanScratch;
	TextWindow TextA, TextB, TextC;
	TextWindow ScratchMatrix[5][5];
	HWND Window;
	HWND EditDivA, EditDivB, EditDivC;
	HINSTANCE Instance;

	HDC DeviceContext;
	unsigned int CorrectCount, WrongCount, ProblemState, 
		SolutionState, A, B;
};
#endif