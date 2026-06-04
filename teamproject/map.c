// 게임 맵 관련 조작, map.c

#include <stdio.h>
#include <stdlib.h>
#include "constant.h"
#include "map.h"
#include "util.h"


char map[MAPSIZE][MAPSIZE] = { 0 };
static int playerLocation[2] = { 4 , 9}; // x, y

int player_movement(int dir, int * moveCount)
{
	int temp;
	switch (dir)
	{
	case 72: // 상
		if (playerLocation[1] == 0)
			return 0;
		else
		{
			delete_player();
			playerLocation[1] -= 1;
			temp = get_tile_info(playerLocation);
			locate_player();
			(*moveCount)--;
			return temp;
		}

	case 75: // 좌
		if (playerLocation[0] == 0)
			return 0;
		else
		{
			delete_player();
			playerLocation[0] -= 1;
			temp = get_tile_info(playerLocation);
			locate_player();
			(*moveCount)--;
			return temp;
		}

	case 80: // 하
		if (playerLocation[1] == MAPSIZE - 1)
			return 0;
		else
		{
			delete_player();
			playerLocation[1] += 1;
			temp = get_tile_info(playerLocation);
			locate_player();
			(*moveCount)--;
			return temp;
		}

	case 77: // 우
		if (playerLocation[0] == MAPSIZE - 1)
			return 0;
		else
		{
			delete_player();
			playerLocation[0] += 1;
			temp = get_tile_info(playerLocation);
			locate_player();
			(*moveCount)--;
			return temp;
		}
	}
}

/*
int can_move(char dir, int playerLocation[])
{
	switch(dir)
	{
		case 'w':
			if (playerLocation[2] == 1)
				return 0;
			else 
				return 1;

		case 'a':
			if (playerLocation[1] == 1)
				return 0;
			else 
				return 1;

		case 's':
			if (playerLocation[2] == mapSize)
				return 0;
			else
				return 1;

		case 'd':
			if (playerLocation[1] == mapSize)
				return 0;
			return 1;
	}
}
*/

void locate_player()
{
	map[playerLocation[1]][playerLocation[0]] = PLAYER;
}

void delete_player()
{
	map[playerLocation[1]][playerLocation[0]] = LAND;
}

void init_map()
{
	int y, x;

	for (y = 0; y < MAPSIZE; y++)
	{
		for (x = 0; x < MAPSIZE; x++)
		{
			map[y][x] = LAND;
		}
	}
}