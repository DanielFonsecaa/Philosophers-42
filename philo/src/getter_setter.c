/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getter_setter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-fons <dda-fons@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 10:57:10 by dda-fons          #+#    #+#             */
/*   Updated: 2025/10/05 12:38:58 by dda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

/**
 * @brief Safely get a boolean value with mutex protection
 * 
 * @param mutex Mutex to protect the operation
 * @param value Pointer to boolean value to read
 * @return bool The protected boolean value
 */
bool	get_bool(pthread_mutex_t *mutex, bool *value)
{
	bool	ret;

	safe_mutex_handle(mutex, LOCK);
	ret = *value;
	safe_mutex_handle(mutex, UNLOCK);
	return (ret);
}

/**
 * @brief Safely set a boolean value with mutex protection
 * 
 * @param mutex Mutex to protect the operation
 * @param dest Pointer to boolean destination
 * @param value Boolean value to set
 */
void	set_bool(pthread_mutex_t *mutex, bool *dest, bool value)
{
	safe_mutex_handle(mutex, LOCK);
	*dest = value;
	safe_mutex_handle(mutex, UNLOCK);
}

/**
 * @brief Safely get a long value with mutex protection
 * 
 * @param mutex Mutex to protect the operation
 * @param value Pointer to long value to read
 * @return long The protected long value
 */
long	get_long(pthread_mutex_t *mutex, long *value)
{
	long	ret;

	safe_mutex_handle(mutex, LOCK);
	ret = *value;
	safe_mutex_handle(mutex, UNLOCK);
	return (ret);
}

/**
 * @brief Safely set a long value with mutex protection
 * 
 * @param mutex Mutex to protect the operation
 * @param dest Pointer to long destination
 * @param value Long value to set
 */
void	set_long(pthread_mutex_t *mutex, long *dest, long value)
{
	safe_mutex_handle(mutex, LOCK);
	*dest = value;
	safe_mutex_handle(mutex, UNLOCK);
}

bool	simulation_finished(t_sim *sim)
{
	return (get_bool(&sim->table_mtx, &sim->simul_end));
}
