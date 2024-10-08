#include "marcoyolo.h"

int main (int argc, char** argv) {

    struct s_map *map;

    if (argc>1) {
        printf("Too many parameters.\nUsage : %s\n", argv[0]);
        return 1;
	}

    map=malloc((MAP_SIZE_X*MAP_SIZE_Y*2+1)*sizeof(int));
    if (!map) {
        printf("Error : Cannot allocate memory\n");
        return 2;
    }

    init(map);
    display(map);
    browse(map);

    return 0;
}

int init(struct s_map *map) {
    int x,y;
    srand ( time(NULL) );
    for (x=0;x<MAP_SIZE_X;x++) {
        for (y=0;y<MAP_SIZE_Y;y++) {
            map->ground[x][y]=rand()%2;
            map->color[x][y]=COLOR_NULL;
        }
    }
    map->next_color=30;
    return 0;
}

int display(struct s_map *map) {
    int x,y;
    char color[16];
    char ground;
    struct timespec pause;

    pause.tv_sec = 0;
    pause.tv_nsec = T_PAUSE;  

    printf("\e[1;1H\e[2J");
    for (y=0;y<MAP_SIZE_Y;y++) {
        for (x=0;x<MAP_SIZE_X;x++) {
            if ( map->ground[x][y] == 0 ) 
                ground='~';
            else
                ground='o';
            sprintf(color,"\x1B[%im",map->color[x][y]);
            printf("%s%c",color,ground);
        }
        printf("\n");
    }

    if (nanosleep(&pause,NULL) < 0) {
        printf("Error : syscall nanosleep failed.\n");
        exit(1);
    }

    return 0;
}

int browse(struct s_map *map) {
    int x,y;
    for (y=0;y<MAP_SIZE_Y;y++) {
        for (x=0;x<MAP_SIZE_X;x++) {
            if ( (map->color[x][y]==COLOR_NULL) && (map->ground[x][y] != 0) )
                spread(map,x,y,map->ground[x][y],nextcolor(map));
        }
                display(map);
    }
    return 0;
}

int nextcolor(struct s_map *map) {
    map->next_color=(map->next_color-29)%7+30;
    return map->next_color;
}

int spread(struct s_map *map,int x, int y, int ground, int color) {

    if ( (x<0) || (x>=MAP_SIZE_X) || (y<0) || (y>=MAP_SIZE_Y) ) 
        return 0;

    if (map->color[x][y]!=COLOR_NULL)
        return 0;

    if ( map->ground[x][y] != ground )
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

