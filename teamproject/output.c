// 실제 콘솔 화면 출력, output.c

#include <stdio.h>
#include "constant.h"
#include "output.h"
#include "input.h"
#include <Windows.h>
#include <conio.h>

extern char map[MAPSIZE][MAPSIZE];

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

int show_start_menu()
{
	char* levelMenu[] =
	{
		"EASY",
		"NORMAL",
		"HARD",
		"EXIT"
	};
	int i, input, select = 0;

	while (1)
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

		for (i = 0; i < 4; i++)
		{
			if (select == i)
				printf("                       > %s\n", levelMenu[i]);
			else printf("                         %s\n", levelMenu[i]);
		}

		while (1)
		{
			input = get_input();

			switch (input)
			{
			case 72:
				if (select != 0)
					select--;
				break;
			case 80:
				if (select != 3)
					select++;
				break;
			case 13:
				return select;
			default:
				continue;
			}
			break;
		}
	}	
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