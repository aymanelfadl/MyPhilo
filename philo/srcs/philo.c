#include "../includes/philo.h"

void	take_forks(t_philo *philo)
{
	if (philo->table->num_of_philos == 1)
	{
		pthread_mutex_lock(&philo->table->forks[philo->left_fork]);
		print_state(philo, TOOK_FORK);
		smart_sleep(philo->table->time_to_die + 1);
		pthread_mutex_unlock(&philo->table->forks[philo->left_fork]);
		return;
	}
	
	pthread_mutex_lock(&philo->table->forks[philo->left_fork]);
	print_state(philo, TOOK_FORK);
	
	pthread_mutex_lock(&philo->table->forks[philo->right_fork]);
	print_state(philo, TOOK_FORK);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->meal_mutex);
	philo->last_meal_time = get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->table->meal_mutex);
	
	print_state(philo, EATING);
	smart_sleep(philo->table->time_to_eat);
	
	pthread_mutex_unlock(&philo->table->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->table->forks[philo->right_fork]);
}

void	sleep_and_think(t_philo *philo)
{
	print_state(philo, SLEEPING);
	smart_sleep(philo->table->time_to_sleep);
	print_state(philo, THINKING);
}

int	philo_should_exit(t_philo *philo)
{
	if (philo->table->num_times_to_eat != -1 && 
		philo->meals_eaten >= philo->table->num_times_to_eat)
		return (1);
	return (0);
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(800);
	while (!check_death(philo))
	{
		take_forks(philo);
		if (philo->table->num_of_philos == 1)
			break;
		eat(philo);
		if (philo_should_exit(philo))
			break;
		sleep_and_think(philo);
	}
	return (NULL);
}
