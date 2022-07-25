/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eharuni < eharuni@student.42istanbul.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 21:45:47 by eharuni           #+#    #+#             */
/*   Updated: 2022/02/26 21:45:47 by eharuni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_all(t_ph **ph)
{
	int		i;
	t_data	*data;

	i = -1;
	data = ph[0]->data;
	while (++i < data->fork_size)
		free(ph[i]);
	free(data->forks);
	free(data);
	free(ph);
}

int	main(int ac, char **av)
{
	t_data	*data;
	t_ph	**ph;

	if (ac != 5 && ac != 6)
		error("Error: arguments\n");
	data = data_init(ac, av);
	ph = philo_init(data);
	threading(ph);
}
