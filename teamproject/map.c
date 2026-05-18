// 게임 맵 관련 조작, map.c

#include <stdio.h>
#include "constant.h"

int player_movement(char dir, char map[][mapSize+1], int playerLocation[]);
//int can_move(char dir, int playerLocation[]);
void locate_player(int playerLocation[], char map[][mapSize+1]);
void delete_player(int playerLocation[], char map[][mapSize + 1]);
void init_map(char map[][mapSize + 1]);

static char map[mapSize][mapSize + 1] = { 0 };
static int playerLocation[2] = { 9 ,1 };

int player_movement(char dir, char map[][mapSize+1], int playerLocation[])
{
	switch (dir)
	{
	case 'w':
		if (playerLocation[1] == 1)
			return 0;
		else
		{
			delete_player(playerLocation, map);
			playerLocation[1] -= 1;
			locate_player(playerLocation, map);
			return 1;
		}

	case 'a':
		if (playerLocation[0] == 1)
			return 0;
		else 
		{
			delete_player(playerLocation, map);
			playerLocation[0] -= 1;
			locate_player(playerLocation, map);
			return 1;
		}

	case 's':
		if (playerLocation[1] == mapSize)
			return 0;
		else
		{
			delete_player(playerLocation, map);
			playerLocation[1] += 1;
			locate_player(playerLocation, map);
			return 1;
		}

	case 'd':
		if (playerLocation[0] == mapSize)
			return 0;
		else 
		{
			delete_player(playerLocation, map);
			playerLocation[0] += 1;
			locate_player(playerLocation, map);
			return 1;
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

void locate_player(int playerLocation[], char map[][mapSize + 1])
{
	map[playerLocation[0]][playerLocation[1]] = player;
}

void delete_player(int playerLocation[], char map[][mapSize + 1])
{
	map[playerLocation[0]][playerLocation[1]] = '*';
}

void init_map(char map[][mapSize + 1])
{
	int i, j;

	for (i = 0; i < mapSize; i++)
		for (j = 0; j < mapSize; j++)
			map[i][j] = '*';
}