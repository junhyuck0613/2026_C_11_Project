//기본적인 진행만, 함수 호출과 루프로만, main.c

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <Windows.h>
#include <time.h>
#include "output.h"
#include "input.h"
#include "map.h"

int main()
{
	int level = 0;

	SetConsoleOutputCP(CP_UTF8);
	srand((unsigned int)time(NULL));

	init_map();
	locate_player();

	show_start_menu();
	
	scanf("%d", &level);

	place_flags(level - 1);

	render_map();

	return 0;
}