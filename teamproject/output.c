// 실제 콘솔 화면 출력, output.c

#include <stdio.h>
#include "constant.h"

void render_map(char map[][mapSize + 1]);



void render_map(char map[][mapSize + 1])
{
	int i, j;

	for (i = 0; i < mapSize; i++)
		printf("\n");
		for (j = 0; j < mapSize; j++)
		{
			printf("%c ", map[i][j]);
		}
}