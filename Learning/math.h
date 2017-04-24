#ifndef MATH_H
#define MATH_H

#include "utility.h"

class MathState
{
public:
	MathState() : Window(0), EditA(0), EditB(0), EditC(0),
	CheckButton(0), DeviceContext(0), CorrectCount(0),
	WrongCount(0), ProblemState(0), SolutionState(0),
	A(0), B(0), Save(0) {}

	void Initialize(HWND window, State *SaveState);
	void Loop();
	void Commands(unsigned short Command);
	void Display(unsigned int SolutionState);
	void CheckAnswer();
	void CleanUp();

private:
	State* Save;
	HWND Window, EditA, EditB, EditC, CheckButton;
	HDC DeviceContext;
	unsigned int CorrectCount, WrongCount, ProblemState, 
		SolutionState, A, B;
};
#endif