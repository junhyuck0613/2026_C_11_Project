// 실제 콘솔 화면 출력, output.c

#include <stdio.h>
#include "constant.h"
#include "output.h"
#include "input.h"
#include <Windows.h>
#include <conio.h>
#include "story.h"

extern char map[MAPSIZE][MAPSIZE];
extern int itemNum[ITEMNUM];
extern char itemName[ITEMNUM][30];
extern char itemKey[ITEMNUM][10];
extern int playerLocation[2];
extern int visionRange;

void render_map()
{
	int y, x;
	char line[MAPSIZE * 3 + 2];

	for (y = 0; y < MAPSIZE; y++)
	{
		int pos = 0;

		for (x = 0; x < MAPSIZE; x++)
		{
			int xDistance = abs(x - playerLocation[0]);
			int yDistance = abs(y - playerLocation[1]);

			line[pos++] = ' ';

			if (xDistance <= visionRange && yDistance <= visionRange)
				line[pos++] = map[y][x];
			else
				line[pos++] = ' ';

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

int show_menu()
{
	char* menu[2] = {
		"RESTART",
		"EXIT"
	};
	int select = 0, input = 0;

	while (1)
	{
		system("cls");
		printf("\n\n\n");
		printf("                         MENU\n");
		for (int i = 0; i < 2; i++)
		{
			if (select == i)
				printf("                     > %s\n", menu[i]);
			else
				printf("                       %s\n", menu[i]);
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
				if (select != 1)
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

void show_message(char str[][150], int count)
{
	int i;

	for (i = 0; i < count; i++)
	{
		printf("%s\n", str[i]);
		_getch();
	}
}

void show_game_over()
{
	system("cls");

	printf("                    ███████╗ █████╗ ██╗██╗     \n");
	printf("                    ██╔════╝██╔══██╗██║██║     \n");
	printf("                    █████╗  ███████║██║██║     \n");
	printf("                    ██╔══╝  ██╔══██║██║██║     \n");
	printf("                    ██║     ██║  ██║██║███████╗\n");
	printf("                    ╚═╝     ╚═╝  ╚═╝╚═╝╚══════╝\n");
	printf("                             FAIL..\n");

	printf("\n\nPRESS ENTER TO CONTINUE.");

	while (_getch() != 13)
	{
	}
}

void print_moveCount(int* moveCount)
{
	printf("\n\n");
	printf("Moves Left: %d", *moveCount);
}

void print_item()
{
	int i;
	printf("\n");
	for (i = 0; i < ITEMNUM; i++)
	{
		printf("%s ", itemName[i]);
		printf("(%s): ", itemKey[i]);
		printf("%d ", itemNum[i]);
	}
}

void show_story(int level)
{
	system("cls");
	switch (level)
	{
	case 0:
		show_message(easyStory, easyStoryCount);
		break;
	case 1:
		show_message(normalStory, normalStoryCount);
		break;
	case 2:
		show_message(hardStory, hardStoryCount);
		break;
	case 3://시작 스토리
		show_message(startStory, startStoryCount);
	}
}

void show_clear_screen()
{
	system("cls");

	printf("\n\n");

	printf("          ███████╗████████╗ █████╗  ██████╗ ███████╗\n");
	printf("          ██╔════╝╚══██╔══╝██╔══██╗██╔════╝ ██╔════╝\n");
	printf("          ███████╗   ██║   ███████║██║  ███╗█████╗  \n");
	printf("          ╚════██║   ██║   ██╔══██║██║   ██║██╔══╝  \n");
	printf("          ███████║   ██║   ██║  ██║╚██████╔╝███████╗\n");
	printf("          ╚══════╝   ╚═╝   ╚═╝  ╚═╝ ╚═════╝ ╚══════╝\n");

	printf("\n");

	printf("           ██████╗██╗     ███████╗ █████╗ ██████╗ ██╗\n");
	printf("          ██╔════╝██║     ██╔════╝██╔══██╗██╔══██╗██║\n");
	printf("          ██║     ██║     █████╗  ███████║██████╔╝██║\n");
	printf("          ██║     ██║     ██╔══╝  ██╔══██║██╔══██╗╚═╝\n");
	printf("          ╚██████╗███████╗███████╗██║  ██║██║  ██║██╗\n");
	printf("           ╚═════╝╚══════╝╚══════╝╚═╝  ╚═╝╚═╝  ╚═╝╚═╝\n");

	printf("\n\n");
	printf("                    PRESS ENTER TO CONTINUE.");

	while (_getch() != 13)
	{
	}
}