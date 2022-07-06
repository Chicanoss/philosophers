#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include <limits.h>
# include <string.h>
# include <stdbool.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>
#include <time.h>


typedef struct s_arguments
{
    char    *str;
    char    *str2;
    int     j;
    int     k;
    int     usec;
    pthread_t id[2];
}				t_struct;

#endif