/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-fons <dda-fons@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 11:36:59 by dda-fons          #+#    #+#             */
/*   Updated: 2025/07/12 16:19:37 by dda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>
# include <errno.h>

// Color text
# define R  "\033[0m"
# define RST  "\033[0m"
# define RED  "\033[1;31m"
# define GRN  "\033[1;32m"
# define Y  "\033[1;33m"
# define BLU  "\033[1;34m"
# define MAG  "\033[1;35m"
# define CYN  "\033[1;36m"
# define W  "\033[1;37m"
# define B "\033[1m"
# define UNDL "\033[4m"

# define DEBUG_MODE 0

//ENEM FOR MUTEX
typedef enum e_opcode
{
	LOCK,
	UNLOCK,
	INIT,
	DESTOY,
	CREATE,
	JOIN,
	DETACH,
}		t_opcode;

typedef enum e_time_code
{
	SECOND,
	MILISECOND,
	MICROSECOND,
}		t_time_code;

typedef enum e_philo_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DIED,
}		t_philo_status;

//IOU
typedef struct s_table	t_table;
//more readable code
typedef pthread_mutex_t	t_mtx;

// ***** STRUCTS *****
typedef struct s_fork
{
	t_mtx	fork;
	int		fork_id;
}			t_fork;

typedef struct s_philo
{
	int			philo_id;
	int			meals_count;
	bool		full;
	long		last_meal_time;
	t_fork		*first_fork;
	t_fork		*second_fork;
	pthread_t	thread_id;
	t_mtx		philo_mutex;
	t_table		*table;
}		t_philo;

typedef struct s_table
{
	long		philo_nbr;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	long		nbr_limit_meals;
	long		start_simulation;
	long		threads_running_nbr;
	bool		end_simulation;
	bool		all_threads_ready;
	pthread_t	monitor;
	t_mtx		table_mutex;
	t_mtx		write_mutex;
	t_fork		*forks;
	t_philo		*philos;
}		t_table;

// ***** PROTOTYPES *****

// ***** utils *****
void	error_exit(char *error);
long	get_time(t_time_code time_code);
void	precise_usleep(long usec, t_table *table);

// ***** parsing *****
void	parse_input(t_table *table, char **av);

//***** safe functions *****
void	*safe_malloc(size_t bytes);
void	safe_mutex_handle(t_mtx *mutex, t_opcode opcode);
void	safe_thread_handle(pthread_t *thread, void *(*foo)(void *),
			void *data, t_opcode opcode);

// ***** init *****
void	init_data(t_table *table);

// ***** getters and setters *****
void	set_bool(t_mtx *mutex, bool *dest, bool value);
bool	get_bool(t_mtx *mutex, bool *value);
void	set_long(t_mtx *mutex, long *dest, long value);
long	get_long(t_mtx *mutex, long *value);
bool	simulation_finished(t_table *table);

// ***** syncro and wait *****
void	wait_all_threads(t_table *table);
bool	all_threads_running(t_mtx *mutex, long *threads, long philo_nbr);
void	increase_long(t_mtx *mutex, long *value);

// ***** write *****
void	write_status(t_philo_status status, t_philo *philo, bool debug);
void	write_status_debug(t_philo_status status, t_philo *philo, long elapsed);

//dinner
void	*dinner_simulation(void *data);
void	start_dinner(t_table *table);

//monitor
void	*monitor_dinner(void *data);


void	clean(t_table *table);

#endif
