/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_philos.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelfadl <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 11:37:21 by aelfadl           #+#    #+#             */
/*   Updated: 2025/06/18 11:37:21 by aelfadl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	handle_single_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->forks[philo->left_fork]);
	print_state(philo, TOOK_FORK);
	pthread_mutex_unlock(&philo->table->forks[philo->left_fork]);
}

void	special_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->meal_mutex);
	philo->last_meal_time = get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->table->meal_mutex);
	print_state(philo, EATING);
	custom_sleep(philo->table->time_to_eat, philo);
	pthread_mutex_lock(&philo->table->turn_mutex);
	put_forks(philo);
	philo->table->current_turn = (philo->table->current_turn + 1) % 3;
	pthread_mutex_unlock(&philo->table->turn_mutex);
}

void	wait_for_turn(t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock(&philo->table->turn_mutex);
		if (philo->table->current_turn == philo->id - 1)
		{
			pthread_mutex_unlock(&philo->table->turn_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->table->turn_mutex);
	}
}

void	take_special_forks(t_philo *philo)
{
	wait_for_turn(philo);
	take_forks(philo);
}

void	*routine_special_group(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!check_death(philo))
	{
		if (philo->table->num_of_philos == 1)
			handle_single_philo(philo);
		if (philo_should_exit(philo))
			break ;
		take_special_forks(philo);
		special_eat(philo);
		sleep_and_think(philo);
	}
	return (NULL);
}
