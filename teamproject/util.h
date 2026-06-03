const int flagsPerLevel[3];
extern struct flag flags[15];

void place_flags(int level);
int find_flag(int x, int y);
int get_tile_info(int player[]);