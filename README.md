
This project has been created as part of the 42 curriculum by ylang.

# Description

In computer science, the dining philosophers problem is an example problem often used in concurrent algorithm design to illustrate synchronization issues and techniques for resolving them. 

This project is attempted to solve this problem with thread and mutex.

### Allowed functions

```
memset, printf, malloc, free, write,
precise_sleep, gettimeofday, 
pthread_create, pthread_detach, pthread_join, 
pthread_mutex_init, pthread_mutex_destroy, pthread_mutex_lock,pthread_mutex_unlock
```

# Instruction

- git clone this repository, open terminal, go to the project root where Makefile is located
- run `make`, a `./philo` executable will be genereated.

# Usage Examples

### Arguements 
`number_of_philosophers`, `time_to_die`, `time_to_eat`, `time_to_sleep`, optional argument `[number_of_times_each_philosopher_must_eat]`

```
./philo 5 100 100 100 2
```

### How to choose an appropriate data type for number of philos, time_to_sleep, time_to_eat, time_to_sleep?

int, long, long long ? unsigned or signed ?

decision made :
int, signed, 

INT_MAX 2147483647 milieseconds is already 24.85 days. Philosophoer project is not necessary to run this long. 

### What if this number of bigger than INT_MAX and smaller than INT_MIN?
treat it as `INT_MAX` or `INT_MIN`.

###  Why not use printf ?

printf is not atomic — one thread can interrupt another halfway through writing a line. multiple threads write to stdout simultaneously. so we need a print_mutex to make sure at one time there is only one thread writes to output. 

###  What is deadlock and how to avoid it ?
We have equal amounts of forks as amounts of philosophors. Each philo needs left fork and right fork to eat. When he eats he needs to lock the fork so other philo could not take it.  If everyone lock the left fork at the same time, a circular lock formed, because everyone is waiting for the second fork ,but they are locked by others, they start to death waiting for the another fork.

To avoid this kind of situation, we can introduce a bit assymetric in to the table. Each philo take the lower index fork first and then take the higher index fork, for the last one, because it is circular index, it takes fork 0 first and then try to take the higher index fork.  This avoid the deadlock. 

### Reduce contention
- delayed start  
split the philo into even/odd group, initially the even ones intentionally wait for `time to eat` before reaching for forks will reduce contention. 

- adaptive thinking time
Thinking time is not obligatory, but when a lot of philos wake up at the same time and reach for fork, it creats mutex contentions, adding adapative thinking time to handle larger philo numbers and larger think_time budget.

- precise sleep over usleep 
useelp can oversleep, polling in smaller intervals for better responsitve and status update. 

## 2 types of threads

Each philosophor is a thread running on its own, who eats ,sleeps and thinks , they don't know the status of other philosophors or the state of the game.

So we need a master monitor thread to check on the status of the game and state of each philosophor so that the program can know when philo is dead or when all philos are full, it is the time to end the simulation game. 


# Resources

https://nafuka11.github.io/philosophers-visualizer/

https://www.youtube.com/watch?v=d9s_d28yJq0

https://youtu.be/FYUi-u7UWgw?si=dVw4iaJWI3UI1klk