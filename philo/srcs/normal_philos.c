#include "../includes/philo.h"

void	sleep_and_think(t_philo *philo)
{
	print_state(philo, SLEEPING);
	custom_sleep(philo->table->time_to_sleep);
	print_state(philo, THINKING);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->meal_mutex);
	philo->last_meal_time = get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->table->meal_mutex);
	print_state(philo, EATING);
	custom_sleep(philo->table->time_to_eat);
	put_forks(philo);
}

void	take_forks(t_philo *philo)
{
	if ((philo->id % 2) == 0)
	{
		pthread_mutex_lock(&philo->table->forks[philo->left_fork]);
		print_state(philo, TOOK_FORK);	
		pthread_mutex_lock(&philo->table->forks[philo->right_fork]);
		print_state(philo, TOOK_FORK);
	}
	else
	{
		pthread_mutex_lock(&philo->table->forks[philo->right_fork]);
		print_state(philo, TOOK_FORK);
		pthread_mutex_lock(&philo->table->forks[philo->left_fork]);
		print_state(philo, TOOK_FORK);
	}
}

void	put_forks(t_philo *philo)
{
	if ((philo->id % 2) == 0)
	{
		pthread_mutex_unlock(&philo->table->forks[philo->left_fork]);
		pthread_mutex_unlock(&philo->table->forks[philo->right_fork]);
	}
	else
	{
		pthread_mutex_unlock(&philo->table->forks[philo->right_fork]);
		pthread_mutex_unlock(&philo->table->forks[philo->left_fork]);
	}
}

void	*routine_even_pair(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!check_death(philo))
	{
		take_forks(philo);
		eat(philo);
		if (philo_should_exit(philo))
			break;
		sleep_and_think(philo);
	}
	return (NULL);
}
