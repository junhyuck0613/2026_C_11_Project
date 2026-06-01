//적 및 공격, enemy.c
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
void MoveEnemy(int map[][MAX_SIZE], int mapSize, int* enemyX, int* enemyY)
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
}
