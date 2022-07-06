#include "../incs/philosophers.h"

void routine(t_struct *data)
{
	int i;
	char c = 'A';

	i = 0;
	if (data->k == 0)
		data->j = 10;
	if (data->k == 1)
	{
		//data->j = 12;
		while(i < 10)
		{
			data->str[i] = c;
			/*if (data->str[i] <= '9' && data->str[i] >= '0')
			{	
				printf("test\n");
				data->str[i] = c;
			}*/
			i++;
		}
	}
	pthread_exit(NULL);
}
int get_usec ()
{
	struct timeval tv;
    struct timezone tz;
    struct tm *today;

    gettimeofday(&tv,&tz);
	return(tv.tv_usec);

}
int main()
{
	int i;
	t_struct data;
	
	while (1)
	{
		data.usec = get_usec();
		if (data.usec == 10000)
			printf("test\n");
		//printf("%d\n", data.usec);
	}

	 //printf("seconds : %ld\nmicro seconds : %ld", current_time.tv_sec, current_time.tv_usec);
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

}