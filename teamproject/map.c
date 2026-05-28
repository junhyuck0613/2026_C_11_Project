// 게임 맵 관련 조작, map.c

#include <stdio.h>
#include <stdlib.h>
#include "constant.h"
#include "map.h"

static char map[MAPSIZE][MAPSIZE + 1] = { 0 };
static int playerLocation[2] = { 9 ,1 };
const int flagsPerLevel[4] = { 1, 2, 3 };

int player_movement(char dir)
{
	switch (dir)
	{
	case 72: // 상
		if (playerLocation[1] == 1)
			return 0;
		else
		{
			delete_player(playerLocation, map);
			playerLocation[1] -= 1;
			locate_player(playerLocation, map);
			return 1;
		}

	case 75: // 좌
		if (playerLocation[0] == 1)
			return 0;
		else
		{
			delete_player(playerLocation, map);
			playerLocation[0] -= 1;
			locate_player(playerLocation, map);
			return 1;
		}

	case 80: // 하
		if (playerLocation[1] == MAPSIZE)
			return 0;
		else
		{
			delete_player(playerLocation, map);
			playerLocation[1] += 1;
			locate_player(playerLocation, map);
			return 1;
		}

	case 77: // 우
		if (playerLocation[0] == MAPSIZE)
			return 0;
		else
		{
			delete_player(playerLocation, map);
			playerLocation[0] += 1;
			locate_player(playerLocation, map);
			return 1;
		}

		return 0;
	}

	return 0;
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
	map[playerLocation[0]][playerLocation[1]] = PLAYER;
}

void delete_player()
{
	map[playerLocation[0]][playerLocation[1]] = LAND;
}

void init_map()
{
	int i, j;

	for (i = 0; i < MAPSIZE; i++)
		for (j = 0; j < MAPSIZE; j++)
			map[i][j] = LAND;
}

void place_flags(int level)
{
	int i;

	for (i = 0; i < flagsPerLevel[level]; i++)
	{
		int x = rand() % MAPSIZE;
		int y = rand() % MAPSIZE;
		if (map[x][y] == LAND)
			map[x][y] = FLAG;
		else
			i--;
	}
}