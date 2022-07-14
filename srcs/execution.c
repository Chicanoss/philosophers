#include "../incs/philosophers.h"

/*int eating_time(t_struct *data)
{

    return(0);
}*/
int taking_fork(t_philosophers *philo)
{
    int lfork;
    int rfork;

    lfork = philo->left_fork;
    rfork = philo->right_fork;
    pthread_mutex_lock(&philo->main->forkmutex[lfork]);
    while (philo->main->forks[lfork] != 0)
        ;
    if (philo->main->forks[lfork] == 0)
	{
        pthread_mutex_lock(&philo->main->printmutex);
        printf("%zu    : philosopher %d took left fork\n", philo->main->usec, philo->position);
        pthread_mutex_unlock(&philo->main->printmutex);
		philo->main->forks[lfork] = 1;
	}
    pthread_mutex_lock(&philo->main->forkmutex[rfork]);
    while (philo->main->forks[rfork] != 0)
        ;
    if (philo->main->forks[rfork] == 0)
    {
        pthread_mutex_lock(&philo->main->printmutex);
        printf("%zu    : philosopher %d took right fork\n", philo->main->usec, philo->position);
        pthread_mutex_unlock(&philo->main->printmutex);
        philo->main->forks[rfork] = 1;
    }
     pthread_mutex_unlock(&philo->main->forkmutex[lfork]);
     pthread_mutex_unlock(&philo->main->forkmutex[rfork]);
        sleep(5);
     return(0);
 }

 int eat(t_philosophers *philo)
 {
     pthread_mutex_lock(&philo->main->printmutex);
     printf("%zu    : philosopher %d is eating\n", philo->main->usec, philo->position);
     pthread_mutex_unlock(&philo->main->printmutex);
     //sleep(5);
     //printf("%zu    : philosopher %d has finished eating\n", philo->main->usec, philo->position);

     return(0);
 }

 int release_forks(t_philosophers *philo)
 {
	pthread_mutex_lock(&philo->main->forkmutex[philo->right_fork]);
	philo->main->forks[philo->right_fork] = 0;
	pthread_mutex_unlock(&philo->main->forkmutex[philo->right_fork]);
	pthread_mutex_lock(&philo->main->forkmutex[philo->left_fork]);
	philo->main->forks[philo->left_fork] = 0;
	pthread_mutex_unlock(&philo->main->forkmutex[philo->left_fork]);
    pthread_mutex_lock(&philo->main->printmutex);
    printf("%zu    : philosopher %d start sleeping\n", philo->main->usec, philo->position);
    pthread_mutex_unlock(&philo->main->printmutex);
    //sleep(5);
    
 }

int start_execution(void *philo_temp)
{
    //int i;

    t_philosophers *philo;
    philo = (t_philosophers *)philo_temp;
    //i = 0;
    if (philo->position % 2 == 0)
    {
        pthread_mutex_lock(&philo->main->printmutex);
        printf("%zu    : philosopher %d start thinking\n", philo->main->usec, philo->position);
        pthread_mutex_unlock(&philo->main->printmutex);
        usleep(philo->main->eat_time);
    }
    while (1)
    {
        philo->main->usec = get_usec() - philo->main->starting_time;
        //printf("%d\n", philo->position);
        //sleep(5);
        //break;

        taking_fork(philo);
        eat(philo);
        release_forks(philo);
        //printf("hello\n");
        //taking_rfork(philo);
        //printf("%zu\n", data->usec);
    }
   // printf("hello\n");
    return(0);
}