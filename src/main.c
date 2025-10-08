/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-fons <dda-fons@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 11:33:47 by dda-fons          #+#    #+#             */
/*   Updated: 2025/10/05 14:40:28 by dda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

/**
 * @brief Main entry point for the Philosophers simulation program
 * 
 * @param argc Number of command line arguments
 * @param argv Array of command line argument strings:
 *             argv[1]: number_of_philosophers
 *             argv[2]: time_to_die (milliseconds)
 *             argv[3]: time_to_eat (milliseconds) 
 *             argv[4]: time_to_sleep (milliseconds)
 *             argv[5]: [optional] number_of_times_each_philosopher_must_eat
 * @return int 0 on successful completion, 1 on error
 */
int	main(int argc, char **argv)
{
	t_sim	sim;

	if (argc != 5 && argc != 6)
		return (print_and_return(ERR_INVALID_ARGS, 1));
	if (!init_simulation(&sim, argv, argc))
		return (1);
	if (!start_simulation(&sim))
	{
		free_all(&sim);
		return (1);
	}
	free_all(&sim);
	return (0);
}
