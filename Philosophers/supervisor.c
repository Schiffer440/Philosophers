#include "philo.h"

int	supervisor(t_data *data)
{
	pthread_t overseer;
	int	i;
	
	i = 0;
	if (pthread_create(&overseer, NULL, &monitor, data) != 0)
	{
		printf(TH_ERROR);
		return(1);
	}
	while(i <= data->nb_of_philo)
	{
		if (pthread_create(&data->th[i], NULL, &philo_routine, &data->philos[i]))
		{
			free_all(data);
			return (2);
		}
		i++;
	}
	if (pthread_join(overseer, NULL) != 0)
	{
		printf("JOIN_ERROR");
		return(3);
	}
	i = 0;
	while (i <= data->nb_of_philo)
	{
		if (pthread_join(data->th[i], NULL) != 0)
		{
			printf(JOIN_ERROR);
			return(4);
		}
		i++;
	}
	return (0);
}