/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-fons <dda-fons@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 12:38:45 by dda-fons          #+#    #+#             */
/*   Updated: 2025/07/08 16:24:31 by dda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*safe_malloc(size_t bytes)
{
	void	*ret;

	ret = malloc(bytes);
	if (ret == NULL)
		error_exit("Error with malloc");
	return (ret);
}

static void	handle_mutex_error(int status, t_opcode code)
{
	if (0 == status)
		return ;
	if (EINVAL == status && (LOCK == code || UNLOCK == code || DESTOY == code))
		error_exit("The value specifed by mutex is invalid");
	else if (EINVAL == status && INIT == code)
		error_exit("The value specifed by attr is invalid");
	else if (EDEADLK == status)
		error_exit("The current thread already owns the mutex. Will deadlock");
	else if (EPERM == status)
		error_exit("The current thread does not own the mutex.");
	else if (ENOMEM == status)
		error_exit("The process can't allocate enough memory to another mutex");
	else if (EBUSY == status)
		error_exit("Mutex is locked");
}

void	safe_mutex_handle(t_mtx *mutex, t_opcode opcode)
{
	if (LOCK == opcode)
		handle_mutex_error(pthread_mutex_lock(mutex), opcode);
	else if (UNLOCK == opcode)
		handle_mutex_error(pthread_mutex_unlock(mutex), opcode);
	else if (INIT == opcode)
		handle_mutex_error(pthread_mutex_init(mutex, NULL), opcode);
	else if (DESTOY == opcode)
		handle_mutex_error(pthread_mutex_destroy(mutex), opcode);
	else
		error_exit("Wrong opcode for mutex handle");
}

static void	handle_thread_error(int status, t_opcode code)
{
	if (0 == status)
		return ;
	if (EAGAIN == status)
		error_exit("No resources to create another thread\n");
	else if (EINVAL == status && CREATE == code)
		error_exit("The value specifed by attr is invalid \n");
	else if (EINVAL == status && (JOIN == code || DETACH == code))
		error_exit("The value specifed is not joinable \n");
	else if (EDEADLK == status)
		error_exit("Deadlock was detected or value of thread"
			"specifies the calling thread\n");
	else if (EPERM == status)
		error_exit("The caller does not have permission \n");
	else if (ESRCH == status)
		error_exit("No thread was found by the given thread ID \n");
}

void	safe_thread_handle(pthread_t *thread, void *(*foo)(void *),
	void *data, t_opcode opcode)
{
	if (CREATE == opcode)
		handle_thread_error(pthread_create(thread, NULL, foo, data), opcode);
	else if (JOIN == opcode)
		handle_thread_error(pthread_join(*thread, NULL), opcode);
	else if (DETACH == opcode)
		handle_thread_error(pthread_detach(*thread), opcode);
	else
		error_exit("Wrong opcode for thread handle");
}
