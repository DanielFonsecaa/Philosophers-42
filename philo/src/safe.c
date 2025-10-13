/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-fons <dda-fons@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 22:55:00 by dda-fons          #+#    #+#             */
/*   Updated: 2025/10/08 14:54:25 by dda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

/**
 * @brief Handles pthread mutex operation errors with detailed error messages
 * 
 * @param status Return value from pthread mutex operation
 * @param code Operation type for context-specific errors
 * @return int Returns 1 on success, 0 on any error with message printed
 */
static int	handle_mutex_error(int status, t_code cod)
{
	if (0 == status)
		return (1);
	if (EINVAL == status && (LOCK == cod || UNLOCK == cod || DESTROY == cod))
		return (print_and_return(MUTEX_VAL_INV, 0));
	else if (EINVAL == status && INIT == cod)
		return (print_and_return(ATTR_INV, 0));
	else if (EDEADLK == status)
		return (print_and_return(DEADLCK, 0));
	else if (EPERM == status)
		return (print_and_return(THREAD_NOT_OWN, 0));
	else if (ENOMEM == status)
		return (print_and_return(PR_NOT_MEM, 0));
	else if (EBUSY == status)
		return (print_and_return(MUTEX_LOCKED, 0));
	return (1);
}

/**
 * @brief Safe wrapper for pthread mutex operations with error handling
 * 
 * @param mutex Pointer to the pthread_mutex_t to operate on
 * @param code Operation type: LOCK, UNLOCK, INIT, or DESTROY
 * @return int 1 on success, 0 on failure (with error message printed)
 */
int	safe_mutex_handle(pthread_mutex_t *mutex, t_code code)
{
	if (LOCK == code)
		return (handle_mutex_error(pthread_mutex_lock(mutex), code));
	else if (UNLOCK == code)
		return (handle_mutex_error(pthread_mutex_unlock(mutex), code));
	else if (INIT == code)
		return (handle_mutex_error(pthread_mutex_init(mutex, NULL), code));
	else if (DESTROY == code)
		return (handle_mutex_error(pthread_mutex_destroy(mutex), code));
	else
		return (print_and_return(WRONG_CODE, 0));
}

/**
 * @brief Handles pthread thread operation errors
 * 
 * @param status Return value from pthread operation
 * @param code Operation type for context-specific error handling
 * @return void Prints error message and returns (no return value)
 */
static int	handle_thread_error(int status, t_code code)
{
	if (0 == status)
		return (1);
	if (EAGAIN == status)
		return (print_and_return(TH_NO_RSC, 0));
	else if (EINVAL == status && CREATE == code)
		return (print_and_return(ATTR_INV, 0));
	else if (EINVAL == status && JOIN == code)
		return (print_and_return(NOT_JOINABLE, 0));
	else if (EDEADLK == status)
		return (print_and_return(DEADLOCK, 0));
	else if (EPERM == status)
		return (print_and_return(NO_PERM, 0));
	else if (ESRCH == status)
		return (print_and_return(NOT_FOUND, 0));
	return (1);
}

/**
 * @brief Safe wrapper for pthread thread operations with error handling
 * 
 * @param thread Pointer to pthread_t thread identifier
 * @param foo Function pointer to thread routine (used only for CREATE)
 * @param data Argument to pass to thread routine (used only for CREATE)
 * @param code Operation type: CREATE or JOIN
 * @return void No return value (prints errors and returns on failure)
 */
int	safe_thread_handle(pthread_t *th, void *(*foo)(void *),
		void *sim, t_code code)
{
	if (CREATE == code)
		return (handle_thread_error(pthread_create(th, NULL, foo, sim), code));
	else if (JOIN == code)
		return (handle_thread_error(pthread_join(*th, NULL), code));
	else
		return (print_and_return(WRONG_CODE, 0));
}

/**
 * @brief Prints a string and returns a specified value
 * 
 * @param str String to be printed to stdout
 * @param return_value Value to be returned by the function
 * @return int The return_value parameter unchanged
 */
int	print_and_return(char *str, int return_value)
{
	printf("%s", str);
	return (return_value);
}
