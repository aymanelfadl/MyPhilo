#include "../includes/philo.h"

long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	run_simulation_special(t_table *table)
{
	int i;
	i = 0;
	while (i < 3 && i < table->num_of_philos)
	{
		table->philos[i].last_meal_time = table->start_time;
		if (pthread_create(&table->philos[i].thread, NULL,
			routine_special_group, &table->philos[i]) != 0)
			return (printf("%s\n", "Thread creation failed"), 0);
		i++;
	}
	return i;				
}

int	init_simulation(t_table *table)
{
	int	i;

	i = 0;
	table->start_time = get_time();
	if ((table->num_of_philos % 2) != 0)
		i = run_simulation_special(table);
	while (i < table->num_of_philos)
	{
		table->philos[i].last_meal_time = table->start_time;
		if (pthread_create(&table->philos[i].thread, NULL,
			routine_even_pair, &table->philos[i]) != 0)
			return (printf("%s\n", "Thread creation failed"), 0);
		i++;
	}
	if (pthread_create(&table->monitor, NULL,
		monitor_routine, table) != 0)
		return (printf("%s\n", "Thread creation failed"), 0);

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
