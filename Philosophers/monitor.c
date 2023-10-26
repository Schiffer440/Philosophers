#include "philo.h"

static int	is_dead(t_philo philo)
{
	pthread_mutex_lock(&philo.lock);
	if (philo.time_to_die <= 0 || philo.time_to_die < philo.data->time_to_eat
		|| philo.time_to_die < philo.data->time_to_sleep)
	{
		philo.status = DEAD;
		return(philo.status);
	}
	pthread_mutex_unlock(&philo.lock);
	return(philo.status);
}

static int	dead_check(t_data *data)
{
	int	i;

	i = 0;
	while (i <= data->nb_of_philo)
	{
		if (is_dead(data->philos[i]) == DEAD)
			return(1);
		i++;
	}
	return(0);
}

static int	are_full(t_data *data)
{
	int	i;
	int	finished;

	finished = 0;
	i = 0;
	while(i <= data->nb_of_philo)
	{
		pthread_mutex_lock(&data->philos[i].lock);
		if (data->philos[i].meal_count == data->meal_needed)
			finished++;
		pthread_mutex_unlock(&data->philos[i].lock);
		i++;
	}
	if (finished >= data->nb_of_philo)
		return(1);
	return(0);
}

void	*monitor(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;

	while(1)
	{
		if (dead_check(data) == 1 || are_full(data) == 1)
			break ;
	}
	return(arg);
}