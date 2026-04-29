/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylang <ylang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 12:00:56 by ylang             #+#    #+#             */
/*   Updated: 2026/04/29 16:55:59 by ylang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

/*
int			gettimeofday(struct timeval *restrict tp, void *restrict tzp);
*/

long long	get_time_in_milliseconds(void)
{
	struct timeval	current_time;
	long long		time_io_millisecond;

	time_io_millisecond = 0;
	if (gettimeofday(&current_time, NULL) != 0)
		return (0);
	time_io_millisecond = ((long long)current_time.tv_sec) * 1000
		+ current_time.tv_usec / 1000;
	return (time_io_millisecond);
}

/*
if remaining time is long, i try to usleep half first,
if remaining time is short, i try to usleep at 0.2ms granularity
*/
void	precise_sleep(t_game *game, long long duration_ms)
{
	long long	start;
	long long	elapsed;
	long long	remaining;

	start = get_time_in_milliseconds();
	while (!is_simulation_over(game))
	{
		elapsed = get_time_in_milliseconds() - start;
		if (elapsed >= duration_ms)
			break ;
		remaining = duration_ms - elapsed;
		if (remaining > 10)
			usleep(remaining * 500);
		usleep(200);
	}
}
