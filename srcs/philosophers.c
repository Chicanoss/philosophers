#include "../incs/philosophers.h"

void routine(t_struct *data)
{
	start_execution(&data);
	pthread_exit(NULL);
}

size_t	get_usec(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
int	philosophers_placement(t_struct *data)
{
	int i;

	i = 0;
	while (i < data->philo_count)
	{
		data->philo[i].position = i;
		data->philo[i].left_fork = i;
		if (i != data->philo_count - 1)
			data->philo[i].right_fork = i + 1;
		else
			data->philo[i].right_fork = 1;
		i++;
	}
	return(0);

}

int main()
{
	int i;
	t_struct data;

	data.philo_count = 4;
	data.philo = malloc(sizeof(t_philosophers) * data.philo_count);
	data.starting_time = get_usec();
	philosophers_placement(&data);
	i = 0;
	
	while(i < data.philo_count)
	{
		printf("test\n");
		pthread_create(&data.philo[i].id, NULL, (void *)routine, &data);
		pthread_join(data.philo[i].id, NULL);
		i++;
	}










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