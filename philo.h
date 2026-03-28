
typedef struct	s_game
{
	int	num_philo_must_eat;
	int	number_of_philo;
    int number_of_fork;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
    int start_of_simulation;
} t_game;


typedef struct s_philo
{
    int *left_fork;
    int *right_fork;
    int last_meal_time;
    int count_of_eat_times;
} t_philo;


typedef struct s_fork{
    
} t_fork;