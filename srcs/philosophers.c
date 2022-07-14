#include "../incs/philosophers.h"

void *routine(void *philo)
{
	start_execution(philo);
	pthread_exit(NULL);
}

size_t	get_usec(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
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
}

int main()
{
	int i;
	t_struct main;
	size_t	time;

	main.philo_count = 4;
	main.eat_time = 100;
	main.need_to_eat_time = 250;
	main.sleep_time = 125;

	main.philo = malloc(sizeof(t_philosophers) * main.philo_count);
	main.forks = malloc(sizeof(int) * main.philo_count);
	main.starting_time = get_usec();
	philosophers_placement(&main);
	get_mutex(&main);
	i = 0;
	pthread_t	ida;
	while(i < main.philo_count)
	{
		//printf("test\n");
		pthread_create(&ida, NULL, (void *)routine, (void *)&main.philo[i]);
		pthread_detach(ida);
		i++;
	}
	while(1)
	{
	}
	//pthread_join(ida, NULL);











	/*while (1)
	{
		data.usec = get_usec() - data.starting_time;
		time_to_eat = get_usec() - reset_eat;
		//printf("%lu\n", data.usec);
		if (time_to_eat == data.eating_time)
		{
			printf("Eating time\n");
			time_to_eat = 0;
			reset_eat = get_usec();
		}
		
		while (i < data.philo_nbr)
		{
			pthread_create(&data.id[i], NULL, (void *)routine, &data);
			i++;
			d.k++;
		}


	}*/

}
















/*
	data.j = 1;
	data.str = strdup("ADOF1AK");
	data.k = 0;
	i = 0;
	while (i < 2)
	{
		pthread_create(&data.id[i], NULL, (void *)routine, &data);
		pthread_join(data.id[i], NULL);
		i++;
		data.k++;
	}
	i = 0;
	data.k = 0;
	while (i < 2)
	{
		i++;
		data.k++;
	}
	printf("Valeur de j : %d\n", data.j);
	printf("STR : %s\n", data.str);*/