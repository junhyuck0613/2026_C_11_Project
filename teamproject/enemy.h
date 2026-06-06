struct enemy {
	int x, y;
	int preX, preY;
	int dir; // 0 상, 1 하, 2 좌, 3 우
};

struct laser {
	int active;
	int line;
	int isVertical; // 0 가로, 1 세로 로 발사
	char countdown;
};

extern struct enemy enemies[10];
extern int enemyPerLevel[3];
extern int maxLaserPerLevel[3];
extern struct laser lasers[8];

/*void ActivateStopEnemyItem();
void UpdateEnemyStopItem();
void MoveEnemy();
int CheckEnemyCollision();*/
void generate_enemy(int level);
void move_enemy(int num, int canMove);
int check_enemy_collision(int prevX, int prevY, int curX, int curY);
void generate_laser(int* laserNum);
void init_laser(int num, int* laserNum);