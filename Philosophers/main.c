/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adugain <adugain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 12:28:55 by adugain           #+#    #+#             */
/*   Updated: 2023/10/11 15:24:29 by adugain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	lonely_philo(t_data *data)
{
	data->start_time = get_time();
	if (pthread_create(&data->th[0], NULL, &routine, &data->philos[0]) != 0)
		return (ft_error(TH_ERROR, data));
	pthread_detach(data->th[0]);
	while (data->dead == 0)
	{
		if (ft_usleep(0) != 0)
			return(ft_error(TIME_ERROR, data));
	}
	free_all(data);
	return (0);
}

void	free_all(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nb_of_philo)
	{
		pthread_mutex_destroy(&data->philos[i].lock);
		pthread_mutex_destroy(&data->fork[i]);
	}
	pthread_mutex_destroy(&data->write);
	pthread_mutex_destroy(&data->lock);
	if (data->th)
		free(data->th);
	if (data->philos)
		free(data->philos);
	if (data->fork)
		free(data->fork);
}

int	ft_error(char *str, t_data *data)
{
	printf("%s\n", str);
	free_all(data);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac == 6 || ac == 5)
	{
		if (check_args(av) != 0)
			return (printf("Wrong args...\n"));
		if (init(&data, av, ac) != 0)
			return (printf("Init error...\n"));
		if(data.nb_of_philo == 1)
			lonely_philo(&data);
	}
	else
		printf("usage ./Philo philos_number time_to_die time_\
		to_eat time_to_sleep meal_needed\n");
	free_all(&data);
	return (0);
}

