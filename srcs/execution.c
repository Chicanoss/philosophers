#include "../incs/philosophers.h"

/*int	is_dead(t_philosophers *philo)
{
	size_t	dead;
	
	if (philo->lastmeal - get_usec() > philo->ttd)
		return(1);
	else 
		return(0);
}*/
 int eat(t_philosophers *philo)
 {

	ft_log(philo, get_usec() - philo->main->starting_time, 2);
    ft_usleep(100);
    philo->nbr_meal++;
    if (philo->nbr_meal == philo->main->repeat_time && philo->main->repeat_time > 0)
    {
    	pthread_mutex_lock(&philo->main->timemutex);
        philo->main->over++;
		pthread_mutex_unlock(&philo->main->timemutex);
        return(0);
    }
	// data race ici attention
	//pthread_mutex_lock(&philo->main->timemutex);
	//int temp = philo->main->over;
	//pthread_mutex_unlock(&philo->main->timemutex);
    if (philo->main->over == philo->main->philo_count)
    {
        pthread_mutex_unlock(&philo->main->forkmutex[philo->right_fork]);
	    pthread_mutex_unlock(&philo->main->forkmutex[philo->left_fork]);
	//	pthread_mutex_lock(&philo->main->timemutex);
		philo->main->is_over++;
	//	pthread_mutex_unlock(&philo->main->timemutex);
        pthread_mutex_lock(&philo->main->printmutex);
        return(1);
    }
     return(0);
 }

int taking_fork(t_philosophers *philo)
{
    pthread_mutex_lock(&philo->main->forkmutex[philo->left_fork]);
    pthread_mutex_lock(&philo->main->forkmutex[philo->right_fork]);
    ft_log(philo, get_usec() - philo->main->starting_time, 1);
	if (eat(philo))
		return(1);
	pthread_mutex_unlock(&philo->main->forkmutex[philo->right_fork]);
	pthread_mutex_unlock(&philo->main->forkmutex[philo->left_fork]);
    ft_log(philo, get_usec() - philo->main->starting_time, 3);
    ft_usleep(50);
	ft_log(philo, get_usec() - philo->main->starting_time, 4);
	return(0);
 }

 /*int release_forks(t_philosophers *philo)
 {
	pthread_mutex_unlock(&philo->main->forkmutex[philo->right_fork]);
	pthread_mutex_unlock(&philo->main->forkmutex[philo->left_fork]);
    ft_log(philo, get_usec() - philo->main->starting_time, 3);
    ft_usleep(50);
	ft_log(philo, get_usec() - philo->main->starting_time, 4);
	return(0);
 }*/

void    *start_execution(void *philo_temp)
{

    t_philosophers *philo;

    philo = (t_philosophers *)philo_temp;
    philo->nbr_meal = 0;
	//pthread_mutex_lock(&philo->main->printmutex);
	philo->main->is_over = 0;
	//pthread_mutex_unlock(&philo->main->printmutex);
	while (1)
	{
		if (philo->main->ready == philo->main->philo_count)
		{
			break;
		}
	}
	philo->main->starting_time = get_usec();
	if (philo->position % 2 != 0)
	{
		ft_log(philo, get_usec() - philo->main->starting_time, 4);
		ft_usleep(philo->main->eat_time / 2);
		//ft_usleep(100);
	}
    while (1)
    {
        if(taking_fork(philo))
			break;
    }
    return(NULL);
}