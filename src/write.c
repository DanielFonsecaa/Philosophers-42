/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-fons <dda-fons@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 18:39:46 by dda-fons          #+#    #+#             */
/*   Updated: 2025/07/11 14:39:21 by dda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	write_status_debug(t_philo_status status, t_philo *philo, long elapsed)
{
	if (TAKE_FIRST_FORK == status && !simulation_finished(philo->table))
		printf(W "%-6ld %d" R " has taken the 1 fork\n"
			"\t\t\tn"B"[  %d  ]\n"RST, elapsed, philo->philo_id,
			philo->first_fork->fork_id);
	if (TAKE_SECOND_FORK == status && !simulation_finished(philo->table))
		printf(W"%-6ld %d" R " has taken the 2 fork\n"
			"\t\t\tn"B"[  %d  ]\n"RST, elapsed, philo->philo_id,
			philo->second_fork->fork_id);
	else if (EATING == status && !simulation_finished(philo->table))
		printf(W"%-6ld %d is eating\n"
			"\t\t\t"Y"[  %d  ]\n"RST, elapsed, philo->philo_id,
			philo->meals_count);
	else if (SLEEPING == status && !simulation_finished(philo->table))
		printf(W"%-6ld %d is sleeping\n"RST, elapsed, philo->philo_id);
	else if (THINKING == status && !simulation_finished(philo->table))
		printf(W"%-6ld %d is thinking\n"RST, elapsed, philo->philo_id);
	else if (DIED == status)
		printf(RED"%-6ld %d died\n"RST, elapsed, philo->philo_id);
}

void	write_status(t_philo_status status, t_philo *philo, bool debug)
{
	long	elapsed;

	elapsed = get_time(MILISECOND) - philo->table->start_simulation;
	if (philo->full)
		return ;
	safe_mutex_handle(&philo->table->write_mutex, LOCK);
	if (debug)
		write_status_debug(status, philo, elapsed);
	else
	{
		if ((TAKE_FIRST_FORK == status || TAKE_SECOND_FORK == status)
			&& !simulation_finished(philo->table))
			printf(W "%-6ld %d" R " has taken the 1 fork\n", elapsed, philo->philo_id);
		else if (EATING == status && !simulation_finished(philo->table))
			printf(W"%-6ld %d is eating\n"RST, elapsed, philo->philo_id);
		else if (SLEEPING == status && !simulation_finished(philo->table))
			printf(W"%-6ld %d is sleeping\n"RST, elapsed, philo->philo_id);
		else if (THINKING == status && !simulation_finished(philo->table))
			printf(W"%-6ld %d is thinking\n"RST, elapsed, philo->philo_id);
		else if (DIED == status)
			printf(RED"%-6ld %d died\n"RST, elapsed, philo->philo_id);
	}
	safe_mutex_handle(&philo->table->write_mutex, UNLOCK);
}
