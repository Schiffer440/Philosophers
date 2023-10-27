/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adugain <adugain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 12:24:35 by adugain           #+#    #+#             */
/*   Updated: 2023/10/27 17:07:26 by adugain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_args(char **av)
{
	int	i;

	i = 1;
	while (av[i])
	{
		if (ft_atoi(av[i]) <= 0)
			return (1);
		i++;
	}
	return(0);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	nb;
	int	sign;

	sign = 1;
	i = 0;
	nb = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' && str[i + 1] >= '0' && str[i + 1] <= '9')
	{
		sign = -sign;
		i++;
	}
	if (str[i] == '+' && str[i + 1] >= '0' && str[i + 1] <= '9')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + (str[i] - 48);
		i++;
	}
	return (nb * sign);
}

uint64_t	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (ft_error("gettimeofday() FAILURE\n", NULL));
	return ((tv.tv_sec * (uint64_t)1000) + (tv.tv_usec / 1000));
	// get_time(void) - getimeofday(0) //
}

// int	ft_usleep(unsigned long time)
// {
//     struct timespec req;
//     req.tv_sec = time / 1000;
//     req.tv_nsec = (time % 1000) * 100000;

//     return 0;
// }

uint64_t	timeleft(t_philo *philo)
{
	return (philo->data->start_time - philo->last_meal);
}

void	print_message(char *str, t_philo *philo, int index)
{
	uint64_t	time;

	pthread_mutex_lock(&philo->data->write);
	time = get_time() - philo->data->start_time;
	if (philo->data->dead != 0)
		printf("%ld %d %s %ld\n", time, index, str, timeleft(philo));
	else
		printf("%ld %d %s\n", time, index, str);
	pthread_mutex_unlock(&philo->data->write);
}

