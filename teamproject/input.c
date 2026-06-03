//입력 관련, input.c

#include <stdio.h>
#include <conio.h>
#include "input.h"

int get_input()
{

	int input = _getch();

	if (input == 224 || input == 0)
	{
		input = _getch();

		return input;
	}

	return input;
}