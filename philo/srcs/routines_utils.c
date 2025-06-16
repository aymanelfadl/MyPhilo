#include "../includes/philo.h"

void	special_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->meal_mutex);
	philo->last_meal_time = get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->table->meal_mutex);
	print_state(philo, EATING);
	custom_sleep(philo->table->time_to_eat);
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
	pthread_mutex_lock(&philo->table->turn_mutex);
	philo->table->current_turn = (philo->table->current_turn + 1) % 3;
	pthread_mutex_unlock(&philo->table->turn_mutex);
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

void	*routine_special_group(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!check_death(philo))
	{
		take_special_forks(philo);
		if (philo_should_exit(philo))
			break;
		special_eat(philo);
		sleep_and_think(philo);
	}
	return (NULL);
}
