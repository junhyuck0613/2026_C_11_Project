#include "constant.h"

void reset_player_location();
int player_movement(int dir, int* moveCount);
int check_enemies_collision(int prevX, int prevY, int currX, int currY);
//int can_move(char dir, int playerLocation[]);
void locate_player();
void delete_player();
void init_map();
void place_enemy(int num);
void delete_enemy(int num);
void place_all_enemy(int level);
void enemy_movement(int level, int canMove);