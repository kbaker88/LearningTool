#ifndef NEWWINDOW_H
#define NEWWINDOW_H

#include <Windows.h>

//void Window_UpdateStates(NewWindow* Window);

class NewWindow
{
public:
	NewWindow();
	~NewWindow();

	unsigned char Initialize( int SetWidth, int SetHeight,
		int XPos, int YPos, HWND ToWindow, HINSTANCE Instance);

	unsigned char GetState();
	void SetCommand(WPARAM wParam);
	void ClearCommand();
	void Clean();

	HWND Window, BelongsToWindow;
	WPARAM Command;
private:
	int Width, Height, XPosition, YPosition;
	unsigned char State;
};

#endif