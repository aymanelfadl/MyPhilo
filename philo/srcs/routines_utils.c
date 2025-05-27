#include "../includes/philo.h"

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

void	special_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->meal_mutex);
	philo->last_meal_time = get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->table->meal_mutex);
	print_state(philo, EATING);
	smart_sleep(philo->table->time_to_eat);
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
		take_forks(philo, 0);
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
	int		id;

	philo = (t_philo *)arg;
	id = philo->id - 1;
	while (!check_death(philo))
	{
		if (id == 0)
		{
			take_forks(philo, 1);
			special_eat(philo);
		}
		else if (id == 1 || id == 2)
		{
			smart_sleep(id * philo->table->time_to_eat / 2);
			take_forks(philo, 1);
			special_eat(philo);
		}
		if (philo_should_exit(philo))
			break;
		sleep_and_think(philo);
	}
	return (NULL);
}
