#include "../includes/philo.h"

static void	handle_single_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->forks[philo->left_fork]);
	print_state(philo, TOOK_FORK);
	custom_sleep(philo->table->time_to_die + 1);
	pthread_mutex_unlock(&philo->table->forks[philo->left_fork]);
}

void	special_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->meal_mutex);
	philo->last_meal_time = get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->table->meal_mutex);
	print_state(philo, EATING);
	custom_sleep(philo->table->time_to_eat);
	pthread_mutex_lock(&philo->table->turn_mutex);
	put_forks(philo);
	philo->table->current_turn = (philo->table->current_turn + 1) % 3;
	pthread_mutex_unlock(&philo->table->turn_mutex);
}

int	wait_for_turn(t_philo *philo)
{
	while (1)
	{
		if (check_death(philo))
			return (1);
		pthread_mutex_lock(&philo->table->turn_mutex);
		if (philo->table->current_turn == philo->id - 1)
		{
			pthread_mutex_unlock(&philo->table->turn_mutex);
			return (0);
		}
		pthread_mutex_unlock(&philo->table->turn_mutex);
	}
}

int	take_special_forks(t_philo *philo)
{
	wait_for_turn(philo);
	if (philo->table->num_of_philos == 1)
		return	(handle_single_philo(philo), 1);
	take_forks(philo);
	return 0;
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
