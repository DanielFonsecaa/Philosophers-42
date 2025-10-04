/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-fons <dda-fons@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 12:23:19 by dda-fons          #+#    #+#             */
/*   Updated: 2025/10/04 21:57:08 by dda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

/**
 * @brief Initializes all philosopher structures and their associated mutexes
 * 
 * @param sim Pointer to the simulation structure
 * @return int 1 on success, 0 on failure (memory allocation or mutex init error)
 */
static int	init_philos(t_sim *sim)
{
	int	i;

	i = 0;
	sim->table.n_philos_full = 0;
	sim->table.philos = malloc(sizeof(t_philo) * sim->table.num_philos);
	if (!sim->table.philos)
		return (0);
	while (i < sim->table.num_philos)
	{
		memset(&sim->table.philos[i], 0, sizeof(t_philo));
		sim->table.philos[i].id = i + 1;
		sim->table.philos[i].is_full = false;
		sim->table.philos[i].last_meal_time = get_time();
		sim->table.philos[i].left_fork = i;
		sim->table.philos[i].right_fork = (i + 1) % sim->table.num_philos;
		sim->table.philos[i].sim = sim;
		if (!safe_mutex_handle(&sim->table.philos[i].philo_mtx, INIT))
			return (0);
		i++;
	}
	return (1);
}

/**
 * @brief Initializes fork mutexes and global simulation mutexes
 * 
 * @param sim Pointer to the simulation structure  
 * @return int 1 on success, 0 on failure (memory allocation or mutex init error)
 */
static int	init_forks(t_sim *sim)
{
	int	i;

	sim->table.forks = malloc(sizeof(pthread_mutex_t) * sim->table.num_philos);
	if (!sim->table.forks)
		return (0);
	i = 0;
	while (i < sim->table.num_philos)
	{
		if (!safe_mutex_handle(&sim->table.forks[i], INIT))
			return (0);
		i++;
	}
	if (!safe_mutex_handle(&sim->table_mtx, INIT))
		return (0);
	if (!safe_mutex_handle(&sim->write_mtx, INIT))
		return (0);
	return (1);
}

/**
 * @brief Main simulation initialization function
 * 
 * @param sim Pointer to simulation structure to initialize
 * @param argv Command line arguments array containing simulation parameters
 * @param argc Number of command line arguments
 * @return int 1 on successful initialization, 0 on failure
 */
int	init_simulation(t_sim *sim, char **argv, int argc)
{
	sim->table.num_philos = ft_atoi(argv[1]);
	sim->time_die = ft_atoi(argv[2]);
	sim->time_eat = ft_atoi(argv[3]);
	sim->time_sleep = ft_atoi(argv[4]);
	sim->num_of_meals = -1;
	if (argc == 6)
		sim->num_of_meals = ft_atoi(argv[5]);
	if (sim->table.num_philos <= 0 || sim->time_die <= 0
		|| sim->time_eat <= 0 || sim->time_sleep <= 0)
		return (print_and_return("Arguments must be positive", 0));
	if (!init_forks(sim) || !init_philos(sim))
		return (print_and_return("Failed initialization", 0));
	return (1);
}
