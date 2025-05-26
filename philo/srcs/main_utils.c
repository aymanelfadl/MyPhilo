#include "../includes/philo.h"

int	init_simulation(t_table *table)
{
	int	i;

	i = 0;
	table->start_time = get_time();
	while (i < table->num_of_philos)
	{
		table->philos[i].last_meal_time = table->start_time;
		if (pthread_create(&table->philos[i].thread, NULL,
			philosopher_routine, &table->philos[i]) != 0)
		{
			printf("%s\n", ERR_THREAD);
			return (0);
		}
		pthread_detach(table->philos[i].thread);
		i++;	
		usleep(100);
	}
	if (pthread_create(&table->monitor, NULL, monitor_routine, table) != 0)
	{
		printf("%s\n", ERR_THREAD);
		return (0);
	}
	return (1);
}

void	finish_simulation(t_table *table)
{
	pthread_join(table->monitor, NULL);
	cleanup(table);
}
