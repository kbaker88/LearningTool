#ifndef TEXT_WINDOW_H
#define TEXT_WINDOW_H

#include <Windows.h>

class TextWindow
{
public:
	TextWindow();
	~TextWindow();

	unsigned char Initialize(HMENU SetID, int SetWidth,
		int SetHeight, int XPos, int YPos, HWND ToWindow,
		unsigned int Style);
	void UpdateState(WPARAM Command);
	unsigned char GetState();
	void Clean();

	HWND Window;

private:
	HWND BelongsToWindow;
	HMENU ID;
	int Width, Height, XPosition, YPosition;
	unsigned char State;
	char* Name;
};

#endif
