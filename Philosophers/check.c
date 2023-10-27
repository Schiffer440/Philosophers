#include "philo.h"

int	check_vitals(t_philo *philo)
{
	pthread_mutex_lock(philo->lock);
	if (philo->data->dead > 0)
		return (pthread_mutex_unlock(philo->lock), DEAD);
	else if (philo->data->done > 0)
		return (pthread_mutex_unlock(philo->lock), FULL);
	pthread_mutex_unlock(philo->lock);
	return (0);
}