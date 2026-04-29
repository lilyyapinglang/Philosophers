/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylang <ylang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 12:04:29 by ylang             #+#    #+#             */
/*   Updated: 2026/04/29 12:28:55 by ylang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

bool	is_simulation_over(t_game *game)
{
	bool	result;

	pthread_mutex_lock(&game->state_mutex);
	result = game->end_simulation;
	pthread_mutex_unlock(&game->state_mutex);
	return (result);
}

static bool	set_philo_dead(t_game *game, int i)
{
	pthread_mutex_lock(&game->state_mutex);
	if (game->end_simulation)
	{
		pthread_mutex_unlock(&game->state_mutex);
		return (true);
	}
	game->end_simulation = true;
	pthread_mutex_unlock(&game->state_mutex);
	log_death(&game->philos[i]);
	return (true);
}

/*
as philo (aka thread) does not communicate with each other
and	they(each thread) don't know if another thread is about to die
*/
bool	check_philo_die(t_game *game_real, int count, int *full_count)
{
	long long	last_eat;
	bool		full;
	int			i;

	i = 0;
	while (i < count)
	{
		pthread_mutex_lock(&game_real->state_mutex);
		last_eat = game_real->philos[i].last_meal_time;
		full = game_real->philos[i].full;
		pthread_mutex_unlock(&game_real->state_mutex);
		if (get_time_in_milliseconds() - last_eat >= game_real->time_to_die)
			return (set_philo_dead(game_real, i));
		if (full)
			(*full_count)++;
		i++;
	}
	return (false);
}

void	*monitor_die_or_full(void *game)
{
	int		count;
	t_game	*game_real;
	int		full_philo_count;

	full_philo_count = 0;
	game_real = game;
	count = game_real->number_of_philo;
	while (!is_simulation_over(game_real))
	{
		usleep(1000);
		full_philo_count = 0;
		if (check_philo_die(game_real, count, &full_philo_count))
			return (NULL);
		if (game_real->num_philo_must_eat != -1 && full_philo_count == count)
		{
			pthread_mutex_lock(&game_real->state_mutex);
			game_real->end_simulation = true;
			pthread_mutex_unlock(&game_real->state_mutex);
			return (NULL);
		}
	}
	return (NULL);
}
