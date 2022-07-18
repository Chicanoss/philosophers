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
    pthread_mutex_lock(&philo->main->printmutex);
    printf("%zu    : philosopher %d took left fork\n", philo->main->usec, philo->position);
    pthread_mutex_unlock(&philo->main->printmutex);
	philo->main->forks[lfork] = 1;
    pthread_mutex_lock(&philo->main->forkmutex[rfork]);
    pthread_mutex_lock(&philo->main->printmutex);
    printf("%zu    : philosopher %d took right fork\n", philo->main->usec, philo->position);
    pthread_mutex_unlock(&philo->main->printmutex);
    philo->main->forks[rfork] = 1;
    return(0);
 }

 int eat(t_philosophers *philo)
 {
     pthread_mutex_lock(&philo->main->printmutex);
     printf("%zu    : philosopher %d is eating\n", philo->main->usec, philo->position);
     pthread_mutex_unlock(&philo->main->printmutex);
     usleep(philo->main->eat_time);
     return(0);
 }

 int release_forks(t_philosophers *philo)
 {
	pthread_mutex_unlock(&philo->main->forkmutex[philo->right_fork]);
	pthread_mutex_unlock(&philo->main->forkmutex[philo->left_fork]);
    pthread_mutex_lock(&philo->main->printmutex);
    printf("%zu    : philosopher %d start sleeping\n", philo->main->usec, philo->position);
    pthread_mutex_unlock(&philo->main->printmutex);
    ft_usleep(philo->main->sleep_time);  
 }

int start_execution(void *philo_temp)
{

    t_philosophers *philo;

    philo = (t_philosophers *)philo_temp;
    philo->main->usec = get_usec() - philo->main->starting_time;
    if (philo->position % 2 == 0)
    {
        pthread_mutex_lock(&philo->main->printmutex);
        printf("%zu    : philosopher %d start thinking\n", philo->main->usec, philo->position);
        pthread_mutex_unlock(&philo->main->printmutex);
        ft_usleep(philo->main->eat_time);
    }
    while (1)
    {
        philo->main->usec = get_usec() - philo->main->starting_time;
        taking_fork(philo);
        eat(philo);
        release_forks(philo);
    }
    return(0);
}