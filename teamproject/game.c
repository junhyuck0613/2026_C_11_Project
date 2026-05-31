//게임의 전체 흐름을 관리, game.c

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <Windows.h>
#include <time.h>
#include "output.h"
#include "input.h"
#include "map.h"
#include "game.h"

void init_game()
{
	SetConsoleOutputCP(CP_UTF8);
	srand((unsigned int)time(NULL));

	init_map();
	locate_player();
}

void start_menu()
{
	int level;
	show_start_menu();
	scanf("%d", &level);

	set_difficulty(level);
}

void set_difficulty(int level)
{
	place_flags(level - 1);
}

void game_loop()
{
	while (1)
	{
		int input = get_input();
		if (input == 27) // ESC 키
			break;
		player_movement(input);
		render_map();
	}
}