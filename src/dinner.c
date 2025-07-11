/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-fons <dda-fons@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 16:23:56 by dda-fons          #+#    #+#             */
/*   Updated: 2025/07/08 19:15:12 by dda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*dinner_simulation(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_threads(philo->table);
	while (!simulation_finished(philo->table))
	{
		if (philo->full)
			break ;
		eat(philo);
		thinking(philo);
	}
	return (NULL);
}

void	start_dinner(t_table *table)
{
	int	i;

	i = 0;
	if (table->nbr_limit_meals)
		return ;
	else if (table->philo_nbr == 1)
		; //todo
	else
	{
		while (i++ < table->philo_nbr)
			safe_thread_handle(&table->philos[i].thread_id, dinner_simulation,
				&table->philos[i], CREATE);
	}
	table->start_simulation = get_time(MILISECOND);
	set_bool(&table->table_mutex, &table->all_threads_ready, true);
	i = 0;
	while (i++ < table->philo_nbr)
		safe_thread_handle(&table->philos[i].thread_id, NULL, NULL, JOIN);
}
