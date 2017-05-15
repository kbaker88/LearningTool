#ifndef BUTTON_H
#define BUTTON_H

#include <Windows.h>

class Button
{
public:
	Button();
	~Button();

	unsigned char Initialize(char* ToName, HMENU SetID,
		int SetWidth, int SetHeight, 
		int XPos, int YPos, HWND ToWindow);
	void UpdateState(WPARAM Command);
	unsigned char GetState();
	void Clean();

	HWND Window, BelongsToWindow;
	HMENU ID;
private:
	int Width, Height;
	int XPosition, YPosition;
	unsigned char State;
	char* Name;
};

#endif