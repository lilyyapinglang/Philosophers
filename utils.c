/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylang <ylang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 18:01:00 by ylang             #+#    #+#             */
/*   Updated: 2026/04/14 18:41:04 by ylang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
	num of philo ,  >0
	time to sleep > 60ms , >0
	time to die > 60ms, >0
	time to eat >60 ms, >0
*/

int	ft_atoi(char *str)
{
	int	i;
	int	nbr;
	int	sign;

	nbr = 0;
	sign = 1;
	i = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nbr = (str[i] - '0') + nbr * 10;
		i++;
	}
	return (nbr * sign);
}


void	cleanup_game(t_game *game, int stage)
{
	int i;

	if (stage >= STAGE_THREADS)
	{
		i = 0;
		while (i < game->number_of_philo)
		{
			pthread_join(game->philos[i].thread_id, NULL);
			i++;
		}
	}
	pthread_join(game->monitor_thread, NULL);

	if (stage >= STAGE_MUTEXES)
	{
		pthread_mutex_destroy(&game->state_mutex);
		pthread_mutex_destroy(&game->print_mutex);
	}

	if(stage >=STAGE_FORKS && game->forks)
	{
		i=0;
		while(i<game->number_of_philo)
		{
			pthread_mutex_destroy(&game->forks[i].fork);
			i++;
		}
	}

	if(stage>=STAGE_PHILOS && game->philos)
		free(game->philos);
	if(stage>=STAGE_FORKS &&game->forks)
		free(game->forks);
}
