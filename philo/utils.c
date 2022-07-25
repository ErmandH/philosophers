/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eharuni < eharuni@student.42istanbul.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 21:46:14 by eharuni           #+#    #+#             */
/*   Updated: 2022/02/26 21:46:14 by eharuni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

long long	ft_atoll(char *str)
{
	int			i;
	long long	sign;
	long long	number;

	sign = 1;
	number = 0;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		number = (number * 10) + (str[i] - 48) * sign;
		i++;
	}
	return (number);
}

void	print_status(t_ph *ph, const char *msg)
{
	t_data	*data;

	data = ph->data;
	pthread_mutex_lock(&data->mtx_write);
	if (!(data->is_dead))
	{
		printf("%lld ", current_time() - data->ms_start);
		printf("%d %s", ph->i + 1, msg);
	}	
	pthread_mutex_unlock(&data->mtx_write);
}
