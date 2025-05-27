#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>

# define ERR_ARGS "Invalid number of arguments"
# define ERR_INPUT "Invalid input arguments"
# define ERR_MALLOC "Memory allocation failed"
# define ERR_MUTEX "Mutex initialization failed"
# define ERR_THREAD "Thread creation failed"

# define THINKING 1
# define EATING 2
# define SLEEPING 3
# define TOOK_FORK 4
# define DIED 5

typedef struct s_philo	t_philo;
typedef struct s_table	t_table;

struct s_table
{
	int				num_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_times_to_eat;
	long long		start_time;
	int				someone_died;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	turn_mutex; // Added turn_mutex
	int				current_turn; // Added current_turn
	t_philo			*philos;
	pthread_t		monitor;
};

struct s_philo
{
	int				id;
	int				left_fork;
	int				right_fork;
	int				meals_eaten;
	long long		last_meal_time;
	pthread_t		thread;
	t_table			*table;
};

/* Init functions */
int			init_table(t_table *table, int argc, char **argv);
int			init_mutex(t_table *table);
int			init_philos(t_table *table);

/* Utility functions */
int			ft_atoi(const char *str);
long long	get_time(void);
void		print_state(t_philo *philo, int state);
void		smart_sleep(long long time_to_wait);
int			check_args(int argc, char **argv);
int			wait_for_turn(t_philo *philo);

/* Philosopher actions */
void		take_forks(t_philo *philo, int special);
void		eat(t_philo *philo);
void		special_eat(t_philo *philo);
void		sleep_and_think(t_philo *philo);
int			philo_should_exit(t_philo *philo);

/* Monitoring and cleanup */
void		*monitor_routine(void *arg);
int			check_death(t_philo *philo);
void		cleanup(t_table *table);
void		destroy_mutexes(t_table *table);

/* Additional utility functions */
int			check_numeric_args(char **argv);
int			validate_table_values(t_table *table, int argc);
int			allocate_table_memory(t_table *table);
int			init_additional_mutexes(t_table *table);
void		init_philo_data(t_table *table);
void		assign_forks_odd(t_table *table);
void		assign_forks_even(t_table *table);

/* Main utility functions */
int			init_simulation(t_table *table);
void		finish_simulation(t_table *table);

/* Monitoring functions */
int			check_philosopher_death(t_table *table, int i);
int			check_philo_ate_enough(t_table *table, int i);
int			check_all_ate_enough(t_table *table);
int			monitor_each_philosopher(t_table *table);
void		*routine_even_pair(void *arg);
void		*routine_special_group(void *arg);

#endif
