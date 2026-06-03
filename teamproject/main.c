//기본적인 진행만, 함수 호출과 루프로만, main.c

#define _CRT_SECURE_NO_WARNINGS

#include "game.h"
#include "output.h"
#include <Windows.h>

int main()
{
	init_game();
	//시작 메뉴 나오기 전에 스토리 출력

	start_menu();

	game_loop();
}