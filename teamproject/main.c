//기본적인 진행만, 함수 호출과 루프로만, main.c

#define _CRT_SECURE_NO_WARNINGS

#include "game.h"
#include "output.h"

int main()
{
	init_game();

	start_menu();

	render_map();

	return 0;
}