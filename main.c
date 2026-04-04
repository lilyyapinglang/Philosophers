#include "philo.h"
#include <stdio.h>

void	*philo_routine(t_philo philo)
{
	// philo take fork, lock 2 forks
	// philo eat
	// philo put down fork, unlock 2 forks
	// philo sleep
	// philo think
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

// ./philo num_of_philo time_to_die time_to_eat time_to_sleep [num_of_times_must_eat]
// ./philo 2 100 100 100 5
int	main(int argc, char **argv)
{
	t_game			game;
	struct timeval	current_time;

	if (argc < 5)
		// not enough argument
		return (1);
	// validity check
	game.number_of_philo = atoi(argv[1]);
	game.number_of_fork = game.number_of_philo;
	game.time_to_die = atoi(argv[2]);
	game.time_to_eat = atoi(argv[3]);
	game.time_to_sleep = aoit(argv[4]);
	if (argv[5])
		game.num_philo_must_eat = atoi(argv[5]);
	// int gettimeofday(struct timeval *restrict tp, void *restrict tzp);
	game.start_of_simulation = gettimeofday(&current_time, NULL);
	game.is_someone_died = false;
	game.num_of_full_philos = 0;
	printf("seconds: %ld \n microsecond :%ld ", current_time.tv_sec,
		current_time.tv_usec);
	while (!game.is_someone_died
		|| game.num_of_full_philos != game.number_of_philo) //
		start_philo(&game);
}
