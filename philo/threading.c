/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eharuni < eharuni@student.42istanbul.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 21:46:06 by eharuni           #+#    #+#             */
/*   Updated: 2022/02/26 21:46:06 by eharuni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_meal(t_ph **ph)
{
	int		i;
	t_data	*data;

	i = 0;
	data = ph[0]->data;
	i = 0;
	while (data->max_eat != -1 && i < data->fork_size
		&& ph[i]->nbr_eat >= data->max_eat)
		i++;
	if (i == data->fork_size)
		data->is_all_eaten = 1;
}

void	check_death(t_ph **ph)
{
	int		i;
	t_data	*data;

	data = ph[0]->data;
	while (!(data->is_all_eaten))
	{
		i = -1;
		while (++i < data->fork_size)
		{
			pthread_mutex_lock(&data->mtx_eat);
			if (current_time() - ph[i]->last_eat_t > data->time_die)
			{
				print_status(ph[i], "died\n");
				data->is_dead = 1;
			}
			pthread_mutex_unlock(&data->mtx_eat);
			usleep(100);
		}
		if (data->is_dead)
			break ;
		check_meal(ph);
	}
}

void	eating(t_ph *ph)
{
	t_data	*data;

	data = ph->data;
	pthread_mutex_lock(&data->forks[ph->i]);
	print_status(ph, "has taken a fork\n");
	if (data->fork_size == 1)
	{
		ft_usleep(ph, data->time_die + 50);
		return ;
	}	
	pthread_mutex_lock(&data->forks[(ph->i + 1) % data->fork_size]);
	print_status(ph, "has taken a fork\n");
	pthread_mutex_lock(&data->mtx_eat);
	print_status(ph, "is eating\n");
	ph->last_eat_t = current_time();
	pthread_mutex_unlock(&data->mtx_eat);
	ft_usleep(ph, data->time_eat);
	ph->nbr_eat += 1;
	pthread_mutex_unlock(&data->forks[ph->i]);
	pthread_mutex_unlock(&data->forks[(ph->i + 1) % data->fork_size]);
}

void	*dining(void *param)
{
	t_ph	*ph;
	t_data	*data;

	ph = (t_ph *)param;
	data = ph->data;
	if (ph->i % 2)
		usleep(15000);
	while (!(data->is_dead))
	{
		eating(ph);
		if (data->is_all_eaten)
			break ;
		print_status(ph, "is sleeping\n");
		ft_usleep(ph, data->time_sleep);
		print_status(ph, "is thinking\n");
	}
	return (NULL);
}

int	threading(t_ph **ph)
{
	long long int	i;

	i = 0;
	while (i < ph[0]->data->fork_size)
	{
		if (pthread_create(&ph[i]->th, NULL, &dining, ph[i]) != 0)
			error("Error creating threads!\n");
		ph[i]->last_eat_t = current_time();
		i++;
	}
	check_death(ph);
	i = 0;
	while (i < ph[0]->data->fork_size)
	{
		if (pthread_join(ph[i]->th, NULL) != 0)
			error("Error joining threads!\n");
		i++;
	}
	free_all(ph);
	return (0);
}
