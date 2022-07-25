/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eharuni < eharuni@student.42istanbul.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 21:45:51 by eharuni           #+#    #+#             */
/*   Updated: 2022/02/26 21:45:51 by eharuni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

pthread_mutex_t	*fork_init(long long size, t_data *data)
{
	long long		i;
	pthread_mutex_t	*forks;

	forks = malloc(sizeof(pthread_mutex_t) * size);
	if (!forks)
	{
		free(data);
		error("Malloc error\n");
	}	
	i = -1;
	while (++i < size)
		pthread_mutex_init(&forks[i], NULL);
	pthread_mutex_init(&data->mtx_write, NULL);
	pthread_mutex_init(&data->mtx_eat, NULL);
	return (forks);
}

t_data	*data_init(int ac, char **av)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		error("Malloc error\n");
	data->fork_size = ft_atoll(av[1]);
	data->time_die = ft_atoll(av[2]);
	data->time_eat = ft_atoll(av[3]);
	data->time_sleep = ft_atoll(av[4]);
	if (ac == 5)
		data->max_eat = -1;
	else
		data->max_eat = ft_atoll(av[5]);
	if (data->time_die < 1 || data->time_eat < 1 || data->time_sleep < 1
		|| data->fork_size < 1 || (ac == 6 && data->max_eat < 1))
	{
		free(data);
		error("Error: arguments\n");
	}
	data->forks = fork_init(ft_atoll(av[1]), data);
	data->ms_start = current_time();
	data->is_dead = 0;
	data->is_all_eaten = 0;
	return (data);
}

t_ph	**philo_init(t_data *data)
{
	t_ph	**ph;
	int		i;

	ph = (t_ph **)malloc(sizeof(t_ph *) * data->fork_size);
	if (!ph)
	{
		free(data->forks);
		free(data);
		error("Malloc error\n");
	}
	i = 0;
	while (i < data->fork_size)
	{
		ph[i] = (t_ph *)malloc(sizeof(t_ph));
		ph[i]->i = i;
		ph[i]->data = data;
		ph[i]->nbr_eat = 0;
		i++;
	}
	return (ph);
}
