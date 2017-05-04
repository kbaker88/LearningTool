#include "button.h"

Button::Button()
{

}

Button::~Button()
{

}

unsigned char Button::Initialize(char* ToName, HMENU SetID,
	int SetWidth, int SetHeight, int XPos,
	int YPos, HWND ToWindow)
{
	if (!Window)
	{
		Width = SetWidth;
		Height = SetHeight;
		XPosition = XPos;
		YPosition = YPos;
		ID = SetID;
		BelongsToWindow = ToWindow;

		Window = CreateWindow("BUTTON", ToName,
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
			XPosition, YPosition, Width, Height, BelongsToWindow, ID,
			(HINSTANCE)GetWindowLong(BelongsToWindow, GWL_HINSTANCE),
			NULL);

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

void Button::UpdateState(WPARAM Command)
{
	if (Command == (WPARAM)ID)
	{
		State = 1;
	}
}

unsigned char Button::GetState()
{
	unsigned char Result = State;
	if (State)
	{
		State = 0;
	}
	return Result;
}

void Button::Clean()
{
	if (Window)
	{
		DestroyWindow(Window);
		Window = 0;
	}
}