#include "../includes/philo.h"

int	init_simulation(t_table *table)
{
	int	i;

	i = 0;
	table->start_time = get_time();
	if ((table->num_of_philos % 2) != 0)
	{
		while (i < 3 && i < table->num_of_philos)
		{
			table->philos[i].last_meal_time = table->start_time;
			if (pthread_create(&table->philos[i].thread, NULL,
				routine_special_group, &table->philos[i]) != 0)
			{
				printf("%s\n", ERR_THREAD);
				return (0);
			}
			i++;
		}
	}
	while (i < table->num_of_philos)
	{
		table->philos[i].last_meal_time = table->start_time;
		if (pthread_create(&table->philos[i].thread, NULL,
			routine_even_pair, &table->philos[i]) != 0)
		{
			printf("%s\n", ERR_THREAD);
			return (0);
		}
		i++;
	}
	if (pthread_create(&table->monitor, NULL,
		monitor_routine, table) != 0)
	{
		printf("%s\n", ERR_THREAD);
		return (0);
	}
	return (1);
}

void	finish_simulation(t_table *table)
{
	int i;

	pthread_join(table->monitor, NULL);
	i = 0;
	while (i < table->num_of_philos)
	{
		pthread_join(table->philos[i].thread, NULL);
		i++;
	}
	cleanup(table);
}
