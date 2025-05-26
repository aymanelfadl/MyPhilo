#include "../includes/philo.h"

int	check_philosopher_death(t_table *table, int i)
{
	long long current_time;
	long long time_since_last_meal;
	long long last_meal;

	current_time = get_time();
	
	pthread_mutex_lock(&table->meal_mutex);
	last_meal = table->philos[i].last_meal_time;
	pthread_mutex_unlock(&table->meal_mutex);
	
	time_since_last_meal = current_time - last_meal;
	
	if (time_since_last_meal > table->time_to_die)
	{
		pthread_mutex_lock(&table->death_mutex);
		if (table->someone_died == 0)
		{
			table->someone_died = 1;
			pthread_mutex_unlock(&table->death_mutex);
			print_state(&table->philos[i], DIED);
			return (1);
		}
		pthread_mutex_unlock(&table->death_mutex);
	}
	return (0);
}

int	check_philo_ate_enough(t_table *table, int i)
{
	pthread_mutex_lock(&table->meal_mutex);
	if (table->philos[i].meals_eaten < table->num_times_to_eat)
	{
		pthread_mutex_unlock(&table->meal_mutex);
		return (0);
	}
	pthread_mutex_unlock(&table->meal_mutex);
	return (1);
}
int	check_all_ate_enough(t_table *table)
{
	int	i;
	int	all_ate_enough;

	if (table->num_times_to_eat == -1)
		return (0);
	i = 0;
	all_ate_enough = 1;
	while (i < table->num_of_philos)
	{
		if (!check_philo_ate_enough(table, i))
			all_ate_enough = 0;
		i++;
	}
	return (all_ate_enough);
}

int	monitor_each_philosopher(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_of_philos)
	{
		if (check_philosopher_death(table, i))
			return (1);
		i++;
	}
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_table	*table;

	table = (t_table *)arg;
	
	usleep(100);
	
	while (1)
	{
		if (monitor_each_philosopher(table))
			return (NULL);
			
		if (check_all_ate_enough(table))
			return (NULL);
			
		usleep(500);
	}
	return (NULL);
}
