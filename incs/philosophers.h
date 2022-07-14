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

struct s_argument;

typedef struct s_philosophers
{
	// Philo misc

	pthread_t	id; // philosopher ID
	int			state; // 1: think, 2: eat, 3: sleep, 4: dead
	int			position;
	int			left_fork;
	int			right_fork;
	

	// Time for each philo

	int			ttd; // time till die
	int			ttt; // time to think
	int			tts; // time to think

	// Main

	struct s_struct *main;


}				t_philosophers;

typedef struct s_struct
{

    // Test Functions

    char	*str;
    char	*str2;
    int		j;
    int		k;
	int 	pos;

    // Time functions

    size_t	usec;
	size_t	starting_time;	


	// Args

	int			philo_count; // Nbr of philo's
	size_t		need_to_eat_time; //Time until philo must eat
	size_t		eat_time; // How long it takes for a philosopher to eat
	size_t		sleep_time; //How long it takes for a philosopher to sleep
	size_t		repeat_time; // Number of times every philosopher must eat before exiting

	//Philo

	t_philosophers *philo;
	int			*forks;

	pthread_mutex_t printmutex;	
	pthread_mutex_t	*forkmutex;

	
}				t_struct;

//functions 
int start_execution(void* philo_temp);
size_t get_usec();


#endif