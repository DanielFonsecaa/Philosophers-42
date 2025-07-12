/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-fons <dda-fons@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 11:55:35 by dda-fons          #+#    #+#             */
/*   Updated: 2025/07/12 16:05:12 by dda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
//	argv0 	argv1	argv2	argv3	argv4	argv 5
// ./philo 	5 		800 	200 	200 	[5]
int	main(int argc, char **argv)
{
	t_table	table;

	if (argc == 5 || argc == 6)
	{
		parse_input(&table, argv);
		init_data(&table);
		start_dinner(&table);
		clean(&table);
	}
	else
	{
		error_exit("Wrong input: \n"
			GRN"Correct is ./philo 5 500 200 200 [5]"RST);
	}
}
