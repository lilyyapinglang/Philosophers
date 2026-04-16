/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilypad <lilypad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 18:01:04 by ylang             #+#    #+#             */
/*   Updated: 2026/04/16 20:11:28 by lilypad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int	ft_atoi(char *str)
{
	int	i;
	long nbr;
	int	sign;
	int digit;

	nbr = 0;
	sign = 1;
	i = 0;
	if(!str)
		return 0;
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
		digit = str[i]-'0';
		
		if(nbr>(INT_MAX - digit)/10)
		{
			if(sign==1)
				return INT_MAX;
			return INT_MIN;
		}
		nbr = digit + nbr * 10;
		i++;
	}
	return (int)(nbr * sign);
}

void	join_philo_threads(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->number_of_philo)
	{
		pthread_join(game->philos[i].thread_id, NULL);
		i++;
	}
}

void    cleanup_game(t_game *game, int stage)
{
    int i;

    if (stage >= STAGE_MUTEXES)
    {
        pthread_mutex_destroy(&game->state_mutex);
        pthread_mutex_destroy(&game->print_mutex);
		pthread_mutex_destroy(&game->meal_mutex);
    }
    if (stage >= STAGE_FORKS && game->forks)
    {
        i = 0;
        while (i < game->number_of_philo)
            pthread_mutex_destroy(&game->forks[i++].fork);
    }
    if (stage >= STAGE_PHILOS && game->philos)
        free(game->philos);
    if (stage >= STAGE_FORKS && game->forks)
        free(game->forks);
}
// int gettimeofday(struct timeval *restrict tp, void *restrict tzp);
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

long long	get_start_time(t_philo *philo)
{
	return (philo->game->start_time_of_simulation);
}

bool	is_simulation_over(t_game *game)
{
	bool	result;

	pthread_mutex_lock(&game->state_mutex);
	result = game->end_simulation;
	pthread_mutex_unlock(&game->state_mutex);
	return (result);
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
			return (-1);
		i++;
	}
	game->forks = forks;
	return (0);
}

void	assign_forks(int i, t_philo *philos, t_game *game, int count)
{
	if (i % 2 == 0)
	{
		philos[i].first_fork = &game->forks[i];
		if (i == 0)
			philos[i].second_fork = &game->forks[count - 1];
		else
			philos[i].second_fork = &game->forks[i - 1];
	}
	else
	{
		philos[i].first_fork = &game->forks[i - 1];
		philos[i].second_fork = &game->forks[i];
	}
}
/*
	fork assign strategy:
	id = odd set the first fork as the left one
	id = sevent, set first fork to right one
*/
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
only one philo thread can printf at a time — lines are always complete and clean.
*/

void log_action(t_philo *philo, char *msg)
{
    t_game *game = philo->game;

    pthread_mutex_lock(&game->print_mutex);

    if (!game->end_simulation)
    {
        printf("%lld %d %s\n",
            get_time_in_milliseconds() - game->start_time_of_simulation,
            philo->philo_id,
            msg);
    }

    pthread_mutex_unlock(&game->print_mutex);
}

void	philo_think(t_philo *philo)
{
	long long	think_time;

	log_action(philo, "is thinking");
	think_time = philo->game->time_to_die - philo->game->time_to_eat
		- philo->game->time_to_sleep;
	if (think_time > 0)
		usleep((think_time / 2) * 1000);
	else
		usleep(500);
}

void	philo_sleep(t_philo *philo)
{
	
	log_action(philo, "is sleeping");
	usleep(philo->game->time_to_sleep * 1000);
}

void philo_eat(t_philo *philo)
{
    t_game *game = philo->game;

    pthread_mutex_lock(&philo->first_fork->fork);
    log_action(philo, "has taken a fork");

    pthread_mutex_lock(&philo->second_fork->fork);
    log_action(philo, "has taken a fork");

    pthread_mutex_lock(&game->meal_mutex);
    philo->last_meal_time = get_time_in_milliseconds();
    pthread_mutex_unlock(&game->meal_mutex);

    log_action(philo, "is eating");
    usleep(game->time_to_eat * 1000);

    pthread_mutex_lock(&game->meal_mutex);

    philo->count_of_eat_times++;

    if (game->num_philo_must_eat != -1 &&
        philo->count_of_eat_times >= game->num_philo_must_eat)
        philo->full = true;

    pthread_mutex_unlock(&game->meal_mutex);

    pthread_mutex_unlock(&philo->first_fork->fork);
    pthread_mutex_unlock(&philo->second_fork->fork);
}

/*
To prevent contension,
	philos who has even id wait for a little bit late 1ms to take their first fork.
*/
void	*philo_routine(void *philo)
{
	t_philo	*philo_real;

	philo_real = philo;
	if (philo_real->game->number_of_philo == 1)
	{
		log_action(philo, "has taken a fork");
		while (!is_simulation_over(philo_real->game))
			usleep(1000);
		return (NULL);
	}
	if (philo_real->philo_id % 2 == 0)
		usleep(1000);
	while (!is_simulation_over(philo_real->game))
	{
		philo_eat(philo_real);
		philo_sleep(philo_real);
		philo_think(philo_real);
	}
	return (NULL);
}

// create threads for each philo,  thread, attributes, function_2_call,
// function_args

int start_philo_simulation(t_game *game)
{
    int i;

    i = 0;
    while (i < game->number_of_philo)
    {
        if (pthread_create(&game->philos[i].thread_id, NULL,
                philo_routine, &game->philos[i]) != 0)
        {
            while (--i >= 0)
                pthread_join(game->philos[i].thread_id, NULL);
            return (-1);
        }
        i++;
    }
    return (0);
}

bool check_philo_die(int i, t_game *game_real, int count, int *full_count)
{
    long long last_eat;
	bool full;
    while (i < count)
    {
        pthread_mutex_lock(&game_real->meal_mutex);
        last_eat = game_real->philos[i].last_meal_time;
		full = game_real->philos[i].full;
        pthread_mutex_unlock(&game_real->meal_mutex);

        if (get_time_in_milliseconds() - last_eat > game_real->time_to_die)
        {
            log_action(&game_real->philos[i], "died");

            pthread_mutex_lock(&game_real->state_mutex);
            game_real->end_simulation = true;
            pthread_mutex_unlock(&game_real->state_mutex);

            return (true);
        }
		if (full)
            (*full_count)++;
        i++;
    }
    return (false);
}
/*
	as philo (aka thread) does not communicate with each other
	and they(each thread) don't know if another thread is about to die
*/
void	*monitor_die_or_full(void *game)
{
	int		i;
	int		count;
	t_game	*game_real;
	int		full_philo_count;

	full_philo_count = 0;
	game_real = game;
	count = game_real->number_of_philo;
	i = 0;
	while (!is_simulation_over(game_real))
	{
		usleep(1000);
		i = 0;
		full_philo_count = 0;
		if (check_philo_die(i, game_real, count, &full_philo_count))
			return (NULL);
		if (game_real->num_philo_must_eat != -1 && full_philo_count == count)
		{
    		pthread_mutex_lock(&game_real->state_mutex);
    		game_real->end_simulation = true;
    		pthread_mutex_unlock(&game_real->state_mutex);
			pthread_mutex_lock(&game_real->print_mutex);
			printf("simulation ended\n");
			pthread_mutex_unlock(&game_real->print_mutex);
    		return (NULL);
		}
	}
	return (NULL);
}

bool	contains_only_digit(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] > '9' || argv[i][j] < '0')
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}
int	init(t_game *game, int argc, char **argv)
{
	if (!(argc == 5 || argc == 6))
		return (printf("invalid number of argeuments\n"), -1);
	if (!contains_only_digit(argc, argv))
		return (printf("Arguments must be positive numbers\n"), -1);
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
		return (printf("Must eat count must be >= 0 \n"), -1);
	game->start_time_of_simulation = get_time_in_milliseconds();
	game->end_simulation = false;
	game->forks = NULL;
	game->philos = NULL;
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
./philo num_of_philo time_to_die time_to_eat time_to_sleep [num_of_times_must_eat]
./ philo 2 100 100 100 5
*/
int	main(int argc, char **argv)
{
	t_game	game;
	int		stage;

	stage = STAGE_NONE;
	if (init(&game, argc, argv) != 0)
		return (-1);
	if (init_forks(&game) != 0)
		return (cleanup_game(&game, stage), -1);
	stage = STAGE_FORKS;
	if (init_philos(&game) != 0)
		return (cleanup_game(&game, stage), -1);
	stage = STAGE_PHILOS;
	if (pthread_mutex_init(&game.state_mutex, NULL) != 0
		|| pthread_mutex_init(&game.print_mutex, NULL) != 0 || pthread_mutex_init(&game.meal_mutex, NULL) != 0)
		return (cleanup_game(&game, stage), -1);
	stage = STAGE_MUTEXES;
	if (pthread_create(&game.monitor_thread, NULL, monitor_die_or_full,
			&game) != 0)
		return (cleanup_game(&game, stage), -1);
	if (start_philo_simulation(&game) != 0)
		return (cleanup_game(&game, stage), -1);
	stage = STAGE_THREADS;
	wait_threads(&game);
	cleanup_game(&game, stage);
}
