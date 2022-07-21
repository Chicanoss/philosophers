#include "../incs/philosophers.h"

void	ft_log(t_philosophers *philo, size_t timestamp, int action)
{
	pthread_mutex_lock(&philo->main->printmutex);
	if (action == 1)
		printf("%zu %zu has taken a fork\n", timestamp, philo->position);
	else if (action == 2)
		printf("%zu %zu is eating\n", timestamp, philo->position);
	else if (action == 3)
		printf("%zu %zu is sleeping\n", timestamp, philo->position);
	else if (action == 4)
		printf("%zu %zu is thinking\n", timestamp, philo->position);
	else if (action == 5)
		printf("%zu %zu died \n", timestamp, philo->position);
	else if (action == 6)
		printf("%zu %zu has finished his meals\n", timestamp, philo->position);
    else if (action == 7)
        printf("%zu %zu has taken a fork\n", timestamp, philo->position);
	pthread_mutex_unlock(&philo->main->printmutex);
}

/*void log_err(int err_msg)
{

}*/