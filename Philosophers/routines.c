#include "philo.h"

void	*philo_routine(void *arg)
{
	t_philo *philo;
	
	philo = (t_philo *)arg;
	if (philo->index % 2 == 0)
		ft_usleep(1000);
	while(check_vitals(philo) == 0)
	{
		printf("**************\n");
		ft_usleep(1000);
		eat_r(philo);
		ft_usleep(1000);
		sleep_r(philo);
		ft_usleep(1000);
		think_r(philo);
		printf("+++++++++++++++++\n");
	}
	return(arg);
}

void	think_r(t_philo *philo)
{
	if (philo->status != EATING || philo->status != SLEEPING)
		pthread_mutex_lock(philo->think);
	philo->status = THINKING;
	print_message("is thinking... time to death", philo, philo->index);
	philo->time_to_die -= philo->data->time_to_sleep;
	pthread_mutex_unlock(philo->think);
}

void	sleep_r(t_philo *philo)
{
	if (philo->status == EATING)
		pthread_mutex_lock(philo->sleep);
	philo->status = SLEEPING;
	print_message("is sleeping... time to death", philo, philo->index);
	philo->time_to_die -= philo->data->time_to_sleep;
	ft_usleep(philo->data->time_to_sleep);
	pthread_mutex_unlock(philo->sleep);
}

void	eat_r(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	print_message("has taken a fork", philo, philo->index);
	pthread_mutex_lock(philo->l_fork);
	print_message("has taken a fork", philo, philo->index);
	pthread_mutex_lock(philo->eat);
	philo->status = EATING;
	print_message("is eating", philo, philo->index);
	philo->meal_count++;
	pthread_mutex_unlock(philo->eat);
	philo->time_to_die -= philo->data->time_to_eat;
	ft_usleep(philo->data->time_to_eat);
	philo->time_to_die = philo->data->death_time;
	pthread_mutex_unlock(philo->r_fork);
	print_message("has dropped a fork", philo, philo->index);
	pthread_mutex_unlock(philo->l_fork);
	print_message("has dropped a fork", philo, philo->index);
}