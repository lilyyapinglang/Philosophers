/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylang <ylang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 12:01:56 by ylang             #+#    #+#             */
/*   Updated: 2026/04/29 12:29:03 by ylang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	log_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->game->print_mutex);
	printf("%lld %d died\n", get_time_in_milliseconds()
		- philo->game->start_time_of_simulation, philo->philo_id);
	pthread_mutex_unlock(&philo->game->print_mutex);
}

/*
only one philo thread can printf at a time, lines are always complete and clean.
*/
void	log_action(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->game->print_mutex);
	pthread_mutex_lock(&philo->game->state_mutex);
	if (philo->game->end_simulation)
	{
		pthread_mutex_unlock(&philo->game->state_mutex);
		pthread_mutex_unlock(&philo->game->print_mutex);
		return ;
	}
	pthread_mutex_unlock(&philo->game->state_mutex);
	printf("%lld %d %s\n", get_time_in_milliseconds()
		- philo->game->start_time_of_simulation, philo->philo_id, msg);
	pthread_mutex_unlock(&philo->game->print_mutex);
}
