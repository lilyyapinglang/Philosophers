#include "philo.h"
#include <stdio.h>

void	start_philo(t_game game)
{
	pthread_mutex_t	mutext_FUEL;

	// double linked list ?
	// create an array of philo;
	// create thread for each philo
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
	printf("seconds: %ld \n microsecond :%ld ", current_time.tv_sec,
		current_time.tv_usec);
	start_philo(game);
}
