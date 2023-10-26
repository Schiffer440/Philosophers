#include "philo.h"

int	check_vitals(t_philo *philo)
{
	pthread_mutex_lock(philo->lock);
	if (philo->status == DEAD)
		return (pthread_mutex_unlock(philo->lock), DEAD);
	pthread_mutex_unlock(philo->lock);
	return (0);
}