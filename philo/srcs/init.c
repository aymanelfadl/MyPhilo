#include "../includes/philo.h"

int	check_args(int argc, char **argv)
{
	int	i;
	int	j;

	if (argc != 5 && argc != 6)
		return (printf("%s\n", "Invalid number of arguments"), 0);
	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return(printf("%s\n", "Invalid input arguments"), 0);
			j++;
		}
		i++;
	}
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

	i = -1;
	while (++i < table->num_of_philos)
	{
		if (pthread_mutex_init(&table->forks[i], NULL) != 0)
			return (printf("%s\n", "Mutex initialization failed"), 0);
	}
	if (pthread_mutex_init(&table->print_mutex, NULL) != 0)
		return (printf("%s\n", "Mutex initialization failed"), 0);
	if (pthread_mutex_init(&table->death_mutex, NULL) != 0)
		return (printf("%s\n", "Mutex initialization failed"), 0);
	if (pthread_mutex_init(&table->meal_mutex, NULL) != 0)
		return (printf("%s\n", "Mutex initialization failed"), 0);
	if (pthread_mutex_init(&table->turn_mutex, NULL) != 0)
		return (printf("%s\n", "Mutex initialization failed"), 0);
	return (1);
}

void	init_philos(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_of_philos)
	{
		table->philos[i].id = i + 1;
		table->philos[i].meals_eaten = 0;
		table->philos[i].last_meal_time = 0;
		table->philos[i].table = table;
		i++;
	}
	if (table->num_of_philos % 2 == 0)
		assign_forks_even(table);
	else
		assign_forks_odd(table);
}

