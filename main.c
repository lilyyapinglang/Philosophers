#include "philo.h"
#include <stdio.h>

long long	get_time_in_milliseconds(void)
{
	struct timeval	current_time;
	long long		time_io_millisecond;

	time_io_millisecond = 0;
	// int gettimeofday(struct timeval *restrict tp, void *restrict tzp);
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
	// TODO safe_malloc
	forks = malloc(sizeof(t_fork) * count);
	while (i < count)
	{
		forks[i].fork_id = i;
		pthread_mutex_init(&forks[i].fork, NULL);
		i++;
	}
	game->forks = forks;
	return (0);
}

/*
typedef struct s_philo
{
	int		philo_id;
	t_fork	*left_fork;
	t_fork	*right_fork;
	long last_meal_time; // time passed from last meal
	long	count_of_eat_times;
	bool	full;
	pthread_t thread_id; // a philo is a thread
	t_game	*game;
}			t_philo;
*/
int	init_philos(t_game *game)
{
	int			i;
	pthread_t	*philo_threads;
	int			count;
	t_philo		*philos;

	i = 0;
	count = game->number_of_philo;
	philos = malloc(sizeof(t_philo) * count);
	philo_threads = malloc(sizeof(pthread_t) * count);
	while (i < count)
	{
		philos[i].philo_id = i + 1;
		philos[i].last_meal_time = game->start_time_of_simulation;
		philos[i].count_of_eat_times = 0;
		philos[i].full = false;
		philos[i].game = game;
		// philos[i].thread_id = philo_threads[i]; thread_id will have unitialsied values which is not correct.
		if (i % 2 == 0)
		{
			// id = odd set the first fork as the left one
			philos[i].first_fork = &game->forks[i];
			if (i == 0)
				philos[i].second_fork = &game->forks[count - 1];
			else
				philos[i].second_fork = &game->forks[i - 1];
		}
		else // id =event, set first fork to right one
		{
			philos[i].first_fork = &game->forks[i - 1];
			philos[i].second_fork = &game->forks[i];
		}
		i++;
	}
	game->philos = philos;
	// philos->game = game;
	return (0);
}

void	philo_think(t_philo *philo)
{
	if (is_simulation_over(philo->game))
		return ;
	printf("%lld %ld is thinking\n", get_time_in_milliseconds()
		- get_start_time(philo), philo->philo_id);
}
void	philo_sleep(t_philo *philo)
{
	if (is_simulation_over(philo->game))
		return ;
	printf("%lld %ld is sleeping\n", get_time_in_milliseconds()
		- get_start_time(philo), philo->philo_id);
	usleep(philo->game->time_to_sleep * 1000);
}

void	philo_eat(t_philo *philo)
{
	// philo take fork, lock 2 forks
	//  if philo is even, pick right first
	if (is_simulation_over(philo->game))
		return ;
	pthread_mutex_lock(&philo->first_fork->fork);
	if (!is_simulation_over(philo->game))
	{
		pthread_mutex_unlock(&philo->first_fork->fork);
		return ;
	}
	printf("%lld %ld has take a fork %d\n", get_time_in_milliseconds()
		- get_start_time(philo), philo->philo_id, philo->first_fork->fork_id);
	pthread_mutex_lock(&philo->second_fork->fork);
	if (!is_simulation_over(philo->game))
	{
		pthread_mutex_unlock(&philo->first_fork->fork);
		pthread_mutex_unlock(&philo->second_fork->fork);
		return ;
	}
	printf("%lld %ld has take a fork %d\n", get_time_in_milliseconds()
		- get_start_time(philo), philo->philo_id, philo->second_fork->fork_id);
	// philo eat
	pthread_mutex_lock(&philo->game->state_mutex);
	philo->last_meal_time = get_time_in_milliseconds();
	pthread_mutex_unlock(&philo->game->state_mutex);
	printf("%lld %ld is eating\n", get_time_in_milliseconds()
		- get_start_time(philo), philo->philo_id);
	usleep(philo->game->time_to_eat * 1000);
	pthread_mutex_lock(&philo->game->state_mutex);
	philo->count_of_eat_times++;
	philo->full = (philo->count_of_eat_times >= philo->game->num_philo_must_eat) ? true : false;
	pthread_mutex_unlock(&philo->game->state_mutex);
	pthread_mutex_unlock(&philo->first_fork->fork);
	pthread_mutex_unlock(&philo->second_fork->fork);
}

void	*philo_routine(void *philo)
{
	t_philo	*philo_1;

	// is full ?
	philo_1 = philo;
	// if (philo_1->full)
	// 	return (NULL);
	while (!is_simulation_over(philo_1->game))
	{
		// eat
		philo_eat(philo_1);
		// philo sleep?
		philo_sleep(philo_1);
		// philo think ?
		philo_think(philo_1);
	}
	return (NULL);
}
void	start_philo(t_game *game)
{
	int	num;
	int	i;

	// create an array of philo;
	i = 0;
	num = game->number_of_philo;
	// create threads for each philo,  thread, attributes, function_2_call,
	// function_args
	while (i < num)
	{
		if (pthread_create(&game->philos[i].thread_id, NULL, philo_routine,
				&(game->philos[i])) != 0)
			printf("create philo thread %d failed \n", i);
		i++;
	}
}
// as philo (aka thread) does not communicate with each other
// and they(each thread) don't know if another thread is about to die
// later need to check ;
// game.is_someone_died
//|| (game.num_of_full_philos == game.number_of_philo);
void	*monitor_die_or_full(void *game)
{
	int			i;
	int			count;
	t_game		*game_1;
	int			full_count;
	long long	last;
	bool		is_full;

	full_count = 0;
	game_1 = game;
	count = game_1->number_of_philo;
	i = 0;
	// check current time
	// check each philo last eat time
	while (!game_1->end_simulation)
	{
		i = 0;
		full_count = 0;
		while (i < count)
		{
			pthread_mutex_lock(&game_1->state_mutex);
			last = game_1->philos[i].last_meal_time;
			is_full = game_1->philos[i].full;
			pthread_mutex_unlock(&game_1->state_mutex);
			if (get_time_in_milliseconds() - last > game_1->time_to_die)
			{
				// game_1->is_someone_died = true;
				printf("%lld %ld is died\n", get_time_in_milliseconds()
					- game_1->start_time_of_simulation,
					game_1->philos[i].philo_id);
				pthread_mutex_lock(&game_1->state_mutex);
				game_1->end_simulation = true;
				pthread_mutex_unlock(&game_1->state_mutex);
				return (NULL);
			}
			if (is_full)
				full_count++;
			i++;
		}
		if (full_count == count)
		{
			pthread_mutex_lock(&game_1->state_mutex);
			game_1->end_simulation = true;
			pthread_mutex_unlock(&game_1->state_mutex);
			printf("everyone has eaten %ld times, is full\n",
				game_1->num_philo_must_eat);
			return (NULL);
		}
	}
	return (NULL);
}

// ./philo num_of_philo time_to_die time_to_eat time_to_sleep [num_of_times_must_eat]
// ./philo 2 100 100 100 5
int	main(int argc, char **argv)
{
	t_game		game;
	int			i;
	pthread_t	monitor_thread;

	if (argc < 5)
		// not enough argument
		return (1);
	// validity check
	// TODO atoi
	game.number_of_philo = atoi(argv[1]);
	game.time_to_die = atoi(argv[2]);
	game.time_to_eat = atoi(argv[3]);
	game.time_to_sleep = atoi(argv[4]);
	if (argc == 6 && argv[5])
		game.num_philo_must_eat = atoi(argv[5]);
	game.start_time_of_simulation = get_time_in_milliseconds();
	game.is_someone_died = false;
	game.num_of_full_philos = 0;
	game.end_simulation = false;
	printf("start_time_of_simulation :%lld \n", game.start_time_of_simulation);
	// init forks
	init_forks(&game);
	// init philos?
	init_philos(&game);
	pthread_mutex_init(&game.state_mutex, NULL);
	pthread_mutex_init(&game.print_mutex, NULL);
	// create a monitor thread
	pthread_create(&monitor_thread, NULL, monitor_die_or_full, &game);
	// create thread in each philo in the game
	start_philo(&game);
	i = 0;
	while (i < game.number_of_philo)
	{
		pthread_join(game.philos[i].thread_id, NULL);
		i++;
	}
	pthread_join(monitor_thread, NULL);
	pthread_mutex_destroy(&game.state_mutex);
	pthread_mutex_destroy(&game.print_mutex);
	// clean_game, destroy things, free memories
}
