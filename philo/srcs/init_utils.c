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
	if (pthread_mutex_init(&table->turn_mutex, NULL) != 0)
	{
		printf("%s\n", ERR_MUTEX);
		return (0);
	}
	return (1);
}

void	init_philo_data(t_table *table)
{
	int	i;
	int	num;

	i = 0;
	num = table->num_of_philos;
	while (i < num)
	{
		table->philos[i].id = i + 1;
		table->philos[i].meals_eaten = 0;
		table->philos[i].last_meal_time = 0;
		table->philos[i].table = table;
		i++;
	}
}

void	assign_forks_odd(t_table *table)
{
	int	i;
	int	num;

	num = table->num_of_philos;
	table->philos[0].left_fork = 0;
	table->philos[0].right_fork = 1;
	table->philos[1].left_fork = 1;
	table->philos[1].right_fork = 2;
	table->philos[2].left_fork = 2;
	table->philos[2].right_fork = 0;
	i = 3;
	while (i < num - 1)
	{
		table->philos[i].left_fork = i;
		table->philos[i].right_fork = i + 1;
		table->philos[i + 1].left_fork = i + 1;
		table->philos[i + 1].right_fork = i;
		i += 2;
	}
}

void	assign_forks_even(t_table *table)
{
	int	i;
	int	num;

	i = 0;
	num = table->num_of_philos;
	while (i < num - 1)
	{
		table->philos[i].left_fork = i;
		table->philos[i].right_fork = i + 1;
		table->philos[i + 1].left_fork = i + 1;
		table->philos[i + 1].right_fork = i;
		i += 2;
	}
}

