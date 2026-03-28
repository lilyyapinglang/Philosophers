#include"philo.h"
#include <stdio.h>


void start_philo(t_philo philo)
{
    //double linked list ?
}

int	main(int argc, char **argv)
{
	if (argc < 5)
		// not enough argument
		return (1);
    
    t_philo philo;
    // validity check
	philo.number_of_philo = atoi(argv[1]);
	philo.time_to_die = atoi(argv[2]);
	philo.time_to_eat = atoi(argv[3]);
	philo.time_to_sleep = aoit(argv[4]);
	if (argv[5])
		philo.num_philo_must_eat = atoi(argv[5]);
    
    start_philo(philo);
}

