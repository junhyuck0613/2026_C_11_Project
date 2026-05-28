//기본적인 진행만, 함수 호출과 루프로만, main.c

#include <stdio.h>
#include "output.h"
#include <Windows.h>

int main()
{
	SetConsoleOutputCP(CP_UTF8);

	show_start_menu();
	return 0;
}