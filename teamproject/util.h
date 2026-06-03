#include "constant.h"

struct flag
{
	int x, y;
	int effect;
	int id; // 1이면 골
};

extern const int flagsPerLevel[3];
extern struct flag flags[MAXFLAG];

void place_flags(int level);
int find_flag(int x, int y);
int get_tile_info(int player[]);
