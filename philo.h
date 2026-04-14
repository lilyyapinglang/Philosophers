/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylang <ylang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 18:03:37 by ylang             #+#    #+#             */
/*   Updated: 2026/04/14 18:40:42 by ylang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define INT_MAX 2147483647
# define STAGE_NONE 0
# define STAGE_FORKS 1
# define STAGE_PHILOS 2
# define STAGE_MUTEXES 3
# define STAGE_THREADS 4

typedef struct s_fork
{
	int				fork_id;
	pthread_mutex_t	fork;
}					t_fork;

typedef struct s_philo
{
	int				philo_id;
	t_fork			*first_fork;
	t_fork			*second_fork;
	struct s_game	*game;
	long			last_meal_time;
	long			count_of_eat_times;
	bool			full;
	pthread_t		thread_id;
}					t_philo;

/*
 2147483647 millieseconds = 24.85 days
 so int is more than enough for this philo projet
 num_philo_must_eat default to -1 is not exist
 end_simulation =  a philo dead or everything is full
*/
typedef struct s_game
{
	int				num_philo_must_eat;
	int				number_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	long long		start_time_of_simulation;
	bool			num_of_full_philos;
	bool			end_simulation;
	pthread_t		monitor_thread;
	t_fork			*forks;
	t_philo			*philos;
	pthread_mutex_t	state_mutex;
	pthread_mutex_t	print_mutex;
}					t_game;

int					ft_atoi(char *str);
void				cleanup_game(t_game *game, int stage);

#endif