/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adugain <adugain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 15:01:25 by adugain           #+#    #+#             */
/*   Updated: 2023/10/30 09:46:52 by adugain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->index % 2 == 0)
		usleep(1000);
	while (check_vitals(philo) == 0)
	{
		// printf("**************\n");
		// ft_usleep(1000);
		eat_r(philo);
		// ft_usleep(1000);
		sleep_r(philo);
		// ft_usleep(1000);
		think_r(philo);
		// printf("+++++++++++++++++\n");
	}
	return (arg);
}

void	think_r(t_philo *philo)
{
	if (philo->status != EATING || philo->status != SLEEPING)
		pthread_mutex_lock(philo->think);
	philo->status = THINKING;
	print_message("is thinking", philo, philo->index);
	usleep(philo->data->time_to_sleep * 1000);
	pthread_mutex_unlock(philo->think);
}

void	sleep_r(t_philo *philo)
{
	pthread_mutex_lock(philo->eat);
	if (philo->status == EATING)
		pthread_mutex_lock(philo->sleep);
	philo->status = SLEEPING;
	print_message("is sleeping", philo, philo->index);
	usleep(philo->data->time_to_sleep * 1000);
	pthread_mutex_unlock(philo->sleep);
	pthread_mutex_unlock(philo->eat);
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
	philo->last_meal = get_time() - philo->data->start_time;
	pthread_mutex_unlock(philo->eat);
	usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_unlock(philo->r_fork);
	// print_message("has dropped a fork", philo, philo->index);
	pthread_mutex_unlock(philo->l_fork);
	// print_message("has dropped a fork", philo, philo->index);
}