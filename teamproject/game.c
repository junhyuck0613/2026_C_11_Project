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
static int moveNum[3] = { 10, 20, 30 };
static int moveCount;

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
	show_game_menu();
}

void set_difficulty()
{
	place_flags(level);
	moveCount = moveNum[level];
}

void show_game_menu()
{
	system("cls");
	render_map();
	print_moveCount(&moveCount);
}

void game_loop()
{
	int isDie = 0;
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
				continue;
			}
			if (temp == 1)
			{
				exit(0);
			}
				
		}

		player_movement(input, & moveCount);
		show_game_menu();

		if (isDie != 0 || moveCount == 0)
		{
			Sleep(300);
			show_game_over();
			start_menu();
		}
		//깃발 전부 사라지면 다음 스토리 나오고 다음 난이도로.
	}
} 