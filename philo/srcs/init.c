#include "../includes/philo.h"

int	check_args(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
	{
		printf("%s\n", ERR_ARGS);
		return (0);
	}
	if (!check_numeric_args(argv))
		return (0);
	return (1);
}

int	init_table(t_table *table, int argc, char **argv)
{
	table->num_of_philos = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	table->someone_died = 0;
	table->current_turn = 0;
	if (argc == 6)
		table->num_times_to_eat = ft_atoi(argv[5]);
	else
		table->num_times_to_eat = -1;
	if (!validate_table_values(table, argc) || !allocate_table_memory(table))
		return (0);
	return (1);
}

int	init_mutex(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_of_philos)
	{
		if (pthread_mutex_init(&table->forks[i], NULL) != 0)
		{
			printf("%s\n", ERR_MUTEX);
			return (0);
		}
		i++;
	}
	if (!init_additional_mutexes(table))
		return (0);
	return (1);
}

int	init_philos(t_table *table)
{
	int	num;

	num = table->num_of_philos;
	init_philo_data(table);
	if (num % 2 != 0)
		assign_forks_odd(table);
	else
		assign_forks_even(table);
	return (1);
}

