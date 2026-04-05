#include "philo.h"
#include <stdio.h>

void	*philo_think(t_philo *philo)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	printf("%ld %ld is thinking\n", current_time.tv_usec, philo->philo_id);
	if (!usleep(philo->game->time))
		return (-1);
}
void	*philo_sleep(t_philo *philo)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	printf("%ld %ld is sleeping\n", current_time.tv_usec, philo->philo_id);
	if (!usleep(philo->game->time_to_sleep))
		return (-1);
}
void	*philo_eat(t_philo *philo)
{
	struct timeval	current_time;

	// philo take fork, lock 2 forks
	pthread_mutex_lock(&philo->left_fork->fork);
	gettimeofday(&current_time, NULL);
	printf("%ld %ld has take a fork %ld\n", current_time.tv_usec,
		philo->philo_id, (&philo->left_fork->fork_id));
	pthread_mutex_lock(&philo->right_fork->fork);
	gettimeofday(&current_time, NULL);
	printf("%ld %ld has take a fork %ld\n", current_time.tv_usec,
		philo->philo_id, (&philo->right_fork->fork_id));
	// philo eat
	gettimeofday(&current_time, NULL);
	printf("%ld %ld is eating\n", current_time.tv_usec, philo->philo_id);
	philo->count_of_eat_times++;
	if (!usleep(philo->game->time_to_eat))
		return (-1);
	// philo put down fork, unlock 2 forks
	pthread_mutex_unlock(&philo->left_fork->fork);
	pthread_mutex_unlock(&philo->right_fork->fork);
}

void	*philo_routine(t_philo *philo)
{
	// is full ?
	if (philo->full)
		return ;
	// eat
	philo_eat(philo);
	// philo sleep?
	philo_sleep(philo);
	// philo think ?
	philo_think(philo);
}
void	start_philo(t_game *game)
{
	pthread_t		threads[game->number_of_philo];
	pthread_mutex_t	mutext_FUEL;
	int				num;
	int				i;
	t_philo			philos[game->number_of_philo];
	int				forks[game->number_of_philo];

	// double linked list ?
	// create an array of philo;
	i = 0;
	while (i < num)
	{
		philos[i].count_of_eat_times = 0;
		philos[i].last_meal_time = 0;
		if (i == 0)
		{
			philos[i].left_fork = forks[num];
		}
		else
			philos[i].left_fork = forks[i - 1];
		philos[i].right_fork = forks[i];
	}
	// create threads for each philo,  thread, attributes, function_2_call,
	// function_args
	while (i < num)
	{
		pthread_create(&threads[i], NULL, philo_routine, &philos[i]);
		i++;
	}
	i = 0;
	while (i < num)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	// create an array of fork; order matters :
}

t_fork	*init_forks(t_fork *forks, long num_of_forks)
{
	int	i;

	i = 0;
	while (i < num_of_forks)
	{
		forks[i].fork_id = i;
		pthread_mutex_init(&forks[i].fork, NULL);
		i++;
	}
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
t_philo	*init_philos(t_game *game, t_philo *philos)
{
	int			i;
	pthread_t	philo_threads[game->number_of_philo];

	i = 0;
	while (i < game->number_of_philo)
	{
		philos[i].philo_id = i + 1;
		if (i == 0)
			philos[i].left_fork = &game->forks[game->number_of_philo];
		else
			philos[i].left_fork = &game->forks[i];
		philos[i].right_fork = &game->forks[i];
		philos[i].last_meal_time = 0;
		philos[i].count_of_eat_times = 0;
		philos[i].full = false;
		pthread_create(&philo_threads[i], NULL, philo_routine, &philos[i]);
		philos[i].thread_id = i;
		i++;
	}
}

// as philo (aka thread) does not communicate with each other
// and they(each thread) don't know if another thread is about to die
void	*monitor_die_or_full(t_game *game)
{
	struct timeval	current_time;
	int				i;
	int				count;

	count = game->num_of_full_philos;
	i = 0;
	// check current time
	// check each philo last eat time
	while (!game->end_simulation)
	{
		while (i < count)
		{
			gettimeofday(&current_time, NULL);
			if (game->philos[i].last_meal_time
				- current_time.tv_usec > game->time_to_die)
			{
				game->is_someone_died = true;
				game->end_simulation = true;
			}
			if (game->philos[i].full)
				game->num_of_full_philos++;
			i++;
		}
		if (game->num_of_full_philos == game->num_philo_must_eat)
			game->end_simulation = true;
	}
}
// ./philo num_of_philo time_to_die time_to_eat time_to_sleep [num_of_times_must_eat]
// ./philo 2 100 100 100 5
int	main(int argc, char **argv)
{
	t_game			game;
	struct timeval	current_time;
	t_philo			philos[game.number_of_philo];
	t_fork			forks[game.number_of_philo];

	if (argc < 5)
		// not enough argument
		return (1);
	// validity check
	// TODO atoi
	game.number_of_philo = atoi(argv[1]);
	game.time_to_die = atoi(argv[2]);
	game.time_to_eat = atoi(argv[3]);
	game.time_to_sleep = aoit(argv[4]);
	if (argv[5])
		game.num_philo_must_eat = atoi(argv[5]);
	// int gettimeofday(struct timeval *restrict tp, void *restrict tzp);
	game.start_time_of_simulation = gettimeofday(&current_time, NULL);
	game.is_someone_died = false;
	game.num_of_full_philos = 0;
	game.end_simulation = game.is_someone_died
		|| game.num_of_full_philos == game.number_of_philo;
	printf("seconds: %ld \n microsecond :%ld ", current_time.tv_sec,
		current_time.tv_usec);
	// init forks
	game.forks = init_forks(forks, game.number_of_philo);
	// init philos?
	game.philos = init_philos(philos, game.number_of_philo);
	pthread_create(&game.monitor_thread, NULL, monitor_die_or_full, &game);
	while (!game.end_simulation)
		start_philo(&game);
	pthread_join(game.monitor_thread, NULL);
}
