/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-fons <dda-fons@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 11:33:37 by dda-fons          #+#    #+#             */
/*   Updated: 2025/10/05 12:16:36 by dda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <pthread.h>
# include <stdbool.h>

//enum for actions
typedef enum e_enum
{
	FORK,
	EAT,
	SLEEP,
	THINK,
	DIE,
}			t_enum;

typedef enum e_code
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
}		t_code;

//struct for philos
typedef struct s_philo
{
	int				id;
	int				meals;
	int				left_fork;
	int				right_fork;
	bool			is_full;
	long			last_meal_time;
	void			*sim;
	pthread_t		thread;
	pthread_mutex_t	philo_mtx;
}			t_philo;

//struck for table of pfilos
typedef struct table
{
	int				n_philos_full;
	int				num_philos;
	t_philo			*philos;
	pthread_mutex_t	*forks;
}			t_table;

//struck for main sim
typedef struct s_sim
{
	int				time_eat;
	int				time_sleep;
	int				time_die;
	int				num_of_meals;
	bool			simul_end;
	long			time_simul_start;
	t_table			table;
	pthread_mutex_t	write_mtx;
	pthread_mutex_t	table_mtx;
}			t_sim;

#endif