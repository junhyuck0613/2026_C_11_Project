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
#include "util.h"
#include "enemy.h"

extern char map[MAPSIZE][MAPSIZE];
extern int playerLocation[2];  // 플레이어 위치 접근용
static int level;
const int moveNum[3] = { 10, 20, 30 };
static int moveCount;
static int isDie;
static int canMove = 1;

void init_game()
{
	SetConsoleOutputCP(CP_UTF8);
	srand((unsigned int)time(NULL));

	init_map();
	locate_player();
}

void start_menu()
{
	isDie = 0;  // 게임 시작 전 초기화
	level = show_start_menu();

	if (level == 3)
		exit(0);

	set_difficulty(level);
	locate_player();
	show_game();
}

void set_difficulty()
{
	reset_player_location();
	init_map();
	place_flags(level);
	moveCount = moveNum[level];
	generate_enemy(level);
	place_all_enemy(level);
}

void show_game()
{
	system("cls");
	render_map();
	print_moveCount(&moveCount);
	print_item();
}

void check_event(int tileInfo)
{
	switch (tileInfo)
	{
	case -1:
		isDie = 1;
	case 0:
		break;
		//이 아래에 쭉 아이템, 벌칙 추가하기
	}
}

void game_loop()
{
	int tileInfo;
	while (1)
	{
		int input = get_input();
		int prevX = playerLocation[0];
		int prevY = playerLocation[1];
		system("cls");
		if (input == 27)
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

		enemy_movement(level, canMove);
		tileInfo = player_movement(input, & moveCount);

		// tileInfo가 -1이거나 적과의 충돌이 있으면 게임오버
		if (tileInfo == -1 || check_enemy_collision(prevX, prevY, playerLocation[0], playerLocation[1]))
		{
			isDie = 1;
		}
		else
		{
			check_event(tileInfo);
		}
		show_game();

		if (isDie != 0 || moveCount == 0)
		{
			Sleep(500);
			show_game_over();
			start_menu();
		}
	}
}