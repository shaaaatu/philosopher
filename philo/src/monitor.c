/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luebina <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 18:20:11 by luebina           #+#    #+#             */
/*   Updated: 2024/09/26 18:20:31 by luebina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	philo_died(t_philo *philo)
{
	long	elapsed;
	long	t_to_die;

	if (get_bool(&philo->philo_mutex, &philo->full))
		return (false);
	elapsed = gettime("millisecond") - get_long(&philo->philo_mutex,
			&philo->last_meal_time);
	t_to_die = philo->table->time_to_die / 1e3;
	if (elapsed > t_to_die)
		return (true);
	return (false);
}

void	*monitor_dinner(void *data)
{
	int		i;
	t_table	*table;

	table = (t_table *)data;
	while (!all_threads_running(&table->table_mutex,
			&table->threads_running_num, table->philo_num))
		;
	while (!is_simulation_done(table))
	{
		i = -1;
		while (++i < table->philo_num && !is_simulation_done(table))
		{
			if (philo_died(table->philos + i))
			{
				write_status("died", table->philos + i);
				set_bool(&table->table_mutex, &table->end_simulation, true);
			}
		}
	}
	return (NULL);
}
