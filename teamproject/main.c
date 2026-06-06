//기본적인 진행만, 함수 호출과 루프로만, main.c

#define _CRT_SECURE_NO_WARNINGS

#include "game.h"
#include "output.h"
#include <Windows.h>

int main()
{
	SetConsoleOutputCP(CP_UTF8);
	init_game();

	show_story(3);

	start_menu();

	game_loop();
}