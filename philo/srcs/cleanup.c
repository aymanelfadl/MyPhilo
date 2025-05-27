#include "../includes/philo.h"

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
