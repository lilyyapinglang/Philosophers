/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylang <ylang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 12:00:52 by ylang             #+#    #+#             */
/*   Updated: 2026/04/29 12:14:30 by ylang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(void *philo)
{
	t_philo	*philo_real;

	philo_real = philo;
	if (philo_real->game->number_of_philo == 1)
	{
		log_action(philo_real, "has taken a fork");
		while (!is_simulation_over(philo_real->game))
			precise_sleep(philo_real->game, 1000);
		return (NULL);
	}
	if (philo_real->philo_id % 2 == 0)
		precise_sleep(philo_real->game, philo_real->game->time_to_eat);
	while (!is_simulation_over(philo_real->game))
	{
		philo_eat(philo_real);
		philo_sleep(philo_real);
		philo_think(philo_real);
	}
	return (NULL);
}
