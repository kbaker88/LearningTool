#include "text_window.h"

TextWindow::TextWindow()
{

}

TextWindow::~TextWindow()
{

}

unsigned char TextWindow::Initialize(HMENU SetID, int SetWidth,
	int SetHeight, int XPos, int YPos, HWND ToWindow, unsigned int Style)
{
	if (!Window)
	{
		Width = SetWidth;
		Height = SetHeight;
		XPosition = XPos;
		YPosition = YPos;
		ID = SetID;
		BelongsToWindow = ToWindow;

		Window = CreateWindowExW(
			0, L"EDIT", NULL, Style,
			XPosition, YPosition, Width, Height, BelongsToWindow,
			SetID, (HINSTANCE)GetWindowLong(BelongsToWindow,
				GWL_HINSTANCE), NULL);

		if (!Window)
		{
			// NOTE: Error creating window.
			return 1;
		}
		return 0;
	}
	else
	{
		// NOTE: Window already exists.
		return 2;
	}
}

void TextWindow::UpdateState(WPARAM Command)
{

}

unsigned char TextWindow::GetState()
{
	unsigned char Result = State;
	if (State)
	{
		State = 0;
	}
	return Result;
}

void TextWindow::Clean()
{
	if (Window)
	{
		DestroyWindow(Window);
		Window = 0;
	}
}