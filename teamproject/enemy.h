struct enemy {
	int x, y;
	int prevX, prevY;
	int dir; // 0 상, 1 하, 2 좌, 3 우
};

extern struct enemy enemies[10];
extern int enemyPerLevel[3];


void ActivateStopEnemyItem();
void UpdateEnemyStopItem();
void MoveEnemy();
int CheckEnemyCollision();
void generate_enemy(int level);
void move_enemy(int num, int canMove);
int check_enemy_collision(int prevX, int prevY, int currX, int currY);