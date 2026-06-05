//적 및 공격, enemy.c

#include <stdio.h>
#include <stdlib.h>
#include "constant.h"
#include "enemy.h"

struct enemy enemies[10] = { 0 };
int enemyPerLevel[3] = { 0 , 3, 6 };
extern int playerLocation[2];
extern char map[MAPSIZE][MAPSIZE];

int check_enemy_collision(int prevX, int prevY, int currX, int currY)
{
    for (int i = 0; i < 10; i++) {
        if (enemies[i].x == 0 && enemies[i].y == 0 && 
            enemies[i].prevX == 0 && enemies[i].prevY == 0)
            continue;

        // 적이 플레이어 칸에 들어옴
        if (prevX == enemies[i].prevX && prevY == enemies[i].prevY &&
            currX == enemies[i].x && currY == enemies[i].y)
            return 1;

        //정면에서 마주침 (위치 교환)
        if (prevX == enemies[i].x && prevY == enemies[i].y &&
            currX == enemies[i].prevX && currY == enemies[i].prevY)
            return 1;
    }
    return 0;
}

/*
//적 정지 아이템 깃발을 밟았을 때 실행
void ActivateStopEnemyItem(int* enemyStopTurn)
{
    *enemyStopTurn = ITEM_EFFECT_TURN;

    printf("%d턴 동안 움직이는 적이 정지합니다.\n", ITEM_EFFECT_TURN);
}

//적 정지 아이템의 지속 시간을 관리
void UpdateEnemyStopItem(int* enemyStopTurn)
{
    if (*enemyStopTurn > 0) {
        (*enemyStopTurn)--;

        if (*enemyStopTurn == 0) {
            printf("\n적 정지 효과가 종료되었습니다.\n");
            Sleep(600);
        }
    }
}

//움직이는 적을 매 턴마다 랜덤 방향으로 이동시키는 함
void MoveEnemy(int map[][MAPSIZE], int mapSize, int* enemyX, int* enemyY)
{
    int dx[4] = { 0, 0, -1, 1 };
    int dy[4] = { -1, 1, 0, 0 };

    int dir;
    int nextX;
    int nextY;
    int i;

    for (i = 0; i < 10; i++) {
        dir = rand() % 4;

        nextX = *enemyX + dx[dir];
        nextY = *enemyY + dy[dir];

        if (nextX < 0 || nextX >= mapSize || nextY < 0 || nextY >= mapSize) {
            continue;
        }

        if (map[nextY][nextX] == WALL) {
            continue;
        }

        *enemyX = nextX;
        *enemyY = nextY;
        break;
    }
}

//플레이어와 적이 같은 위치에 있는지 확인하는 함수
int CheckEnemyCollision(int playerX, int playerY, int enemyX, int enemyY)
{
    if (playerX == enemyX && playerY == enemyY) {
        printf("\n움직이는 적과 충돌했습니다. 게임 오버!\n");
        return 1;
    }

    return 0;
}*/

void generate_enemy(int level)
{
    int i, x, y, dir;

    for (i = 0; i < 10; i++)
    {
        enemies[i].x = 0;
        enemies[i].y = 0;
        enemies[i].prevX = 0;
        enemies[i].prevY = 0;
        enemies[i].dir = 0;
    }

    for (i = 0; i < enemyPerLevel[level]; i++)
    {
        x = rand() % MAPSIZE;
        y = rand() % MAPSIZE;
        dir = rand() % 4;

        if ((playerLocation[0] == x) && (playerLocation[1] == y))
        {
            i--;
            continue;
        }

        enemies[i].x = x;
        enemies[i].y = y;
        enemies[i].prevX = x;  // 초기 이전 위치도 현재 위치로 설정
        enemies[i].prevY = y;
        enemies[i].dir = dir;
    }
}

void move_enemy(int num, int canMove)
{
    if (!canMove)
        return;

    enemies[num].prevX = enemies[num].x;
    enemies[num].prevY = enemies[num].y;

    switch (enemies[num].dir)
    {
    case 0: // 상
        if (enemies[num].y == 0)
        {
            enemies[num].dir = 1;
            enemies[num].y++;
        }
        else
        {
            enemies[num].y--;
        }
        break;

    case 1: // 하
        if (enemies[num].y == MAPSIZE - 1)
        {
            enemies[num].dir = 0;
            enemies[num].y--;
        }
        else
        {
            enemies[num].y++;
        }
        break;

    case 2: // 좌
        if (enemies[num].x == 0)
        {
            enemies[num].dir = 3;
            enemies[num].x++;
        }
        else
        {
            enemies[num].x--;
        }
        break;

    case 3: // 우
        if (enemies[num].x == MAPSIZE - 1)
        {
            enemies[num].dir = 2;
            enemies[num].x--;
        }
        else
        {
            enemies[num].x++;
        }
        break;
    }
}