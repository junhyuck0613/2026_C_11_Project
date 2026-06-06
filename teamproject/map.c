// 게임 맵 관련 조작, map.c

#include <stdio.h>
#include <stdlib.h>
#include "constant.h"
#include "map.h"
#include "util.h"
#include "enemy.h"


char map[MAPSIZE][MAPSIZE] = { 0 };
int playerLocation[2] = { 4 , 9}; // x, y

void reset_player_location()
{
	playerLocation[0] = 4;
	playerLocation[1] = 9;
}

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

void place_enemy(int num)
{
	map[enemies[num].y][enemies[num].x] = ENEMY1;
}

void delete_enemy(int num)
{
	map[enemies[num].y][enemies[num].x] = LAND;
}

void place_all_enemy(int level)
{
	int i;
	for (i = 0; i < enemyPerLevel[level]; i++)
	{
		place_enemy(i);
	}
}

void enemy_movement(int level, int canMove)
{
	int i;
	
	for (i = 0; i < enemyPerLevel[level]; i++)
	{
		delete_enemy(i);
		move_enemy(i, canMove);
		place_enemy(i);
	}
}

void place_laser()
{
	int i, j;

	for (i = 0; i < MAXLASER; i++)
	{
		if (lasers[i].active == 0)
			continue;

		if (lasers[i].isVertical == 0)
		{
			for (j = 0; j < MAPSIZE; j++)
			{
				if (lasers[i].countdown != LASER &&
					map[lasers[i].line][j] == FLAG)
					continue;

				if (lasers[i].countdown == LASER)
				{
					map[lasers[i].line][j] = LASER;
				}
				else
				{
					map[lasers[i].line][j] = '0' + lasers[i].countdown;
				}
			}
		}
		else
		{
			for (j = 0; j < MAPSIZE; j++)
			{
				if (lasers[i].countdown != LASER &&
					map[j][lasers[i].line] == FLAG)
					continue;

				if (lasers[i].countdown == LASER)
				{
					map[j][lasers[i].line] = LASER;
				}
				else
				{
					map[j][lasers[i].line] = '0' + lasers[i].countdown;
				}
			}
		}
	}
}

void place_flags()
{
	for (int i = 0; i < MAXFLAG; i++)
	{
		if (flags[i].id == 0)
			continue;

		map[flags[i].y][flags[i].x] = FLAG;
	}
}