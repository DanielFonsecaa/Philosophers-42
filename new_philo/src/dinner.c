/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-fons <dda-fons@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 12:22:08 by dda-fons          #+#    #+#             */
/*   Updated: 2025/10/04 21:54:40 by dda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	start_simulation(t_sim	*sim)
{
	int	i;
	pthread_t	monitor_t;

	i = 0;
	sim->time_simul_start = get_time();
	sim->simul_end = false;
	if (!safe_thread_handle(&monitor_t, supervisor, sim, CREATE))
		return (0);
	while (i < sim->table.num_philos)
	{
		if (!safe_thread_handle(&sim->table.philos[i].thread, philo_drill,
			&sim->table.philos[i], CREATE))
			return (0);
		i++;
	}
	if (!safe_thread_handle(&monitor_t, NULL, NULL, JOIN))
		return (0);
	i = -1;
	while (++i < sim->table.num_philos)
	{
		if (!safe_thread_handle(&sim->table.philos[i].thread, NULL, NULL, JOIN))
			return (0);
	}
	return (1);

}

static bool	check_philos_life(t_sim *sim, t_philo *philo)
{
	int		philos_full;
	int		meals;
	long	last_meal;
	if (sim->num_of_meals != -1)
	{
		philos_full = get_int(&sim->table_mtx, &sim->table.n_philos_full);
		if (philos_full == sim->table.num_philos)
		{
			set_bool(&sim->table_mtx, &sim->simul_end, true);
			return (false);
		}
	}
	last_meal = get_long(&philo->philo_mtx, &philo->last_meal_time);
	meals = get_int(&philo->philo_mtx, &philo->meals);
	
	if ((get_time() - last_meal) > sim->time_die
		&& meals != sim->num_of_meals)
	{
		set_bool(&sim->table_mtx, &sim->simul_end, true);
		print_philo_action(sim, philo->id, DIE);
		return (false);
	}
	
	return (true);
}

void	*supervisor(void *data)
{
	t_sim	*sim;
	int		i;

	sim = (t_sim *)data;
	while (!simulation_finished(sim))
	{
		i = -1;
		while (++i < sim->table.num_philos)
		{
			if (!check_philos_life(sim, &sim->table.philos[i]))
				break ;
		}
		usleep(1000);
	}
	return (NULL);
}


