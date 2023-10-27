/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adugain <adugain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 13:05:35 by adugain           #+#    #+#             */
/*   Updated: 2023/10/27 11:56:41 by adugain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	malloc_t_m(t_data *data)
{
	data->philos = malloc(sizeof(t_philo) * data->nb_of_philo);
	if (!data->philos)
		return (1);
	data->fork = malloc(sizeof(pthread_mutex_t) * data->nb_of_philo);
	if (!data->fork)
	{
		free(data->philos);
		return (2);
	}
	return (0);
}

static int	init_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_of_philo)
	{
		data->philos[i].data = data;
		data->philos[i].index = i + 1;
		printf("///////////PHILO: %d\n", data->philos[i].index);
		data->philos[i].time_to_die = data->death_time;
		data->philos[i].eating = 0;
		data->philos[i].status = 0;
		data->philos[i].meal_count = 0;
		data->philos[i].lock = &data->lock;
		data->philos[i].write = &data->write;
		data->philos[i].eat = &data->eat;
		data->philos[i].sleep = &data->sleep;
		data->philos[i].think = &data->think;
		i++;
	}
	return (0);
}

static int	init_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_of_philo)
	{
		if (pthread_mutex_init(&data->fork[i], NULL) != 0)
			return (1);
		i++;
	}
	i = 0;
	while (i < data->nb_of_philo - 1)
	{
		data->philos[i].l_fork = &data->fork[i + 1];
		data->philos[i].r_fork = &data->fork[i];
		i++;
	}
	data->philos[i].l_fork = &data->fork[0];
	data->philos[i].r_fork = &data->fork[i];
	return (0);
}

static void	init_data(t_data *data, char **av, int ac)
{
	data->nb_of_philo = (int) ft_atoi(av[1]);
	data->death_time = (uint64_t) ft_atoi(av[2]);
	data->time_to_eat = (uint64_t) ft_atoi(av[3]);
	data->time_to_sleep = (uint64_t) ft_atoi(av[4]);
	data->start_time = get_time();	
	if (ac == 6)
		data->meal_needed = ft_atoi(av[5]);
	else
		data->meal_needed = -1;
	data->dead = 0;
	data->done = 0;
	pthread_mutex_init(&data->lock, NULL);
	pthread_mutex_init(&data->write, NULL);
	pthread_mutex_init(&data->eat, NULL);
	pthread_mutex_init(&data->sleep, NULL);
	pthread_mutex_init(&data->think, NULL);

}

int	init(t_data *data, char **av, int ac)
{
	(init_data(data, av, ac));
	if (malloc_t_m(data) != 0)
		return (1);
	if (init_philos(data) != 0)
		return (2);
	if (init_forks(data) != 0)
		return (3);
	return (0);
}