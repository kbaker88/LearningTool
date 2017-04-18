#ifndef MATH_H
#define MATH_H

#include "utility.h"

class MathState
{
public:
	MathState() : Window(0), EditA(0), EditB(0), EditC(0),
	CheckButton(0), DeviceContext(0), CorrectCount(0),
	WrongCount(0), ProblemState(0), SolutionState(0) {}

	void Initialize(HWND Window);
	void Loop();
	void AdditionDisplay();
	void AdditionTest();
	void SubtractionDisplay();
	void SubtractionTest();
	void MultiplicationDisplay();
	void MultiplicationTest();
	void DivisonDisplay();
	void DivisionTest();
	void Display(unsigned int SolutionState);
	void CheckAnswer(unsigned short Command);
	void CleanUp();

private:
	HWND Window, EditA, EditB, EditC, CheckButton;
	HDC DeviceContext;
	unsigned int CorrectCount, WrongCount, ProblemState, SolutionState;
};
#endif