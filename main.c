#include "philo.h"
#include <stdio.h>

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
		philos[i].last_meal_time = 0;
		philos[i].count_of_eat_times = 0;
		philos[i].full = false;
		philos[i].thread_id = philo_threads[i];
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
	philos->game = game;
	return (0);
}
void	philo_think(t_philo *philo)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	printf("%ld %ld is thinking\n", current_time.tv_usec, philo->philo_id);
}
void	philo_sleep(t_philo *philo)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	printf("%ld %ld is sleeping\n", current_time.tv_usec, philo->philo_id);
	if (!usleep(philo->game->time_to_sleep))
		return ;
}
void	philo_eat(t_philo *philo)
{
	struct timeval	current_time;

	// philo take fork, lock 2 forks
	//  if philo is even, pick right first
	pthread_mutex_lock(&philo->first_fork->fork);
	gettimeofday(&current_time, NULL);
	printf("%ld %ld has take a fork %d\n", current_time.tv_usec,
		philo->philo_id, philo->first_fork->fork_id);
	pthread_mutex_lock(&philo->second_fork->fork);
	gettimeofday(&current_time, NULL);
	printf("%ld %ld has take a fork %d\n", current_time.tv_usec,
		philo->philo_id, philo->second_fork->fork_id);
	// philo eat
	gettimeofday(&current_time, NULL);
	printf("%ld %ld is eating\n", current_time.tv_usec, philo->philo_id);
	philo->count_of_eat_times++;
	printf(" %ld has eaten %ld times \n", philo->philo_id,
		philo->count_of_eat_times);
	usleep(philo->game->time_to_eat); // need to check usleep return value
	printf(" %ld time to eat is %ld \n", philo->philo_id,
		philo->game->time_to_eat);
	gettimeofday(&current_time, NULL);
	printf("%ld %ld has finished eating\n", current_time.tv_usec,
		philo->philo_id);
	// philo put down fork, unlock 2 forks
	printf("%ld try to put down fork \n. ", philo->philo_id);
	pthread_mutex_unlock(&philo->first_fork->fork);
	pthread_mutex_unlock(&philo->second_fork->fork);
}

void	*philo_routine(void *philo)
{
	t_philo	*philo_1;

	// is full ?
	philo_1 = (t_philo *)philo;
	if (philo_1->full)
		return (NULL);
	// eat
	philo_eat(philo_1);
	// philo sleep?
	philo_sleep(philo_1);
	// philo think ?
	philo_think(philo_1);
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
				(void *)&(game->philos[i])) != 0)
			printf("create philo thread %d failed \n", i);
		i++;
	}
}

// as philo (aka thread) does not communicate with each other
// and they(each thread) don't know if another thread is about to die
// int	monitor_die_or_full(t_game *game)
// {
// 	struct timeval	current_time;
// 	int				i;
// 	int				count;

// 	count = game->num_of_full_philos;
// 	i = 0;
// 	// check current time
// 	// check each philo last eat time
// 	while (!game->end_simulation)
// 	{
// 		while (i < count)
// 		{
// 			gettimeofday(&current_time, NULL);
// 			if (game->philos[i].last_meal_time
// 				- current_time.tv_usec > game->time_to_die)
// 			{
// 				game->is_someone_died = true;
// 				game->end_simulation = true;
// 			}
// 			if (game->philos[i].full)
// 				game->num_of_full_philos++;
// 			i++;
// 		}
// 		if (game->num_of_full_philos == game->num_philo_must_eat)
// 			game->end_simulation = true;
// 	}
// 	return (0);
// }
// ./philo num_of_philo time_to_die time_to_eat time_to_sleep [num_of_times_must_eat]
// ./philo 2 100 100 100 5
int	main(int argc, char **argv)
{
	t_game			game;
	struct timeval	current_time;
	int				i;

	// t_philo			philos[game.number_of_philo];
	// t_fork			forks[game.number_of_philo];
	if (argc < 5)
		// not enough argument
		return (1);
	// validity check
	// TODO atoi
	game.number_of_philo = atoi(argv[1]);
	game.time_to_die = atoi(argv[2]);
	game.time_to_eat = atoi(argv[3]);
	game.time_to_sleep = atoi(argv[4]);
	if (argv[5])
		game.num_philo_must_eat = atoi(argv[5]);
	// int gettimeofday(struct timeval *restrict tp, void *restrict tzp);
	game.start_time_of_simulation = gettimeofday(&current_time, NULL);
	game.is_someone_died = false;
	game.num_of_full_philos = 0;
	game.end_simulation = game.is_someone_died
		|| game.num_of_full_philos == game.number_of_philo;
	printf("seconds: %ld , microsecond :%ld \n", current_time.tv_sec,
		current_time.tv_usec);
	// init forks
	init_forks(&game);
	// init philos?
	init_philos(&game);
	// create a monitor thread
	// pthread_create(&game.monitor_thread, NULL, monitor_die_or_full,
	//	&game);
	while (!game.end_simulation)
		// create thread in each philo in the game
		start_philo(&game);
	i = 0;
	while (i < game.number_of_philo)
	{
		pthread_join(game.philos[i].thread_id, NULL);
		i++;
	}
	pthread_join(game.monitor_thread, NULL);
	// clean_game, destroy things, free memories
}
