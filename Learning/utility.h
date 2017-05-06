#ifndef UTILITY_H
#define UTILITY_H

#include "new_window.h"
#include "text_window.h"
#include "button.h"
#include <string>
#include <fstream>

#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

#include "state_system.h"

//TODO: Put in CharBuffer length checks for robustness
static void Utility_IntToChar(int Number, unsigned short* CharBuffer)
{
	unsigned short Buffer[16] = {};
	unsigned int Index = 0;
	unsigned int Length = 0;

	if (Number != 0)
	{
		while (Number > 0)
		{
			char Hold = (Number % 10) + 48;
			Number = Number / 10;
			Buffer[Index] = Hold;
			Length++;
			Index++;
		}
	}
	else
	{
		Buffer[Index] = 48;
	}

	Index = 0;
	if (Length > 1)
	{
		for (int i = Length - 1; i >= 0; i--)
		{
			if (Buffer[Index])
			{
				CharBuffer[Index] = Buffer[i];
				Index++;
			}
			else
			{
				// TODO: Error
				CharBuffer = 0;
			}
		}
	}
	else
	{
		if (Buffer[Index])
		{
			CharBuffer[0] = Buffer[0];
		}
		else
		{
			// TODO: Error
			CharBuffer =  0;
		}
	}
}

static bool Utility_CompareCharString(unsigned short* StringA, 
	unsigned short* StringB)
{
	if (StringA && StringB)
	{
		while (*StringA != '\0')
		{
			if (*StringB == '\0')
			{
				return 0;
			}
			if (*StringA != *StringB)
			{
				return 0;
			}
			StringB++;
			StringA++;
		}
		if (*StringB != '\0')
		{
			return 0;
		}
		return 1;
	}

	return 0;
}

static bool Utility_CompareCharString(char* StringA, 
	char* StringB)
{
	if (StringA && StringB)
	{
		while (*StringA != '\0')
		{
			if (*StringB == '\0')
			{
				return 0;
			}
			if (*StringA != *StringB)
			{
				return 0;
			}
			StringB++;
			StringA++;
		}
		if (*StringB != '\0')
		{
			return 0;
		}
		return 1;
	}

	return 0;
}

#endif