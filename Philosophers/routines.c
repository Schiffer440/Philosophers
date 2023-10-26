#include "philo.h"

void	*philo_routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	while(check_vitals(philo) != DEAD)
	{
		eat_r(philo);
		sleep_r(philo);
		think_r(philo);
	}
	return(arg);
}

void	think_r(t_philo *philo)
{
	print_message("is thinking... time to death", philo, philo->index - 1);
	philo->status = THINKING;
}

void	sleep_r(t_philo *philo)
{
	print_message("is sleeping... time to death", philo, philo->index - 1);
	philo->status = SLEEPING;
	philo->time_to_die -= philo->data->time_to_sleep;
	ft_usleep(philo->data->time_to_sleep);
}

void	eat_r(t_philo *philo)
{
	pthread_mutex_lock(&philo->lock);
	pthread_mutex_lock(philo->r_fork);
	print_message("has taken a fork", philo, philo->index - 1);
	pthread_mutex_lock(philo->l_fork);
	print_message("has taken a fork", philo, philo->index - 1);
	philo->status = EATING;
	print_message("is eating", philo, philo->index - 1);
	philo->meal_count++;
	pthread_mutex_unlock(&philo->lock);
	philo->time_to_die -= philo->data->time_to_eat;
	ft_usleep(philo->data->time_to_eat);
	philo->status = 0;
	philo->time_to_die = philo->data->death_time;
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}