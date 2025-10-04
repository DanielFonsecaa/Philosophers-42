/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-fons <dda-fons@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 11:33:42 by dda-fons          #+#    #+#             */
/*   Updated: 2025/10/04 20:52:46 by dda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H 

//lib includes
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>
# include <limits.h>
# include <errno.h>

//my includes
# include "structs.h"
# include "declarations.h"

//main functions
int		init_simulation(t_sim *sim, char **argv, int argc);
int		start_simulation(t_sim *sim);
void	print_philo_action(t_sim *sim, int id, t_enum code);

//monitor
void	*supervisor(void *data);

//philo functions
void	*philo_drill(void *data);
bool	philo_eats(t_sim *sim, t_philo *philo);
bool	take_or_release_fork(t_sim *sim, t_philo *philo, bool is_taking);

//safe function
int		safe_mutex_handle(pthread_mutex_t *mutex, t_code code);
int		safe_thread_handle(pthread_t *thread, void *(*foo)(void *), void *data, t_code code);
long	get_long(pthread_mutex_t *mutex, long *value);
void	set_bool(pthread_mutex_t *mutex, bool *dest, bool value);
void	set_long(pthread_mutex_t *mutex, long *dest, long value);
bool	get_bool(pthread_mutex_t *mutex, bool *value);
int		get_int(pthread_mutex_t *mutex, int *value);
void	set_int(pthread_mutex_t *mutex, int *dest, int value);
bool	simulation_finished(t_sim *sim);

//utils
int		ft_atoi(const char *nptr);
int		print_and_return(char *str, int return_value);
long	get_time(void);
void	free_all(t_sim *sim);

#endif