/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelfadl <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 11:31:44 by aelfadl           #+#    #+#             */
/*   Updated: 2025/06/18 11:37:21 by aelfadl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	philo_should_exit(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->meal_mutex);
	if (philo->table->all_ate || philo->table->num_of_philos == 1)
		return (pthread_mutex_unlock(&philo->table->meal_mutex), 1);
	return (pthread_mutex_unlock(&philo->table->meal_mutex), 0);
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
