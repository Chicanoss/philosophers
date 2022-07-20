#include "../incs/philosophers.h"

int taking_fork(t_philosophers *philo)
{
    pthread_mutex_lock(&philo->main->forkmutex[philo->left_fork]);
    ft_log(philo, get_usec() - philo->main->starting_time, 1);
    pthread_mutex_lock(&philo->main->forkmutex[philo->right_fork]);
	ft_log(philo, get_usec() - philo->main->starting_time, 7);
    return(0);
 }

 int eat(t_philosophers *philo)
 {

	ft_log(philo, get_usec() - philo->main->starting_time, 2);
    ft_usleep(philo->main->eat_time);
	/*pthread_mutex_lock(&philo->main->timemutex);
	get_usec() - philo->main->starting_time;
	pthread_mutex_unlock(&philo->main->timemutex);*/
    philo->nbr_meal++;
    if (philo->nbr_meal == philo->main->repeat_time && philo->main->repeat_time > 0)
    {
    	pthread_mutex_lock(&philo->main->timemutex);
        philo->main->over++;
        pthread_mutex_unlock(&philo->main->timemutex);
        return(0);
    }
    if (philo->main->over == philo->main->philo_count)
    {
        pthread_mutex_unlock(&philo->main->forkmutex[philo->right_fork]);
	    pthread_mutex_unlock(&philo->main->forkmutex[philo->left_fork]);
        pthread_mutex_lock(&philo->main->printmutex);
        printf("philosopher %zu has finished ! \n", philo->position);
		pthread_mutex_unlock(&philo->main->printmutex);
		//philo->is_over = 1;
        return(1);
    }
     return(0);
 }

 int release_forks(t_philosophers *philo)
 {
	pthread_mutex_unlock(&philo->main->forkmutex[philo->right_fork]);
	pthread_mutex_unlock(&philo->main->forkmutex[philo->left_fork]);
	pthread_mutex_lock(&philo->main->timemutex);
    ft_log(philo, get_usec() - philo->main->starting_time, 3);
	pthread_mutex_unlock(&philo->main->timemutex);
	pthread_mutex_lock(&philo->main->timemutex);
    ft_usleep(philo->main->sleep_time);
	pthread_mutex_unlock(&philo->main->timemutex);
	/*pthread_mutex_lock(&philo->main->timemutex);
	philo->usec = get_usec() - philo->main->starting_time;
	pthread_mutex_unlock(&philo->main->timemutex);*/
 }

void    *start_execution(void *philo_temp)
{

    t_philosophers *philo;

    philo = (t_philosophers *)philo_temp;
    philo->nbr_meal = 0;
	//philo->is_over = 0;
	while (1)
	{
		if (philo->main->ready == philo->main->philo_count)
			break;
	}
	if (philo->position % 2 == 0)
		ft_usleep(500);
    while (1)
    {
        if (taking_fork(philo) || eat(philo) || release_forks(philo))
            break;
    }
    return(NULL);
}