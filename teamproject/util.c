// 아이템, 벌칙, 깃발 위치 등등, util.c

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "constant.h"
#include "util.h"

extern char map[MAPSIZE][MAPSIZE];
const int flagsPerLevel[4] = { 5, 10, 15 };

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

