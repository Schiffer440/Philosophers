#include "philo.h"

static int	is_dead(t_philo philo)
{
	uint64_t	time;

	// pthread_mutex_lock(&philo.data->write);
	time = get_time() - philo.data->start_time;
	// printf("TTD%ld\n", philo.time_to_die);
	// printf("Time%ld\n", time);
	// printf("last meal%ld\n", philo.last_meal);
	if ((time - philo.last_meal) > philo.time_to_die)
	{
		philo.status = DEAD;
		// printf("////////Status: %d/////////\n", philo.status);
		return(philo.status);
	}
	// pthread_mutex_unlock(&philo.data->write);
	return(philo.status);
}

static int	dead_check(t_data *data)
{
	int	i;

	i = 0;
	// printf("/////Death checking...../////\n");
	while (i < data->nb_of_philo)
	{
		pthread_mutex_lock(&data->eat);
		if (is_dead(data->philos[i]) == DEAD)
		{
			pthread_mutex_lock(data->philos[i].lock);
			print_message("just died\n", data->philos, data->philos[i].index);
			data->dead = 1;
			pthread_mutex_unlock(data->philos[i].lock);
			return (pthread_mutex_unlock(&data->eat), 1);
		}
		pthread_mutex_unlock(&data->eat);
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
	while(i < data->nb_of_philo)
	{
		pthread_mutex_lock(data->philos[i].eat);
		if (data->philos[i].meal_count == data->meal_needed)
		{
			finished++;
			// print_message("is full !!!", &data->philos[i], data->philos[i].index);
		}
		pthread_mutex_unlock(data->philos[i].eat);
		i++;
	}
	if (finished >= data->nb_of_philo)
	{
		data->done = 1;
		return(1);
	}
	return(0);
}

int	monitor(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	// printf("//////Phi:")
	while(1)
	{
		if (dead_check(data) == 1)
			return (1);
		else if (are_full(data) == 1)
			return (0);
	}
}