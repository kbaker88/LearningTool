#ifndef LANGUAGE_H
#define LANGUAGE_H

#include "math.h"

struct WordUnit
{
	WordUnit() : EnglishLength(0), RussianLength(0) {}

	unsigned short English[64] = {};
	unsigned short Russian[64] = {};
	unsigned int EnglishLength;
	unsigned int RussianLength;
};

struct LanguageState
{
	LanguageState() : Window(0), EditWindowOutput(0), EditWindowInput(0),
		CheckButton(0), CorrectCount(0), WrongCount(0), TotalWordCount(0),
		CurrentWordChoice(0), DeviceContext(0), DictionaryButton(0),
		Dictionary(0) {}

	WordUnit Words[256];
	HWND Window, EditWindowOutput, EditWindowInput,
		CheckButton, DictionaryButton, Dictionary;
	HDC DeviceContext;
	unsigned int CorrectCount, WrongCount, TotalWordCount,
		CurrentWordChoice;
};

void Language_Initialize(HWND Window);
bool Language_LoadDatabase(char* FileName);
void Language_Loop();
void Language_Display();
void Language_DisplayDictionary();
bool Language_CompareStrings();

void Language_CheckClickStates(unsigned short Command);
bool Language_ChangeBackground();
void Language_CleanUp();

#endif
