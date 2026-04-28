#include "philo.h"

int	ft_atoi(char *str)
{
	int		i;
	long	nbr;
	int		sign;
	int		digit;

	nbr = 0;
	sign = 1;
	i = 0;
	if (!str)
		return (0);
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
		digit = str[i] - '0';
		if (nbr > (INT_MAX - digit) / 10)
		{
			if (sign == 1)
				return (INT_MAX);
			return (INT_MIN);
		}
		nbr = digit + nbr * 10;
		i++;
	}
	return (int)(nbr * sign);
}

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
		// only the last philosopher: left=count-1, right=0
		// picks lower index first to break the circular wait
		philos[i].first_fork = &game->forks[right];
		philos[i].second_fork = &game->forks[left];
	}
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
void	precise_sleep(t_game *game, long long duration_ms)
{
	long long	start;
	long long	elapsed;

	start = get_time_in_milliseconds();
	while (!is_simulation_over(game))
	{
		elapsed = get_time_in_milliseconds() - start;
		if (elapsed >= duration_ms)
			break ;
		usleep(100); // smaller granularity
	}
}
/*
only one philo thread can printf at a time — lines are always complete and clean.
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
	else
		precise_sleep(philo->game, 1);
}

void	philo_sleep(t_philo *philo)
{
	if (is_simulation_over(philo->game))
		return ;
	log_action(philo, "is sleeping");
	precise_sleep(philo->game, philo->game->time_to_sleep);
}

void	philo_eat(t_philo *philo)
{
	t_game	*game;

	if (is_simulation_over(philo->game))
		return ;
	game = philo->game;
	pthread_mutex_lock(&philo->first_fork->fork);
	if (is_simulation_over(philo->game))
	{
		pthread_mutex_unlock(&philo->first_fork->fork);
		return ;
	}
	log_action(philo, "has taken a fork");
	pthread_mutex_lock(&philo->second_fork->fork);
	if (is_simulation_over(philo->game))
	{
		pthread_mutex_unlock(&philo->first_fork->fork);
		pthread_mutex_unlock(&philo->second_fork->fork);
		return ;
	}
	log_action(philo, "has taken a fork");
	pthread_mutex_lock(&game->state_mutex);
	philo->last_meal_time = get_time_in_milliseconds();
	pthread_mutex_unlock(&game->state_mutex);
	log_action(philo, "is eating");
	precise_sleep(game, game->time_to_eat);
	pthread_mutex_lock(&game->state_mutex);
	philo->count_of_eat_times++;
	if (game->num_philo_must_eat != -1
		&& philo->count_of_eat_times >= game->num_philo_must_eat)
		philo->full = true;
	pthread_mutex_unlock(&game->state_mutex);
	pthread_mutex_unlock(&philo->first_fork->fork);
	pthread_mutex_unlock(&philo->second_fork->fork);
}

void	*philo_routine(void *philo)
{
	t_philo	*philo_real;

	philo_real = philo;
	if (philo_real->game->number_of_philo == 1)
	{
		log_action(philo, "has taken a fork");
		while (!is_simulation_over(philo_real->game))
			precise_sleep(philo_real->game, 1000);
		return (NULL);
	}
	if (philo_real->philo_id % 2 == 0)
		precise_sleep(philo_real->game, philo_real->game->time_to_eat / 2);
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
void	log_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->game->print_mutex);
	printf("%lld %d died\n", get_time_in_milliseconds()
		- philo->game->start_time_of_simulation, philo->philo_id);
	pthread_mutex_unlock(&philo->game->print_mutex);
}

bool	check_philo_die(int i, t_game *game_real, int count, int *full_count)
{
	long long	last_eat;
	bool		full;

	while (i < count)
	{
		pthread_mutex_lock(&game_real->state_mutex);
		last_eat = game_real->philos[i].last_meal_time;
		full = game_real->philos[i].full;
		pthread_mutex_unlock(&game_real->state_mutex);
		if (get_time_in_milliseconds() - last_eat >= game_real->time_to_die)
		{
			pthread_mutex_lock(&game_real->state_mutex);
			if (!game_real->end_simulation)
			{
				game_real->end_simulation = true;
				pthread_mutex_unlock(&game_real->state_mutex);
				log_death(&game_real->philos[i]);
			}
			else
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
		usleep(500); // or even 200
		i = 0;
		full_philo_count = 0;
		if (check_philo_die(i, game_real, count, &full_philo_count))
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
	game->state_mutex_init = false;
	game->print_mutex_init = false;
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

	if (init(&game, argc, argv) != 0)
		return (-1);
	if (pthread_mutex_init(&game.state_mutex, NULL) != 0)
		return (cleanup_game(&game), -1);
	game.state_mutex_init = true;
	if (pthread_mutex_init(&game.print_mutex, NULL) != 0)
		return (cleanup_game(&game), -1);
	game.print_mutex_init = true;
	if (init_forks(&game) != 0)
		return (cleanup_game(&game), -1);
	if (init_philos(&game) != 0)
		return (cleanup_game(&game), -1);
	if (pthread_create(&game.monitor_thread, NULL, monitor_die_or_full,
			&game) != 0)
		return (cleanup_game(&game), -1);
	if (start_philo_simulation(&game) != 0)
		return (cleanup_game(&game), -1);
	wait_threads(&game);
	cleanup_game(&game);
}
