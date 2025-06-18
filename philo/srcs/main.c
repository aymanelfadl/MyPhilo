/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelfadl <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 11:37:21 by aelfadl           #+#    #+#             */
/*   Updated: 2025/06/18 11:37:21 by aelfadl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static	int	run_philo_simulation(t_table *table)
{
	if (!init_mutex(table))
		return (0);
	init_philos(table);
	if (!init_simulation(table))
		return (0);
	return (1);
}

int	main(int argc, char **argv)
{
	t_table	table;

	if (check_args(argc, argv) == 0)
		return (1);
	if (init_table(&table, argc, argv) == 0)
		return (1);
	if (!run_philo_simulation(&table))
		return (cleanup(&table), 1);
	finish_simulation(&table);
	return (0);
}
