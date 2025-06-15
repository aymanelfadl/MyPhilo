#include "../includes/philo.h"

static void	handle_single_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->forks[philo->left_fork]);
	print_state(philo, TOOK_FORK);
	usleep(philo->table->time_to_die + 1);
	pthread_mutex_unlock(&philo->table->forks[philo->left_fork]);
}

int	wait_for_turn(t_philo *philo)
{
	while (1)
	{
		if (check_death(philo))
			return (1);
		pthread_mutex_lock(&philo->table->turn_mutex);
		if (philo->table->current_turn == philo->id)
		{
			pthread_mutex_unlock(&philo->table->turn_mutex);
			return (0);
		}
		pthread_mutex_unlock(&philo->table->turn_mutex);
	}
}

void	take_forks(t_philo *philo, int special)
{
	if (special && wait_for_turn(philo) != 0)
		return;
	if (philo->table->num_of_philos == 1)
		return	(handle_single_philo(philo));
	if ((philo->id % 2) == 0)
	{
		pthread_mutex_lock(&philo->table->forks[philo->left_fork]);
		print_state(philo, TOOK_FORK);	
		pthread_mutex_lock(&philo->table->forks[philo->right_fork]);
		print_state(philo, TOOK_FORK);
	}
	else
	{
		pthread_mutex_lock(&philo->table->forks[philo->left_fork]);
		print_state(philo, TOOK_FORK);
		pthread_mutex_lock(&philo->table->forks[philo->right_fork]);
		print_state(philo, TOOK_FORK);
	}
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->meal_mutex);
	philo->last_meal_time = get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->table->meal_mutex);
	print_state(philo, EATING);
	usleep(philo->table->time_to_eat);
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

void	sleep_and_think(t_philo *philo)
{
	print_state(philo, SLEEPING);
	usleep(philo->table->time_to_sleep);
	print_state(philo, THINKING);
}

int	philo_should_exit(t_philo *philo)
{
	if (philo->table->num_times_to_eat != -1 && 
		philo->meals_eaten >= philo->table->num_times_to_eat)
		return (1);
	return (0);
}

