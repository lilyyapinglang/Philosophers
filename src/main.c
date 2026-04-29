/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylang <ylang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 12:01:53 by ylang             #+#    #+#             */
/*   Updated: 2026/04/29 12:56:49 by ylang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	cleanup_game(t_game *game)
{
	int	i;

	if (game->philos)
		free(game->philos);
	if (game->forks)
	{
		i = 0;
		while (i < game->number_of_philo)
			pthread_mutex_destroy(&game->forks[i++].fork);
		free(game->forks);
	}
	if (game->state_mutex_init)
		pthread_mutex_destroy(&game->state_mutex);
	if (game->print_mutex_init)
		pthread_mutex_destroy(&game->print_mutex);
}

/*
create threads for each philo, thread, attributes,
function_2_call,function_args
*/
int	start_philo_simulation(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->number_of_philo)
	{
		if (pthread_create(&game->philos[i].thread_id, NULL, philo_routine,
				&game->philos[i]) != 0)
		{
			while (--i >= 0)
				pthread_join(game->philos[i].thread_id, NULL);
			return (-1);
		}
		i++;
	}
	return (0);
}

void	wait_threads(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->number_of_philo)
		pthread_join(game->philos[i++].thread_id, NULL);
	pthread_join(game->monitor_thread, NULL);
}

/*
num_of_philo time_to_die time_to_eat
time_to_sleep
[num_of_times_must_eat]
./ philo 2 100 100 100 5
*/

int	main(int argc, char **argv)
{
	t_game	game;

	if (init(&game, argc, argv) != 0)
		return (-1);
	if (init_mutexes(&game) != 0)
		return (cleanup_game(&game), -1);
	if (init_forks(&game) != 0)
		return (cleanup_game(&game), -1);
	if (init_philos(&game) != 0)
		return (cleanup_game(&game), -1);
	if (pthread_create(&game.monitor_thread, NULL, monitor_die_or_full,
			&game) != 0)
		return (cleanup_game(&game), -1);
	if (start_philo_simulation(&game) != 0)
	{
		pthread_mutex_lock(&game.state_mutex);
		game.end_simulation = true;
		pthread_mutex_unlock(&game.state_mutex);
		pthread_join(game.monitor_thread, NULL);
		return (cleanup_game(&game), -1);
	}
	wait_threads(&game);
	cleanup_game(&game);
}
