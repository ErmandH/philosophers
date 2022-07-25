/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eharuni < eharuni@student.42istanbul.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 18:39:33 by eharuni           #+#    #+#             */
/*   Updated: 2022/02/28 18:44:44 by eharuni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	long int	n;
	int			sign;

	n = 0;
	sign = 1;
	while ((*str <= 13 && *str >= 9) || *str == 32)
		str++;
	if (*str == '-')
		return (-1);
	else if (*str == '+')
		str++;
	while (*str)
	{
		if (*str >= '0' && *str <= '9')
			n = n * 10 + (*str++ - '0');
		else
			return (-1);
	}
	return ((int)(n * sign));
}

long long	current_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

long long	time_diff(long long past, long long pres)
{
	return (pres - past);
}

void	ft_usleep(long long time, t_rules *rules)
{
	long long	i;

	i = current_time();
	while (!(rules->dieded))
	{
		if (time_diff(i, current_time()) >= time)
			break ;
		usleep(50);
	}
}

void	print_status(t_rules *rules, int id, char *string)
{
	sem_wait(rules->writing);
	if (!(rules->dieded))
	{
		printf("%lli ", current_time() - rules->first_timestamp);
		printf("%i ", id + 1);
		printf("%s\n", string);
	}
	sem_post(rules->writing);
	return ;
}
