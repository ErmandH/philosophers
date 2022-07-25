/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eharuni <eharuni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 18:39:25 by eharuni           #+#    #+#             */
/*   Updated: 2022/03/01 13:41:12 by eharuni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <sys/wait.h>
# include <signal.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/stat.h>

struct	s_rules;

typedef struct s_philosopher
{
	int					id;
	int					x_ate;
	int					left_fork_id;
	int					right_fork_id;
	long long			t_last_meal;
	struct s_rules		*rules;
	pthread_t			death_check;
	pid_t				proc_id;
}	t_philosopher;

typedef struct s_rules
{
	int					nb_philo;
	int					time_death;
	int					time_eat;
	int					time_sleep;
	int					nb_eat;
	int					dieded;
	long long			first_timestamp;
	sem_t				*meal_check;
	sem_t				*forks;
	sem_t				*writing;
	t_philosopher		philosophers[250];
}	t_rules;

int						error(char *str);
int						init_all(t_rules *rules, char **argv);
int						ft_atoi(const char *str);
void					print_status(t_rules *rules, int id, char *string);
long long				current_time(void);
long long				time_diff(long long past, long long pres);
void					ft_usleep(long long time, t_rules *rules);
int						processing(t_rules *rules);
void					exit_program(t_rules *rules);

#endif
