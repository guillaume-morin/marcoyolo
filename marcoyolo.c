#include "marcoyolo.h"

int main (int argc, char** argv) {
    int* matrix;
    int s_rows,s_cols;

    if (argc<3) {
        printf("Not enough parameters.\nUsage : %s s_rows n_columns\n", argv[0]);
        return 1;
	}

    s_rows=atoi(argv[1]);
    s_cols=atoi(argv[2]);

    matrix=calloc(2*s_rows*s_cols,sizeof(int));

    display(matrix,s_rows,s_cols); 
    initialize(matrix,s_rows,s_cols);
    display(matrix,s_rows,s_cols); 

    /* Actual exercise */
    browse(matrix,s_rows,s_cols); 

    destroy(matrix);

    return 0;
}

int initialize (int* matrix, int s_rows, int s_cols) {
    int x;   

    for (x=0;x<=s_rows*s_cols;x++) {
        /*display(matrix,s_rows,s_cols); */
        matrix[x*2]=rand()%2;
        matrix[x*2+1]=0;
    }
    
    return 0; 
}

int display(int* matrix, int s_rows, int s_cols) {
    int x,y;
    char color[16];
    struct timespec pause;

    pause.tv_sec = 0;
    pause.tv_nsec = T_PAUSE;     

    printf("\e[1;1H\e[2J");
    for (y=0;y<(s_cols-1);y++) {
        for (x=0;x<(s_rows-1);x++) {
            sprintf(color,"\x1B[%im",matrix[2*(x+y*s_rows)+1]);
            printf("%s%i",color,matrix[2*(x+y*s_rows)]);
        }
        printf("\n");
    }

    if (nanosleep(&pause,NULL) < 0) {
        printf("Error : syscall nanosleep failed.\n");
        abort;
    }

    return 0;
}

int destroy(int* matrix) {

    free(matrix);

    return 0;
}

int browse(int* matrix, int s_rows, int s_cols) {
    int x,y;
    int newcolor=1;

    for (y=0;y<=(s_cols-1);y++) {
        for (x=0;x<=(s_rows-1);x++) {
            if ( matrix[2*(x+y*s_rows)+1] == 0 ) {
                matrix[2*(x+y*s_rows)+1] = newcolor+30;
                spread(matrix,s_rows,s_cols,x,y);
                display(matrix,s_rows,s_cols);
                newcolor=(newcolor+1)%8;
            }
        }
    }

    return 0;
}

int spread(int* matrix, int s_rows, int s_cols, int source_x, int source_y) {
    int x,y,left_x,left_y,right_x,right_y;

    left_x=source_x-1;
    if ( left_x < 0 )
        left_x=source_x;

    left_y=source_y-1;
    if ( left_y < 0 )
        left_y=source_y;

    right_x=source_x+1;
    if (right_x>=s_rows-1)
        right_x=source_x;

    right_y=source_y+1;
    if (right_y>=s_cols-1)
        right_y=source_y;


    display(matrix,s_rows,s_cols);

    /* Vertical & horizontal spreading only */
    x=source_x;
    for (y=left_y;y<=right_y;y++) {
        if ( ( matrix[2*(x+y*s_rows)+1] == 0 ) &&
           ( matrix[2*(x+y*s_rows)] == matrix[2*(source_x+source_y*s_rows)] ) ) {
            matrix[2*(x+y*s_rows)+1] = matrix[2*(source_x+source_y*s_rows)+1];
            spread(matrix,s_rows,s_cols,x,y); 
        }
    }

    y=source_y;
    for (x=left_x-1;x<=right_x;x++) {
        if ( ( matrix[2*(x+y*s_rows)+1] == 0 ) &&
           ( matrix[2*(x+y*s_rows)] == matrix[2*(source_x+source_y*s_rows)] ) ) {
            matrix[2*(x+y*s_rows)+1] = matrix[2*(source_x+source_y*s_rows)+1];
            spread(matrix,s_rows,s_cols,x,y); 
        }
    }

    /* Vertical & horizontal & diagonal spreading */
    /*for (y=left_y;y<=right_y;y++) {
        for (x=left_x-1;x<=right_x;x++) {
            if ( ( matrix[2*(x+y*s_rows)+1] == 0 ) &&
                 ( matrix[2*(x+y*s_rows)] == matrix[2*(source_x+source_y*s_rows)] ) ) {
                matrix[2*(x+y*s_rows)+1] = matrix[2*(source_x+source_y*s_rows)+1];
                spread(matrix,s_rows,s_cols,x,y); 
            }
        }
    }*/

    return 0;
}



