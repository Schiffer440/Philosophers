/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adugain <adugain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 12:28:55 by adugain           #+#    #+#             */
/*   Updated: 2023/10/10 14:06:28 by adugain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data	data;
	
	if (ac == 6 || ac == 5)
	{
		if (check_args(av) != 0)
			return(printf("Wrong args...\n"));
		if (init(&data, av, ac) != 0)
			return(printf("Init error...\n"));
	}
	else
		printf("usage ./Philo philos_number time_to_die time_to_eat time_to_sleep meal_needed\n");
	
}

