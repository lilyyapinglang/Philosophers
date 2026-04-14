
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

#define INT_MAX 2147483647

typedef struct s_fork
{
	int				fork_id;
	pthread_mutex_t	fork;
}					t_fork;

typedef struct s_philo
{
	int				philo_id;
	t_fork			*first_fork;
	t_fork			*second_fork;
	struct s_game	*game;
	long			last_meal_time;
	long			count_of_eat_times;
	bool			full;
	pthread_t		thread_id;
}					t_philo;

/*
 2147483647 millieseconds = 24.85 days
 so int is more than enough for this philo projet
 num_philo_must_eat default to -1 is not exist
 end_simulation =  a philo dead or everything is full
*/
typedef struct s_game
{
	int				num_philo_must_eat;
	int				number_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	long long		start_time_of_simulation;
	bool			num_of_full_philos;
	bool			end_simulation;
	pthread_t		monitor_thread;
	t_fork			*forks;
	t_philo			*philos;
	pthread_mutex_t	state_mutex;
	pthread_mutex_t	print_mutex;
}					t_game;

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

// int gettimeofday(struct timeval *restrict tp, void *restrict tzp);
long long	get_time_in_milliseconds(void)
{
	struct timeval	current_time;
	long long		time_io_millisecond;

	time_io_millisecond = 0;
	if (gettimeofday(&current_time, NULL) != -1)
		time_io_millisecond = ((long long)current_time.tv_sec) * 1000
			+ current_time.tv_usec / 1000;
	else
		return (-1);
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
		i++;
	}
	game->philos = philos;
	return (0);
}
/*
only one thread can printf at a time — lines are always complete and clean.
*/
void	log_action(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->game->print_mutex);
	if (!philo->game->end_simulation)
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
	// printf("%lld %ld is thinking\n", get_time_in_milliseconds()
	// 	- get_start_time(philo), philo->philo_id);
	think_time = philo->game->time_to_die - philo->game->time_to_eat
		- philo->game->time_to_sleep;
	if (think_time > 0)
		usleep((think_time / 2) * 1000);
	else
		usleep(500);
}

void	philo_sleep(t_philo *philo)
{
	if (is_simulation_over(philo->game))
		return ;
	log_action(philo, "is sleeping");
	// printf("%lld %ld is sleeping\n", get_time_in_milliseconds()
	// 	- get_start_time(philo), philo->philo_id);
	usleep(philo->game->time_to_sleep * 1000);
}

void	take_firt_fork_try(t_philo *philo)
{
	pthread_mutex_lock(&philo->first_fork->fork);
	if (is_simulation_over(philo->game))
	{
		pthread_mutex_unlock(&philo->first_fork->fork);
		return ;
	}
	log_action(philo, "has taken a fork");
	// printf("%lld %ld has take a fork %d\n", get_time_in_milliseconds()
	// 	- get_start_time(philo), philo->philo_id, philo->first_fork->fork_id);
}

void	try_take_second_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->second_fork->fork);
	if (is_simulation_over(philo->game))
	{
		pthread_mutex_unlock(&philo->first_fork->fork);
		pthread_mutex_unlock(&philo->second_fork->fork);
		return ;
	}
	log_action(philo, "has taken a fork");
	// printf("%lld %ld has take a fork %d\n", get_time_in_milliseconds()
	// 	- get_start_time(philo), philo->philo_id, philo->second_fork->fork_id);
}
void	philo_eat(t_philo *philo)
{
	if (is_simulation_over(philo->game))
		return ;
	take_firt_fork_try(philo);
	if (is_simulation_over(philo->game))
		return ;
	try_take_second_fork(philo);
	if (is_simulation_over(philo->game))
		return ;
	pthread_mutex_lock(&philo->game->state_mutex);
	philo->last_meal_time = get_time_in_milliseconds();
	pthread_mutex_unlock(&philo->game->state_mutex);
	log_action(philo, "is eating");
	// printf("%lld %ld is eating\n", get_time_in_milliseconds()
	// 	- get_start_time(philo), philo->philo_id);
	usleep(philo->game->time_to_eat * 1000);
	pthread_mutex_lock(&philo->game->state_mutex);
	philo->count_of_eat_times++;
	if (philo->game->num_philo_must_eat != -1)
		philo->full = (philo->count_of_eat_times >= philo->game->num_philo_must_eat) ? true : false;
	pthread_mutex_unlock(&philo->game->state_mutex);
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

	// is full ?
	philo_real = philo;
	if (philo_real->game->number_of_philo == 1)
	{
		log_action(philo, "has taken a fork");
		// printf("%lld 1 has taken a fork\n", get_time_in_milliseconds()
		// 	- get_start_time(philo_real));
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
void	start_philo_simulation(t_game *game)
{
	int	num;
	int	i;

	i = 0;
	num = game->number_of_philo;
	while (i < num)
	{
		if (pthread_create(&game->philos[i].thread_id, NULL, philo_routine,
				&(game->philos[i])) != 0)
		{
			printf("create philo thread %d failed \n", i);
			return ;
		}
		i++;
	}
}

// as philo (aka thread) does not communicate with each other
// and they(each thread) don't know if another thread is about to die
// later need to check ;
//|| (game.num_of_full_philos == game.number_of_philo);
void	*monitor_die_or_full(void *game)
{
	int			i;
	int			count;
	t_game		*game_real;
	int			full_philo_count;
	long long	last;
	bool		is_full;

	full_philo_count = 0;
	game_real = game;
	count = game_real->number_of_philo;
	i = 0;
	while (!is_simulation_over(game_real))
	{
		usleep(1000);
		i = 0;
		full_philo_count = 0;
		while (i < count)
		{
			pthread_mutex_lock(&game_real->state_mutex);
			last = game_real->philos[i].last_meal_time;
			is_full = game_real->philos[i].full;
			pthread_mutex_unlock(&game_real->state_mutex);
			if (get_time_in_milliseconds() - last > game_real->time_to_die)
			{
				log_action(&game_real->philos[i], "died");
				pthread_mutex_lock(&game_real->state_mutex);
				game_real->end_simulation = true;
				pthread_mutex_unlock(&game_real->state_mutex);
				return (NULL);
			}
			if (is_full)
				full_philo_count++;
			i++;
		}
		if (game_real->num_philo_must_eat != -1 && full_philo_count == count)
		{
			pthread_mutex_lock(&game_real->state_mutex);
			game_real->end_simulation = true;
			pthread_mutex_unlock(&game_real->state_mutex);
			// printf("everyone has eaten %d times, is full\n",
			// 	game_real->num_philo_must_eat);
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

// ./philo num_of_philo time_to_die time_to_eat time_to_sleep [num_of_times_must_eat]
// ./philo 2 100 100 100 5
int	main(int argc, char **argv)
{
	t_game		game;
	int			i;
	pthread_t	monitor_thread;

	// not enough argument
	if (!(argc == 5 || argc == 6))
	{
		printf("4 or 5 arguments are requied, you entered\
			%d argument. Please try again.\n",
				argc - 1);
		return (-1);
	}
	if (!contains_only_digit(argc, argv))
	{
		printf("Only accept non negative numbers as arguments,\
			please pass correct numbers. \n");
		return (-1);
	}
	game.number_of_philo = ft_atoi(argv[1]);
	if (game.number_of_philo == 0 || game.number_of_philo > 200)
	{
		printf("Consider to enter philosopher numbers from 1 to 200,you entered\
			%d\n",
				game.number_of_philo);
		return (-1);
	}
	game.time_to_die = ft_atoi(argv[2]);
	game.time_to_eat = ft_atoi(argv[3]);
	game.time_to_sleep = ft_atoi(argv[4]);
	if (game.time_to_die < 60 || game.time_to_eat < 60
		|| game.time_to_sleep < 60)
	{
		printf("Consider set time_to_die or time_to_eat or time_to_sleep to values more than 60 ms. \n");
		return (-1);
	}
	game.num_philo_must_eat = -1;
	if (argc == 6 && argv[5])
		game.num_philo_must_eat = ft_atoi(argv[5]);
	if (game.num_philo_must_eat == 0)
	{
		printf("number_of_times_each_philosopher_must_eat must be greater than 0 \n");
		return (-1);
	}
	game.start_time_of_simulation = get_time_in_milliseconds();
	game.num_of_full_philos = 0;
	game.end_simulation = false;
	init_forks(&game);
	init_philos(&game);
	pthread_mutex_init(&game.state_mutex, NULL);
	pthread_mutex_init(&game.print_mutex, NULL);
	// create a monitor thread
	pthread_create(&monitor_thread, NULL, monitor_die_or_full, &game);
	// create thread in each philo in the game
	start_philo_simulation(&game);
	i = 0;
	while (i < game.number_of_philo)
	{
		pthread_join(game.philos[i].thread_id, NULL);
		i++;
	}
	pthread_join(monitor_thread, NULL);
	pthread_mutex_destroy(&game.state_mutex);
	pthread_mutex_destroy(&game.print_mutex);
	// clear game, destroy things, free memories
	free(game.forks);
	free(game.philos);
}
