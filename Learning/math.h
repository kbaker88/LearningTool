#ifndef MATH_H
#define MATH_H

#include <Windows.h>
#include <string>
#include <fstream>

#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

struct MathState
{
	MathState() : Window(0), EditA(0), EditB(0), EditC(0),
	CheckButton(0), DeviceContext(0), CorrectCount(0),
	WrongCount(0), ProblemState(0), SolutionState(0) {}

	HWND Window, EditA, EditB, EditC, CheckButton;
	HDC DeviceContext;
	unsigned int CorrectCount, WrongCount, ProblemState, SolutionState;
};

void Math_Initialize(HWND Window);
void Math_Loop();

void Math_AdditionDisplay();
void Math_AdditionTest();
void Math_SubtractionDisplay();
void Math_SubtractionTest();
void Math_MultiplicationDisplay();
void Math_MultiplicationTest();
void Math_DivisonDisplay();
void Math_DivisionTest();

void Math_Display(unsigned int SolutionState);

void Math_CheckAnswer(unsigned short Command);
//TODO: Put in Buffer length checks for robustness
void Math_IntToChar(int Number, unsigned short* CharBuffer);
void Math_CleanUp();

#endif