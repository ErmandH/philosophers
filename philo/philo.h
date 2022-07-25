/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eharuni < eharuni@student.42istanbul.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 21:46:03 by eharuni           #+#    #+#             */
/*   Updated: 2022/02/26 21:46:03 by eharuni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_data
{
	int				time_die;
	long long int	ms_start;
	int				time_eat;
	int				time_sleep;
	int				max_eat;
	int				fork_size;
	pthread_mutex_t	*forks;
	pthread_mutex_t	mtx_write;
	pthread_mutex_t	mtx_eat;
	int				is_dead;
	int				is_all_eaten;
}	t_data;

typedef struct s_ph
{
	pthread_t	th;
	int			i;
	t_data		*data;	
	int			nbr_eat;	
	long long	last_eat_t;

}	t_ph;

long long		ft_atoll(char *str);
void			error(char *msg);
t_data			*data_init(int ac, char **av);
int				threading(t_ph **ph);
long long int	current_time(void);
t_ph			**philo_init(t_data *data);
void			print_status(t_ph *ph, const char *msg);
void			ft_usleep(t_ph *ph, long long time_eat);
void			free_all(t_ph **ph);
#endif