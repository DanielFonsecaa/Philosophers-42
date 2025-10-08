/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-fons <dda-fons@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 22:37:38 by dda-fons          #+#    #+#             */
/*   Updated: 2025/10/05 14:30:58 by dda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

long	get_time(void)
{
	struct timeval	tv;
	long			time;

	gettimeofday(&tv, NULL);
	time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time);
}

/**
 * @brief Safely get an int value with mutex protection
 * 
 * @param mutex Mutex to protect the operation
 * @param value Pointer to int value to read
 * @return int The protected int value
 */
int	get_int(pthread_mutex_t *mutex, int *value)
{
	int	ret;

	safe_mutex_handle(mutex, LOCK);
	ret = *value;
	safe_mutex_handle(mutex, UNLOCK);
	return (ret);
}

/**
 * @brief Safely set an int value with mutex protection
 * 
 * @param mutex Mutex to protect the operation
 * @param dest Pointer to int destination
 * @param value Int value to set
 */
void	set_int(pthread_mutex_t *mutex, int *dest, int value)
{
	safe_mutex_handle(mutex, LOCK);
	*dest = value;
	safe_mutex_handle(mutex, UNLOCK);
}

void	free_all(t_sim *sim)
{
	int	i;

	i = -1;
	while (++i < sim->table.num_philos)
	{
		safe_mutex_handle(&sim->table.forks[i], DESTROY);
		safe_mutex_handle(&sim->table.philos[i].philo_mtx, DESTROY);
	}
	safe_mutex_handle(&sim->table_mtx, DESTROY);
	safe_mutex_handle(&sim->write_mtx, DESTROY);
	free(sim->table.forks);
	free(sim->table.philos);
}
