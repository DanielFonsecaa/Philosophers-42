/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-fons <dda-fons@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 22:37:38 by dda-fons          #+#    #+#             */
/*   Updated: 2025/10/04 20:56:05 by dda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

/**
 * @brief Converts a string to an integer (ASCII to Integer)
 * 
 * @param nptr Pointer to the null-terminated string to be interpreted
 * @return int The converted integral number as an int value
 */
int	ft_atoi(const char *nptr)
{
	int	i;
	int	sign;
	int	result;

	result = 0;
	sign = 1;
	i = 0;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign *= -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = result * 10 + (nptr[i] - '0');
		i++;
	}
	return (result * sign);
}

void	print_philo_action(t_sim *sim, int id, t_enum code)
{
	long	t_elapsed;

	t_elapsed = get_time() - sim->time_simul_start;
	if (sim->table.philos[id].is_full)
		return ;
	safe_mutex_handle(&sim->write_mtx, LOCK);
	if (code == FORK && !simulation_finished(sim))
		printf(W "%-6ld %d" R " has taken a fork\n", t_elapsed, id);
	else if (code == EAT && !simulation_finished(sim))
		printf(CYN "%-6ld %d is eating\n"RST, t_elapsed, id);
	else if (code == SLEEP && !simulation_finished(sim))
		printf(Y "%-6ld %d is sleeping\n"RST, t_elapsed, id);
	else if (code == THINK && !simulation_finished(sim))
		printf(MAG "%-6ld %d is thinking\n"RST, t_elapsed, id);
	else if (code == DIE)
		printf(RED"%-6ld %d died\n"RST, t_elapsed, id);
	safe_mutex_handle(&sim->write_mtx, UNLOCK);
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

long	get_time(void)
{
	struct timeval	tv;
	long			time;
	
	gettimeofday(&tv, NULL);
	time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time);
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
