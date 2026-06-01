//사용자가 두 칸 이동 아이템 깃발을 밟았을 때 실행
void ActivateDoubleMoveItem(int* moveStep, int* doubleMoveTurn)
{
    *moveStep = DOUBLE_SPEED;
    *doubleMoveTurn = ITEM_EFFECT_TURN;

    printf("%d턴 동안 한 번에 두 칸씩 이동할 수 있습니다.\n", ITEM_EFFECT_TURN);
}

//두 칸 이동 아이템의 지속 시간을 관리
void UpdateDoubleMoveItem(int* moveStep, int* doubleMoveTurn)
{
    if (*doubleMoveTurn > 0) {
        (*doubleMoveTurn)--;

        if (*doubleMoveTurn == 0) {
            *moveStep = NORMAL_SPEED;
            printf("\n두 칸 이동 효과가 종료되었습니다.\n");
            Sleep(600);
        }
    }
}
