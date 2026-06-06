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
extern int playerLocation[2];
static int level;
const int moveNum[3] = { 10, 20, 30 };
static int moveCount;
static int isDie;
static int canMove = 1;
static int laserNum = 0;
char eventMessage[200] = "";

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

	for (int i = 0; i < MAXLASER; i++)
	{
		lasers[i].active = 0;
		lasers[i].line = 0;
		lasers[i].isVertical = 0;
		lasers[i].countdown = 0;
	}

	laserNum = 0;

	generate_flags(level);
	moveCount = moveNum[level];
	generate_enemy(level);
	place_all_enemy();
}

void show_game()
{
	system("cls");

	init_map();
	place_flags();
	place_all_enemy();
	place_laser();
	locate_player();

	render_map();

	printf("\n%s", eventMessage);
	print_moveCount(&moveCount);
	print_item();
}

int get_flag_hint()
{
	int pos = get_flag_relative_position();

	switch (pos)
	{
	case 1:
		strcpy_s(eventMessage, sizeof(eventMessage), "힌트: 깃발은 오른쪽 위에 있습니다.");
		break;
	case 2:
		strcpy_s(eventMessage, sizeof(eventMessage), "힌트: 깃발은 왼쪽 위에 있습니다.");
		break;
	case 3:
		strcpy_s(eventMessage, sizeof(eventMessage), "힌트: 깃발은 왼쪽 아래에 있습니다.");
		break;
	case 4:
		strcpy_s(eventMessage, sizeof(eventMessage), "힌트: 깃발은 오른쪽 아래에 있습니다.");
		break;
	case 5:
		strcpy_s(eventMessage, sizeof(eventMessage), "힌트: 깃발은 위쪽에 있습니다.");
		break;
	case 6:
		strcpy_s(eventMessage, sizeof(eventMessage), "힌트: 깃발은 아래쪽에 있습니다.");
		break;
	case 7:
		strcpy_s(eventMessage, sizeof(eventMessage), "힌트: 깃발은 왼쪽에 있습니다.");
		break;
	case 8:
		strcpy_s(eventMessage, sizeof(eventMessage), "힌트: 깃발은 오른쪽에 있습니다.");
		break;
	}
}

void check_event(int tileInfo)
{
	int temp;
	if (tileInfo == -1) // 보호막 추가해서 그 변수가 있으면 1 줄이고 break 하기
	{
		isDie = 1; 
		return;
	}

	//tileInfo id의 깃발의 효과 적용
	if (tileInfo > 1)
	{
		switch (flags[tileInfo].effect)
		{
		case 0: //시간 정지 아이템 획득
			itemNum[0]++;
			strcpy_s(eventMessage, sizeof(eventMessage), "시간 정지 획득");
			break;
		case 1: 
			itemNum[1]++; // 대시 아이템 획득
			strcpy_s(eventMessage, sizeof(eventMessage), "대시 획득");
			break;
		case 2: // 보호막 획득
			itemNum[2]++;
			strcpy_s(eventMessage, sizeof(eventMessage), "보호막 획득");
			break;
		case 3: //턴 수 +
			moveCount += 5;
			strcpy_s(eventMessage, sizeof(eventMessage), "이동가능 횟수 5회 증가");
			break;
		case 4: //목표지점 힌트
			get_flag_hint();
			break;
		case 5://적 추가
			generate_one_enemy(find_empty_enemy_slot);
			strcpy_s(eventMessage, sizeof(eventMessage), "적 추가 등장");
			break;
		case 6://이동 횟수 감소
			moveCount += 3;
			strcpy_s(eventMessage, sizeof(eventMessage), "이동가능 횟수 3회 감소");
			break;
		case 7://시야 감소
			break;
		case 8://레이저 추가
			generate_laser(&laserNum, 1);
			strcpy_s(eventMessage, sizeof(eventMessage), "레이저 추가 등장");
			break;
		case 9://아이템 사라짐
			temp = rand() & 3;
			itemNum[temp]--;
			switch (temp)
			{
			case 0:
				strcpy_s(eventMessage, sizeof(eventMessage), "시간 정지 파손");
				break;
			case 1:
				strcpy_s(eventMessage, sizeof(eventMessage), "대시 파손");
				break;
			case 2:
				strcpy_s(eventMessage, sizeof(eventMessage), "보호막 파손");
				break;
			}
			break;
		}

		flags[tileInfo - 1].effect = 0;
		flags[tileInfo - 1].id = 0;
		flags[tileInfo - 1].x = 0;
		flags[tileInfo - 1].y = 0;
	}
}

void spawn_laser(int* laserNum, int canLaunch)
{
	if (!canLaunch || (*laserNum) >= maxLaserPerLevel[level])
		return;

	int randNum = rand() % 100;

	if (randNum < LASERCHANCE)
	{
		generate_laser(laserNum, 0);
	}
}

void process_laser(int* laserNum, int canLaunch)
{
	if (!canLaunch)
		return;

	int i;

	for (i = 0; i < MAXLASER; i++)
	{
		if (!lasers[i].active)
			continue;

		if (lasers[i].countdown == LASER)
		{
			init_laser(i, laserNum);
			continue;
		}

		lasers[i].countdown--;

		if (lasers[i].countdown == 0)
		{
			lasers[i].countdown = LASER;

			if (lasers[i].isVertical == 0)
			{
				if (playerLocation[1] == lasers[i].line)
				{
					isDie = 1;
				}
			}
			else
			{
				if (playerLocation[0] == lasers[i].line)
				{
					isDie = 1;
				}
			}
		}
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

		place_laser();
		enemy_movement(canMove);
		tileInfo = player_movement(input, & moveCount);

		process_laser(&laserNum, canMove);
		spawn_laser(&laserNum, canMove);

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