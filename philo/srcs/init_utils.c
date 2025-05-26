#include "../includes/philo.h"

int	check_numeric_args(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
			{
				printf("%s\n", ERR_INPUT);
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	validate_table_values(t_table *table, int argc)
{
	if (table->num_of_philos <= 0 || table->num_of_philos > 200 || 
		table->time_to_die <= 0 || table->time_to_eat <= 0 || 
		table->time_to_sleep <= 0 || (argc == 6 && table->num_times_to_eat <= 0))
	{
		printf("%s\n", ERR_INPUT);
		return (0);
	}
	return (1);
}

int	allocate_table_memory(t_table *table)
{
	table->forks = malloc(sizeof(pthread_mutex_t) * table->num_of_philos);
	if (!table->forks)
		return (printf("%s\n", ERR_MALLOC),0);
	table->philos = malloc(sizeof(t_philo) * table->num_of_philos);
	if (!table->philos)
		return (free(table->forks),printf("%s\n", ERR_MALLOC),0);
	return (1);
}

int	init_additional_mutexes(t_table *table)
{
	if (pthread_mutex_init(&table->print_mutex, NULL) != 0)
	{
		printf("%s\n", ERR_MUTEX);
		return (0);
	}
	if (pthread_mutex_init(&table->death_mutex, NULL) != 0)
	{
		printf("%s\n", ERR_MUTEX);
		return (0);
	}
	if (pthread_mutex_init(&table->meal_mutex, NULL) != 0)
	{
		printf("%s\n", ERR_MUTEX);
		return (0);
	}
	return (1);
}

void	set_philo_forks(t_table *table)
{
	int	i;
	int	temp;

	i = 0;
	while (i < table->num_of_philos)
	{
		if (i % 2 != 0)
		{
			temp = table->philos[i].left_fork;
			table->philos[i].left_fork = table->philos[i].right_fork;
			table->philos[i].right_fork = temp;
		}
		i++;
	}
}
