/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luebina <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 18:21:50 by luebina           #+#    #+#             */
/*   Updated: 2024/09/26 18:22:10 by luebina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_table	table;

	(void)argc;
	parse_input(&table, argv);
	if (table.philo_num < 0 || table.time_to_die < 0
		|| table.time_to_eat < 0 || table.time_to_sleep < 0
		|| table.limit_meals_num < -1)
		return (0);
	init_data(&table);
	start_dinner(&table);
	clean(&table);
	return (0);
}
