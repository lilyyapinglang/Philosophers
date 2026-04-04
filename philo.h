#include <pthread.h>
#include <stdbool.h>
#include <sys/time.h>

typedef struct s_game
{
	long num_philo_must_eat; // flag if -1 ?
	long			number_of_philo;
	long			number_of_fork;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			start_time_of_simulation;
	int				num_of_full_philos;
	bool			is_someone_died;
	bool end_simulation; // a philo dead or everything is full
	t_fork *forks;       // array
	t_philo *philos;     // array
}					t_game;

typedef struct s_philo
{
	int				philo_id;
	t_fork			*left_fork;
	t_fork			*right_fork;
	long last_meal_time; // time passed from last meal
	long			count_of_eat_times;
	bool			full;
	pthread_t thread_id; // a philo is a thread
	t_game			*game;
}					t_philo;

typedef struct s_fork
{
	int				fork_id;
	pthread_mutex_t	fork;
}					t_fork;