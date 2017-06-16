#ifndef LANGUAGE_H
#define LANGUAGE_H

#include "math.h"
//TODO: Free Registered windows classes later

struct WordUnit
{
	WordUnit() : EnglishLength(0), RussianLength(0) {}

	unsigned short English[512] = {};
	unsigned short Russian[512] = {};
	unsigned int EnglishLength;
	unsigned int RussianLength;
};

class LanguageState
{
public:
	LanguageState() : Window(0), CorrectCount(0), 
		WrongCount(0), TotalWordCount(0), 
		CurrentWordChoice(0), DeviceContext(0), 
		DictionaryWindow(0), DictionaryList(0), 
		Instance(0), Save(0) {}

	~LanguageState() {}

	void Initialize(HWND window, State* SaveState);
	bool LoadDatabase(char* FileName);
	void Loop();
	void Display();
	void DisplayDictionary();
	void UpdateStates(WPARAM Command);
	bool ChangeBackground();
	void CleanUp();

private:
	WordUnit Words[256];
	Button Check, Dictionary;
	TextWindow InputWindow, OutputWindow;
	HWND Window, DictionaryWindow, DictionaryList;
	HDC DeviceContext;
	HINSTANCE Instance;
	State* Save;
	unsigned int CorrectCount, WrongCount, TotalWordCount,
		CurrentWordChoice;
};

#endif
