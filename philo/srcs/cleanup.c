#include "../includes/philo.h"

int	philo_should_exit(t_philo *philo)
{
	if (philo->table->num_of_philos == 1)
		return 1;
	if ((philo->table->num_times_to_eat != -1 && 
		philo->meals_eaten >= philo->table->num_times_to_eat) || philo->table->num_of_philos == 1 ) 
		return (1);
	return (0);
}

int	check_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->death_mutex);
	if (philo->table->someone_died)
	{
		pthread_mutex_unlock(&philo->table->death_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->table->death_mutex);
	return (0);
}

void	destroy_mutexes(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_of_philos)
	{
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&table->print_mutex);
	pthread_mutex_destroy(&table->death_mutex);
	pthread_mutex_destroy(&table->meal_mutex);
	pthread_mutex_destroy(&table->turn_mutex);
}

void	cleanup(t_table *table)
{
	if (table->forks)
		destroy_mutexes(table);
	if (table->forks)
		free(table->forks);
	if (table->philos)
		free(table->philos);
}
