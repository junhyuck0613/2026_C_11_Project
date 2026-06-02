// 실제 콘솔 화면 출력, output.c

#include <stdio.h>
#include "constant.h"
#include "output.h"
#include <Windows.h>
#include <conio.h>

extern char map[MAPSIZE][MAPSIZE + 1];

void render_map()
{
	int y, x;
	char line[MAPSIZE * 3 + 2];

	for (y = 0; y < MAPSIZE; y++)
	{
		int pos = 0;
		for (x = 0; x < MAPSIZE; x++)
		{
			line[pos++] = ' ';
			line[pos++] = map[y][x];
			line[pos++] = ' ';
		}

		line[pos++] = '\n';
		line[pos] = '\0';

		printf("%s", line);
	}
}

void show_start_menu()
{
	system("cls");

	printf("\n\n\n");

	printf("                    ██████╗ ██████╗ ███████╗ █████╗ ██╗  ██╗\n");
	printf("                    ██╔══██╗██╔══██╗██╔════╝██╔══██╗██║ ██╔╝\n");
	printf("                    ██████╔╝██████╔╝█████╗  ███████║█████╔╝ \n");
	printf("                    ██╔══██╗██╔══██╗██╔══╝  ██╔══██║██╔═██╗ \n");
	printf("                    ██████╔╝██║  ██║███████╗██║  ██║██║  ██╗\n");
	printf("                    ╚═════╝ ╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝╚═╝  ╚═╝\n");

	printf("\n\n");

	printf("                               BREAK\n");

	printf("\n\n\n");

	printf("                         [1] EASY\n");
	printf("                         [2] NORMAL\n");
	printf("                         [3] HARD\n");
	printf("                         [ESC] EXIT\n");

	printf("\n\n");

	printf("                      난이도를 선택하세요 : ");
}

void show_menu()
{
	printf("                         MENU\n");
	printf("					 [1] RESTART\n");
	printf("					 [ESC] EXIT\n");
}

void show_story(char ** str, int count)
{
	int i;

	for (i = 0; i < count; i++)
	{
		printf("%s\n", str[i]);
		_getch();
	}
}