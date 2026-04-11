#include <pthread.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

typedef struct s_fork
{
	int fork_id; // debug purpose
	pthread_mutex_t	fork;
}					t_fork;

typedef struct s_philo
{
	long			philo_id;
	t_fork			*first_fork;
	t_fork			*second_fork;
	struct s_game	*game;
	long last_meal_time; // time passed from last meal
	long			count_of_eat_times;
	bool			full;
	pthread_t thread_id; // a philo is a thread
}					t_philo;

typedef struct s_game
{
	long num_philo_must_eat; // flag if -1 ?
	long			number_of_philo;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long long		start_time_of_simulation;
	bool			num_of_full_philos;
	bool			is_someone_died;
	bool end_simulation; // a philo dead or everything is full
	pthread_t		monitor_thread;
	t_fork *forks;   // array of mutex forks
	t_philo *philos; // array of philos
}					t_game;
