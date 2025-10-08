/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-fons <dda-fons@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 11:50:40 by dda-fons          #+#    #+#             */
/*   Updated: 2025/10/05 14:54:13 by dda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	*philo_drill(void *data)
{
	t_sim	*sim;
	t_philo	*philo;

	philo = (t_philo *)data;
	sim = (t_sim *)philo->sim;
	if (philo->id % 2 == 0)
		usleep(100);
	while (!simulation_finished(sim))
	{
		if (!philo_eats(sim, philo))
			return (NULL);
		if (simulation_finished(sim))
			break ;
		print_philo_action(sim, philo->id, SLEEP);
		usleep(sim->time_sleep * 1000);
		if (simulation_finished(sim))
			break ;
		print_philo_action(sim, philo->id, THINK);
		usleep(((sim->time_die - sim->time_sleep - sim->time_eat) / 4) * 1000);
	}
	return (NULL);
}

bool	philo_eats(t_sim *sim, t_philo *philo)
{
	int	current_meals;
	int	num_full;

	current_meals = get_int(&philo->philo_mtx, &philo->meals);
	if (current_meals == sim->num_of_meals)
		return (0);
	if (!take_or_release_fork(sim, philo, true))
		return (0);
	current_meals++;
	set_long(&philo->philo_mtx, &philo->last_meal_time, get_time());
	set_int(&philo->philo_mtx, &philo->meals, current_meals);
	print_philo_action(sim, philo->id, EAT);
	usleep(sim->time_eat * 1000);
	take_or_release_fork(sim, philo, false);
	if (current_meals == sim->num_of_meals)
	{
		num_full = get_int(&sim->table_mtx, &sim->table.n_philos_full);
		set_int(&sim->table_mtx, &sim->table.n_philos_full, num_full + 1);
	}
	return (1);
}

bool	take_or_release_fork(t_sim *sim, t_philo *philo, bool is_taking)
{
	int	left;
	int	right;

	left = philo->left_fork;
	right = philo->right_fork;
	if (left == right && is_taking)
		return (print_philo_action(sim, philo->id, 0), 0);
	if (philo->id % 2)
	{
		left = philo->right_fork;
		right = philo->left_fork;
	}
	if (is_taking)
	{
		safe_mutex_handle(&sim->table.forks[left], LOCK);
		print_philo_action(sim, philo->id, FORK);
		if (!safe_mutex_handle(&sim->table.forks[right], LOCK))
			return (safe_mutex_handle(&sim->table.forks[left], UNLOCK));
		print_philo_action(sim, philo->id, FORK);
		return (1);
	}
	safe_mutex_handle(&sim->table.forks[left], UNLOCK);
	safe_mutex_handle(&sim->table.forks[right], UNLOCK);
	return (1);
}

void	print_philo_action(t_sim *sim, int id, t_enum code)
{
	long	t_elapsed;

	t_elapsed = get_time() - sim->time_simul_start;
	if (id <= 0 || id > sim->table.num_philos)
		return ;
	if (sim->table.philos[id - 1].is_full)
		return ;
	safe_mutex_handle(&sim->write_mtx, LOCK);
	if (code == FORK && !simulation_finished(sim))
		printf("%ld %d has taken a fork\n", t_elapsed, id);
	else if (code == EAT && !simulation_finished(sim))
		printf("%ld %d is eating\n", t_elapsed, id);
	else if (code == SLEEP && !simulation_finished(sim))
		printf("%ld %d is sleeping\n", t_elapsed, id);
	else if (code == THINK && !simulation_finished(sim))
		printf("%ld %d is thinking\n", t_elapsed, id);
	else if (code == DIE)
		printf("%ld %d died\n", t_elapsed, id);
	safe_mutex_handle(&sim->write_mtx, UNLOCK);
}
