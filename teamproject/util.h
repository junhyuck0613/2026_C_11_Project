//util.h

#include "constant.h"

struct flag
{
	int x, y;
	int effect;
	int id; // 1이면 골
};

extern const int flagsPerLevel[3];
extern struct flag flags[MAXFLAG];
extern int itemNum[ITEMNUM];
extern char itemName[ITEMNUM][30];
extern char itemKey[ITEMNUM][10];

void generate_flags(int level);
int find_flag(int x, int y);
int get_tile_info(int player[]);
void use_item(int input, int* canMove, int* timeStopTurn, int* dashReady);
