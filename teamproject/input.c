//입력 관련, input.c

#include <stdio.h>
#include <conio.h>
#include "input.h"

static int moveKey[4] = { 72, 75, 80, 77 }; // 상 좌 하 우
static char itemKey[10] = { 0 };

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