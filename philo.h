/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylang <ylang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 18:03:37 by ylang             #+#    #+#             */
/*   Updated: 2026/04/29 11:56:04 by ylang            ###   ########.fr       */
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
# define INT_MIN -2147483648
# define LONG_MAX 9223372036854775807
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
	bool			end_simulation;
	pthread_t		monitor_thread;
	t_fork			*forks;
	t_philo			*philos;
	pthread_mutex_t	state_mutex;
	pthread_mutex_t	print_mutex;
	bool			state_mutex_init;
	bool			print_mutex_init;
}					t_game;

// input valid check

int					ft_atoi(char *str);
bool				contains_only_digit(int argc, char **argv);

// init functions
int					init(t_game *game, int argc, char **argv);
int					init_mutexes(t_game *game);
int					init_forks(t_game *game);
int					init_philos(t_game *game);
void				assign_forks(int i, t_philo *philos, t_game *game,
						int count);
// philo routine/thread
void				*philo_routine(void *philo);
void				philo_eat(t_philo *philo);
void				philo_sleep(t_philo *philo);
void				philo_think(t_philo *philo);

// monitor thread
bool				is_simulation_over(t_game *game);
bool				check_philo_die(t_game *game_real, int count,
						int *full_count);
void				*monitor_die_or_full(void *game);

// print output
void				log_death(t_philo *philo);
void				log_action(t_philo *philo, char *msg);

// utils
long long			get_time_in_milliseconds(void);
void				precise_sleep(t_game *game, long long duration_ms);
// clean
void				cleanup_game(t_game *game);
#endif