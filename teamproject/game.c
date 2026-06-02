//게임의 전체 흐름을 관리, game.c

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <Windows.h>
#include <time.h>
#include "output.h"
#include "input.h"
#include "map.h"
#include "game.h"

extern char map[MAPSIZE][MAPSIZE + 1];

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
	scanf("%d", &level); // 난이도 선택 방향키로 받는 걸로 수정해야 함

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
		system("cls");
		if (input == 27) // ESC 키 누르면 메뉴 나오게.
			break;
		player_movement(input);
		render_map();
		//깃발 전부 사라지면 다음 스토리 나오고 다음 난이도로.
	}
}