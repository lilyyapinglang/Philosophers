
This project has been created as part of the 42 curriculum by ylang.

# Description

## Allowed functions

```
memset, printf, malloc, free, write,
usleep, gettimeofday, 
pthread_create, pthread_detach, pthread_join, 
pthread_mutex_init, pthread_mutex_destroy, pthread_mutex_lock,pthread_mutex_unlock
```

# Instruction

# Usage Examples

## Arguements 
`number_of_philosophers`, `time_to_die`, `time_to_eat`, `time_to_sleep`,`[number_of_times_each_philosopher_must_eat]`

```
./philo 5 100 100 100 2
```


## How to choose an appropriate data type for number of philos, time_to_sleep, time_to_eat, time_to_sleep?

int, long, long long ? unsigned or signed ?

decision made :
int, signed, 

what is this number of bigger than INT_MAX and smaller than INT_MIN 


printf 

printf is not atomic — one thread can interrupt another halfway through writing a line.  multiple threads write to stdout simultaneously.


# Resources

https://nafuka11.github.io/philosophers-visualizer/

https://www.youtube.com/watch?v=d9s_d28yJq0