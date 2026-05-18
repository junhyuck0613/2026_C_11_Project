//입력 관련, input.c

#include <stdio.h>
#include <conio.h>
#include <string.h>

int get_input();

static char input;
static char moveKey[5] = { 'w', 'a', 's', 'd' };
static char itemKey[10] = {0};

int get_input()
{
	int i;

	input = _getch();

	for (i = 0; i < strlen(moveKey);i++)
	{
		if (input == moveKey[i])
			return 1;
	}

	for (i = 0; i < strlen(itemKey);i++)
	{
		if (input == itemKey[i])
			return 2;
	}

	return 0;
}