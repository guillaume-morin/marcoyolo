#if __STDC_VERSION__ >= 199901L
#define _XOPEN_SOURCE 600
#else
#define _XOPEN_SOURCE 500
#endif /* __STDC_VERSION__ */

#define MAP_SIZE_X 60
#define MAP_SIZE_Y 20
#define T_PAUSE 100000000L

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

typedef struct s_map {
  int ground[MAP_SIZE_X][MAP_SIZE_Y];
  int color[MAP_SIZE_X][MAP_SIZE_Y];
  int next_color;
};

int init(struct s_map *map);
int display(struct s_map *map);
int browse(struct s_map *map);
int nextcolor(struct s_map *map);
int spread(struct s_map *map,int x, int y, int ground, int color);

