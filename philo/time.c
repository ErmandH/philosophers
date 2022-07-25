/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eharuni < eharuni@student.42istanbul.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 21:46:11 by eharuni           #+#    #+#             */
/*   Updated: 2022/02/26 21:46:11 by eharuni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long int	current_time(void)
{
	struct timeval	time;
	long long int	ms;

	gettimeofday(&time, NULL);
	ms = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (ms);
}

void	ft_usleep(t_ph *ph, long long time_eat)
{
	long long	start;

	start = current_time();
	while (!(ph->data->is_dead))
	{
		if (current_time() - start >= time_eat)
			break ;
		usleep(50);
	}
}
