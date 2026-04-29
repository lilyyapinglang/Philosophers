/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_details.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylang <ylang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 12:04:42 by ylang             #+#    #+#             */
/*   Updated: 2026/04/29 12:05:53 by ylang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_think(t_philo *philo)
{
	long long	think_time;

	if (is_simulation_over(philo->game))
		return ;
	log_action(philo, "is thinking");
	think_time = philo->game->time_to_die - philo->game->time_to_eat
		- philo->game->time_to_sleep;
	if (think_time > 20)
		precise_sleep(philo->game, think_time / 2);
}

void	philo_sleep(t_philo *philo)
{
	if (is_simulation_over(philo->game))
		return ;
	log_action(philo, "is sleeping");
	precise_sleep(philo->game, philo->game->time_to_sleep);
}

static bool	philo_grab_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->first_fork->fork);
	if (is_simulation_over(philo->game))
	{
		pthread_mutex_unlock(&philo->first_fork->fork);
		return (false);
	}
	log_action(philo, "has taken a fork");
	pthread_mutex_lock(&philo->second_fork->fork);
	if (is_simulation_over(philo->game))
	{
		pthread_mutex_unlock(&philo->first_fork->fork);
		pthread_mutex_unlock(&philo->second_fork->fork);
		return (false);
	}
	log_action(philo, "has taken a fork");
	return (true);
}

static void	philo_release_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->game->state_mutex);
	philo->count_of_eat_times++;
	if (philo->game->num_philo_must_eat != -1
		&& philo->count_of_eat_times >= philo->game->num_philo_must_eat)
		philo->full = true;
	pthread_mutex_unlock(&philo->game->state_mutex);
	pthread_mutex_unlock(&philo->first_fork->fork);
	pthread_mutex_unlock(&philo->second_fork->fork);
}

void	philo_eat(t_philo *philo)
{
	if (is_simulation_over(philo->game))
		return ;
	if (!philo_grab_forks(philo))
		return ;
	pthread_mutex_lock(&philo->game->state_mutex);
	philo->last_meal_time = get_time_in_milliseconds();
	pthread_mutex_unlock(&philo->game->state_mutex);
	log_action(philo, "is eating");
	precise_sleep(philo->game, philo->game->time_to_eat);
	philo_release_forks(philo);
}
