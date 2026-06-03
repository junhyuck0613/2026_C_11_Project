//게임의 전체 흐름을 관리, game.c

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <Windows.h>
#include <time.h>
#include <stdlib.h>
#include "output.h"
#include "input.h"
#include "map.h"
#include "game.h"

extern char map[MAPSIZE][MAPSIZE + 1];
static int level;

void init_game()
{
	SetConsoleOutputCP(CP_UTF8);
	srand((unsigned int)time(NULL));

	init_map();
	locate_player();
}

void start_menu()
{
	level = show_start_menu();

	if (level == 3)
		exit(0);

	set_difficulty(level);
}

void set_difficulty()
{
	place_flags(level);
}

void game_loop()
{
	while (1)
	{
		int input = get_input();
		system("cls");
		if (input == 27) // ESC 키 누르면 메뉴 나오게.
		{
			int temp = show_menu();
			if (temp == 0)
			{
				start_menu();
				render_map();
				continue;
			}
			if (temp == 1)
			{
				break;
			}
				
		}
		player_movement(input);
		render_map();
		//깃발 전부 사라지면 다음 스토리 나오고 다음 난이도로.
	}
}