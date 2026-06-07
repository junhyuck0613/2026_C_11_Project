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
#include <conio.h>
#include <string.h>

extern char map[MAPSIZE][MAPSIZE];
extern int playerLocation[2];
static int level;
const int moveNum[3] = { 30, 20, 20 };
static int moveCount;
static int isDie;
static int canMove = 1;
static int timeStopTurn = 0;
static int laserNum = 0;
char eventMessage[200] = "";
int visionRange = MAPSIZE;
int visionTurn = 0;
static int dashReady = 0;

void init_game()
{
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

void get_flag_hint()
{
	int pos = get_flag_relative_position();

	switch (pos)
	{
	case 0:
		strcpy_s(eventMessage, sizeof(eventMessage), "힌트: 깃발은 오른쪽 위에 있습니다.");
		break;
	case 1:
		strcpy_s(eventMessage, sizeof(eventMessage), "힌트: 깃발은 왼쪽 위에 있습니다.");
		break;
	case 2:
		strcpy_s(eventMessage, sizeof(eventMessage), "힌트: 깃발은 왼쪽 아래에 있습니다.");
		break;
	case 3:
		strcpy_s(eventMessage, sizeof(eventMessage), "힌트: 깃발은 오른쪽 아래에 있습니다.");
		break;
	case 4:
		strcpy_s(eventMessage, sizeof(eventMessage), "힌트: 깃발은 위쪽에 있습니다.");
		break;
	case 5:
		strcpy_s(eventMessage, sizeof(eventMessage), "힌트: 깃발은 아래쪽에 있습니다.");
		break;
	case 6:
		strcpy_s(eventMessage, sizeof(eventMessage), "힌트: 깃발은 왼쪽에 있습니다.");
		break;
	case 7:
		strcpy_s(eventMessage, sizeof(eventMessage), "힌트: 깃발은 오른쪽에 있습니다.");
		break;
	default:
		strcpy_s(eventMessage, sizeof(eventMessage), "힌트: 깃발 위치를 알 수 없습니다.");
		break;
	}
}

void update_vision_effect()
{
	if (visionTurn > 0)
	{
		visionTurn--;

		if (visionTurn == 0)
		{
			visionRange = MAPSIZE;
		}
	}
}

void add_event_message(const char* message)
{
	if (message == NULL || message[0] == '\0')
		return;

	if (eventMessage[0] == '\0')
	{
		strcpy_s(eventMessage, sizeof(eventMessage), message);
	}
	else
	{
		strcat_s(eventMessage, sizeof(eventMessage), "\n");
		strcat_s(eventMessage, sizeof(eventMessage), message);
	}
}

void update_time_stop()
{
	char temp[100];

	if (timeStopTurn > 0)
	{
		timeStopTurn--;

		if (timeStopTurn > 0)
		{
			sprintf_s(temp, sizeof(temp),
				"시간 정지가 %d번 남았습니다.", timeStopTurn);
			add_event_message(temp);
		}
		else
		{
			canMove = 1;
			add_event_message("시간 정지가 끝났습니다.");
		}
	}
}

void check_event(int flagId)
{
	int temp, event;
	if (flagId == 1) // 클리어
	{
		show_clear_screen();
		show_story(level);

		if (level < 2)
		{
			level++;
			set_difficulty();
			show_game();
		}
		else
		{
			start_menu();
		}

	}

	if (flagId > 1)
	{
		switch (flags[flagId - 1].effect)
		{
		case 0: //시간 정지 아이템 획득
			itemNum[0]++;
			add_event_message("시간 정지 획득");
			break;
		case 1: 
			itemNum[1]++; // 대시 아이템 획득
			add_event_message("대시 획득");
			break;
		case 2: // 보호막 획득
			itemNum[2]++;
			add_event_message("보호막 획득");
			break;
		case 3: //턴 수 +
			moveCount += 5;
			add_event_message("이동가능 횟수 5회 증가");
			break;
		case 4: //목표지점 힌트
			get_flag_hint();
			break;
		case 5://적 추가
			if (level < 1)
			{
				add_event_message("적 추가...... 무시됨");
				break;
			}
			generate_one_enemy(find_empty_enemy_slot());
			add_event_message("적 추가 등장");
			break;
		case 6://이동 횟수 감소
			moveCount -= 3;
			add_event_message("이동가능 횟수 3회 감소");
			break;
		case 7://시야 감소
			activate_reduce_vision(3);
			add_event_message("3회 이동 간 시야 감소..");
			break;
		case 8://레이저 추가
			if (level < 2)
			{
				add_event_message("레이저 추가...... 무시됨");
				break;
			}
			generate_laser(&laserNum, 1);
			add_event_message("레이저 추가 등장");
			break;
		case 9://아이템 사라짐
			temp = rand() & 3;
			if(itemNum[temp] > 0)
				itemNum[temp]--;
			switch (temp)
			{
			case 0:
				add_event_message("시간 정지 파손");
				break;
			case 1:
				add_event_message("대시 파손");
				break;
			case 2:
				add_event_message("보호막 파손");
				break;
			}
			break;
		}

		flags[flagId - 1].effect = 0;
		flags[flagId - 1].id = 0;
		flags[flagId - 1].x = 0;
		flags[flagId - 1].y = 0;
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

void process_laser(int* laserNum, int canLaunch, int * isDanger)
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
					(*isDanger) = 1;
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

int is_move_key(int input)
{
	if (input == 72 || input == 75 || input == 80 || input == 77)
		return 1;

	return 0;
}

void game_loop()
{
	int tileInfo, isMove, isDanger;

	while (1)
	{
		tileInfo = 0;
		isMove = 0;
		isDanger = 0;

		int moveDistance = 1;
		int usingDash = 0;

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

		eventMessage[0] = '\0';

		use_item(input, &canMove, &timeStopTurn, &dashReady);

		if (is_move_key(input) && dashReady)
		{
			moveDistance = 3;
			usingDash = 1;
		}

		place_laser();
		enemy_movement(canMove);
		isMove = player_movement(input, &moveCount, &tileInfo, moveDistance);

		if (usingDash && isMove)
		{
			dashReady = 0;
			add_event_message("대시 발동됨");
		}

		if (isMove)
		{
			update_vision_effect();
			update_time_stop();
		}

		process_laser(&laserNum, canMove, &isDanger);
		spawn_laser(&laserNum, canMove);

		if (tileInfo == -1 || check_enemy_collision(prevX, prevY, playerLocation[0], playerLocation[1]))
		{
			isDanger = 1;
		}

		if (isDanger)
		{
			if (itemNum[2] > 0)
			{
				itemNum[2]--;
				add_event_message("보호막이 사용되었습니다.");
			}
			else
			{
				isDie = 1;
			}
		}

		if (!isDie)
		{
			check_event(find_flag(playerLocation[0], playerLocation[1]));
		}

		show_game();

		if (isDie != 0 || moveCount <= 0)
		{
			Sleep(500);
			show_game_over();
			start_menu();
		}
	}
}