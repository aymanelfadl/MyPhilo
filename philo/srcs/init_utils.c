/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelfadl <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 11:37:21 by aelfadl           #+#    #+#             */
/*   Updated: 2025/06/18 11:37:21 by aelfadl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	validate_table_values(t_table *table, int argc)
{
	if (table->num_of_philos <= 0 || table->time_to_die <= 0
		|| table->time_to_eat <= 0 || table->time_to_sleep <= 0 || (argc == 6
			&& table->num_times_to_eat <= 0))
		return (printf("%s\n", "Invalid input arguments"), 0);
	return (1);
}

int	allocate_table_memory(t_table *table)
{
	table->forks = malloc(sizeof(pthread_mutex_t) * table->num_of_philos);
	if (!table->forks)
		return (printf("%s\n", ERR_MALLOC), 0);
	table->philos = malloc(sizeof(t_philo) * table->num_of_philos);
	if (!table->philos)
		return (free(table->forks), printf("%s\n", ERR_MALLOC), 0);
	return (1);
}

void	assign_forks_odd(t_table *table)
{
	int	i;

	table->philos[0].left_fork = 0;
	table->philos[0].right_fork = 1;
	table->philos[1].left_fork = 1;
	table->philos[1].right_fork = 2;
	table->philos[2].left_fork = 2;
	table->philos[2].right_fork = 0;
	i = 3;
	while (i < table->num_of_philos - 1)
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

	i = 0;
	while (i < table->num_of_philos - 1)
	{
		table->philos[i].left_fork = i;
		table->philos[i].right_fork = i + 1;
		table->philos[i + 1].left_fork = i + 1;
		table->philos[i + 1].right_fork = i;
		i += 2;
	}
}
