#include "../incs/philosophers.h"

/*void *routine(void *philo)
{
	start_execution(philo);
	pthread_exit(NULL);
}*/

size_t	get_usec(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

/*int get_args(t_struct *main, int 	argc, char	*argv)
{

}*/

int	philosophers_placement(t_struct *main)
{
	int i;

	i = 0;
	while (i < main->philo_count)
	{
		main->forks[i] = 0;
		main->philo[i].position = i;
		main->philo[i].left_fork = i;
		if (i != main->philo_count - 1)
			main->philo[i].right_fork = i + 1;
		else
			main->philo[i].right_fork = 0;
		main->philo[i].main = main;
		main->philo->nbr_meal = 0;

		/**
		 * On inverse les fouchettes pour un philo sur deux pour
		 * eviter le probleme de "deadlock".
		 */
		if (i & 1)
		{
			int tmp = main->philo[i].left_fork;
			main->philo[i].left_fork = main->philo[i].right_fork;
			main->philo[i].right_fork = tmp;
		}

		i++;
	}
	return(0);

}
void get_mutex(t_struct *main)
{
	int i;

	i = 0;
	main->forkmutex = malloc(sizeof(pthread_mutex_t) * main->philo_count);
 // penser a securiser
	while (i < main->philo_count)
	{
		pthread_mutex_init(&main->forkmutex[i], NULL);
		i++;
	}
	pthread_mutex_init(&main->printmutex, NULL);
	pthread_mutex_init(&main->timemutex, NULL);
}

void	ft_usleep(size_t ms)
{
	size_t	end;

	end = get_usec() + ms;
	while (get_usec() < end)
		usleep(ms / 1000);
}

int main()
{
	int i;
	t_struct main;
	size_t	time;

	main.philo_count = 200;
	main.eat_time = 300;
	main.need_to_eat_time = 500;
	main.sleep_time = 100;
	main.repeat_time = 5;
	main.over = 0;

	main.philo = malloc(sizeof(t_philosophers) * main.philo_count);
	main.forks = malloc(sizeof(int) * main.philo_count);
	main.ready = 0;
	main.starting_time = get_usec();
	philosophers_placement(&main);
	get_mutex(&main);
	i = 0;
	pthread_t	ida;
	printf("hello\n\n");
	while(i < main.philo_count)
	{
		pthread_create(&ida, NULL, (void *)start_execution, (void *)&main.philo[i]);
		i++;
		main.ready++;
		pthread_detach(ida);
	}
	while(1)
	{}

}
