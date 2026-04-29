/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylang <ylang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 12:02:02 by ylang             #+#    #+#             */
/*   Updated: 2026/04/29 12:14:16 by ylang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init(t_game *game, int argc, char **argv)
{
	if (!(argc == 5 || argc == 6))
		return (printf("invalid number of argeuments\n"), -1);
	if (!contains_only_digit(argc, argv))
		return (printf("Arguments must be positive numbers&only digits\n"), -1);
	game->number_of_philo = ft_atoi(argv[1]);
	if (game->number_of_philo == 0 || game->number_of_philo > 200)
		return (printf("invalid number of philo, from 1 to 200 \n"), -1);
	game->time_to_die = ft_atoi(argv[2]);
	game->time_to_eat = ft_atoi(argv[3]);
	game->time_to_sleep = ft_atoi(argv[4]);
	if (game->time_to_die < 60 || game->time_to_eat < 60
		|| game->time_to_sleep < 60)
		return (printf("Timing values must be >= 60ms \n"), -1);
	game->num_philo_must_eat = -1;
	if (argc == 6 && argv[5])
		game->num_philo_must_eat = ft_atoi(argv[5]);
	if (game->num_philo_must_eat == 0)
		return (printf("Must eat count must be >= 1 \n"), -1);
	game->start_time_of_simulation = get_time_in_milliseconds();
	game->end_simulation = false;
	game->state_mutex_init = false;
	game->print_mutex_init = false;
	game->forks = NULL;
	game->philos = NULL;
	return (0);
}

int	init_mutexes(t_game *game)
{
	if (pthread_mutex_init(&game->state_mutex, NULL) != 0)
		return (-1);
	game->state_mutex_init = true;
	if (pthread_mutex_init(&game->print_mutex, NULL) != 0)
		return (-1);
	game->print_mutex_init = true;
	return (0);
}

int	init_forks(t_game *game)
{
	int		i;
	int		count;
	t_fork	*forks;

	i = 0;
	count = game->number_of_philo;
	forks = malloc(sizeof(t_fork) * count);
	if (!forks)
		return (-1);
	while (i < count)
	{
		forks[i].fork_id = i;
		if (pthread_mutex_init(&forks[i].fork, NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&forks[i].fork);
			free(forks);
			return (-1);
		}
		i++;
	}
	game->forks = forks;
	return (0);
}

int	init_philos(t_game *game)
{
	int		i;
	int		count;
	t_philo	*philos;

	i = 0;
	count = game->number_of_philo;
	philos = malloc(sizeof(t_philo) * count);
	if (!philos)
		return (-1);
	while (i < count)
	{
		philos[i].philo_id = i + 1;
		philos[i].last_meal_time = game->start_time_of_simulation;
		philos[i].count_of_eat_times = 0;
		philos[i].full = false;
		philos[i].game = game;
		assign_forks(i, philos, game, count);
		i++;
	}
	game->philos = philos;
	return (0);
}

/*
only the last philosopher: left=count-1, right=0
picks lower index first to break the circular wait
*/
void	assign_forks(int i, t_philo *philos, t_game *game, int count)
{
	int	left;
	int	right;

	left = i;
	right = (i + 1) % count;
	if (left < right)
	{
		philos[i].first_fork = &game->forks[left];
		philos[i].second_fork = &game->forks[right];
	}
	else
	{
		philos[i].first_fork = &game->forks[right];
		philos[i].second_fork = &game->forks[left];
	}
}
