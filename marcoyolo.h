#if __STDC_VERSION__ >= 199901L
#define _XOPEN_SOURCE 600
#else
#define _XOPEN_SOURCE 500
#endif /* __STDC_VERSION__ */

#define T_PAUSE 100000000L

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

int initialize (int* matrix, int s_rows, int s_cols);
int destroy(int* matrix);
int display(int* matrix, int s_rows, int s_cols);

int browse(int* matrix, int s_rows, int s_cols);
int spread(int* matrix, int s_rows, int s_cols, int source_x, int source_y); 

