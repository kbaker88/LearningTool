#ifndef LANGUAGE_H
#define LANGUAGE_H

#include "math.h"

//TODO: Free Registered windows classes later

struct WordUnit
{
	WordUnit() : EnglishLength(0), RussianLength(0) {}

	unsigned short English[64] = {};
	unsigned short Russian[64] = {};
	unsigned int EnglishLength;
	unsigned int RussianLength;
};

class LanguageState
{
public:
	LanguageState() : Window(0), EditWindowOutput(0), EditWindowInput(0),
		CheckButton(0), CorrectCount(0), WrongCount(0), TotalWordCount(0),
		CurrentWordChoice(0), DeviceContext(0), DictionaryButton(0),
		Dictionary(0), DictionaryList(0), Instance(0) {}

	~LanguageState() {}

	void Initialize(HWND Window);
	bool LoadDatabase(char* FileName);
	void Loop();
	void Display();
	void DisplayDictionary();
	bool CompareStrings();
	void CheckClickStates(unsigned short Command);
	bool ChangeBackground();
	void CleanUp();

private:
	WordUnit Words[256];
	HWND Window, EditWindowOutput, EditWindowInput,
		CheckButton, DictionaryButton, Dictionary, DictionaryList;
	HDC DeviceContext;
	HINSTANCE Instance;
	unsigned int CorrectCount, WrongCount, TotalWordCount,
		CurrentWordChoice;
};

#endif
