// 아이템, 벌칙, 깃발 위치 등등, util.c

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "constant.h"
#include "util.h"

extern char map[MAPSIZE][MAPSIZE];
const int flagsPerLevel[3] = { 5, 10, 15 };
struct flag flags[MAXFLAG] = { 0 };
int itemNum[ITEMNUM] = { 0 }; // 시간 정지, 대시, 보호막
char itemName[ITEMNUM][30] = {
	"Time Stop",
	"Dash",
	"Shield"
};
extern int visionRange;
extern int visionTurn;

// 시간 정지, 대시. 보호막, 턴 수 +, 목표지점 힌트, 적 추가, 이동 횟수 감소, 시야 감소, 레이저 빈도 증가, 아이템 사라짐

void generate_flags(int level)
{
	int i;

	for (i = 0; i < MAXFLAG; i++)
	{
		flags[i].x = 0;
		flags[i].y = 0;
		flags[i].effect = 0;
		flags[i].id = 0;
	}

	for (i = 0; i < flagsPerLevel[level]; i++)
	{
		int x = rand() % MAPSIZE;
		int y = rand() % MAPSIZE;

		int isOverlap = 0;
		for (int j = 0; j < i; j++)
		{
			if (flags[j].x == x && flags[j].y == y)
			{
				isOverlap = 1;
				break;
			}
		}

		if (isOverlap)
		{
			i--;
			continue;
		}

		flags[i].x = x;
		flags[i].y = y;
		flags[i].effect = rand() % 10;
		flags[i].id = i + 1;
	}
}

int find_flag(int x, int y)
{
	for (int i = 0; i < MAXFLAG; i++)
	{
		if (flags[i].id != 0 &&
			flags[i].x == x &&
			flags[i].y == y)
		{
			return flags[i].id;
		}
	}

	return -1;
}

int get_tile_info(int player[])
{
	switch (map[player[1]][player[0]])
	{
	case FLAG:
		return find_flag(player[0], player[1]);
	case ENEMY1:
		return -1;
	case LASER:
		return -1;
	default:
		return 0;
	}
}

void activate_reduce_vision(int turn)
{
	visionRange = 3;
	visionTurn = turn;
}

void use_item(int input, int* canMove, int* timeStopTurn, int* dashReady)
{
	switch (input)
	{
	case 'z': // 시간 정지
		if (itemNum[0] > 0)
		{
			itemNum[0]--;

			(*timeStopTurn) = 3;
			(*canMove) = 0;

			add_event_message("시간 정지 사용됨");
		}
		break;

	case 'x': // 대시
		if (*dashReady)
		{
			add_event_message("이미 대시가 준비되어 있습니다.");
			break;
		}

		if (itemNum[1] > 0)
		{
			itemNum[1]--;
			(*dashReady) = 1;
			add_event_message("대시 준비 완료. 다음 이동은 3칸 이동합니다.");
		}
		break;
	}
}