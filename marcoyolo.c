#include "marcoyolo.h"

int main (int argc, char** argv) {

    struct s_map *map;

    if (argc>1) {
        printf("Too much parameters.\nUsage : %s\n", argv[0]);
        return 1;
	}

    map=malloc((MAP_SIZE_X*MAP_SIZE_Y*2+1)*sizeof(int));
    init(map);
    display(map);
    browse(map);
    return 0;
}

int init(struct s_map *map) {
    int x,y;
    for (x=0;x<MAP_SIZE_X;x++) {
        for (y=0;y<MAP_SIZE_Y;y++) {
            map->ground[x][y]=rand()%2;
            map->color[x][y]=0;
        }
    }
    map->next_color=30;
    return 0;
}

int display(struct s_map *map) {
    int x,y;
    char color[16];
    struct timespec pause;

    pause.tv_sec = 0;
    pause.tv_nsec = T_PAUSE;  

    printf("\e[1;1H\e[2J");
    for (y=0;y<MAP_SIZE_Y;y++) {
        for (x=0;x<MAP_SIZE_X;x++) {
            sprintf(color,"\x1B[%im",map->color[x][y]);
            printf("%s%i",color,map->ground[x][y]);
        }
        printf("\n");
    }

    if (nanosleep(&pause,NULL) < 0) {
        printf("Error : syscall nanosleep failed.\n");
        abort;
    }

    return 0;
}

int browse(struct s_map *map) {
    int x,y;
    for (y=0;y<MAP_SIZE_Y-1;y++) {
        for (x=0;x<MAP_SIZE_X-1;x++) {
            if (map->color[x][y]==0)
                spread(map,x,y,map->ground[x][y],nextcolor(map));
                display(map);
        }
    }
}

int nextcolor(struct s_map *map) {
    map->next_color=(map->next_color-29)%8+30;
    return map->next_color;
}

int spread(struct s_map *map,int x, int y, int ground, int color) {

    if ( (x<0) || (x>=MAP_SIZE_X) || (y<0) || (y>=MAP_SIZE_Y) ) 
        return 0;

    if (map->color[x][y]!=0)
        return 0;

    if ( ground != map->ground[x][y])
        return 0;


    map->color[x][y]=color;

    spread(map,x-1,y,ground,color);
    spread(map,x+1,y,ground,color);
    spread(map,x,y-1,ground,color);
    spread(map,x,y+1,ground,color);

    spread(map,x-1,y-1,ground,color);
    spread(map,x-1,y+1,ground,color);
    spread(map,x+1,y-1,ground,color);
    spread(map,x+1,y+1,ground,color);

    return 0;
}

