/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adugain <adugain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 12:00:03 by adugain           #+#    #+#             */
/*   Updated: 2023/10/11 15:23:42 by adugain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <stdint.h>
# include <stdlib.h>
# include <sys/time.h>
# define TH_ERROR "Error creating thread"
# define TIME_ERROR "Time error"

struct	s_data;

typedef struct s_philo
{
	struct s_data	*data;
	pthread_t		t;
	int				index;
	int				meal_count;
	int				status;
	int				eating;
	uint64_t		time_to_die;
	pthread_mutex_t	lock;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
}t_philo;

typedef struct s_data
{
	pthread_t	*th;
	t_philo		*philos;
	int			nb_of_philo;
	int			meal_needed;
	int			dead;
	int			done;
	uint64_t	death_time;
	uint64_t	time_to_sleep;
	uint64_t	time_to_eat;
	uint64_t	start_time;
	pthread_mutex_t	lock;
	pthread_mutex_t	write;
	pthread_mutex_t	*fork;
}t_data;

int	ft_atoi(const char *str);
int	check_args(char **av);
int	init(t_data *data, char **av, int ac);
void	free_all(t_data *data);
uint64_t	get_time(void);

#endif
