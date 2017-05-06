#ifndef NEWWINDOW_H
#define NEWWINDOW_H

#include <Windows.h>

class NewWindow
{
public:
	NewWindow();
	~NewWindow();

	unsigned char Initialize( int SetWidth, int SetHeight,
		int XPos, int YPos, HWND ToWindow, HINSTANCE Instance);

	void Clean();

private:
	HWND Window, BelongsToWindow;
	int Width, Height, XPosition, YPosition;
	unsigned char State;
};

#endif