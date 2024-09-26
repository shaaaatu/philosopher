/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luebina <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 18:19:02 by luebina           #+#    #+#             */
/*   Updated: 2024/09/26 18:20:03 by luebina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	thinking(t_philo *philo, bool pre_simulation)
{
	long	t_eat;
	long	t_sleep;
	long	t_think;

	if (!pre_simulation)
		write_status("thinking", philo);
	if (philo->table->philo_num % 2 == 0)
		return ;
	t_eat = philo->table->time_to_eat;
	t_sleep = philo->table->time_to_sleep;
	t_think = t_eat * 2 - t_sleep;
	if (t_think < 0)
		t_think = 0;
	precise_usleep(t_think * 0.42, philo->table);
}

void	*lone_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_all_threads(philo->table);
	set_long(&philo->philo_mutex, &philo->last_meal_time,
		gettime("millisecond"));
	increase_long(&philo->table->table_mutex,
		&philo->table->threads_running_num);
	write_status("take_first_fork", philo);
	while (!is_simulation_done(philo->table))
		usleep(200);
	return (NULL);
}

static void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->first_fork->fork);
	write_status("take_first_fork", philo);
	pthread_mutex_lock(&philo->second_fork->fork);
	write_status("take_second_fork", philo);
	set_long(&philo->philo_mutex, &philo->last_meal_time,
		gettime("millisecond"));
	philo->meals_counter++;
	write_status("eating", philo);
	precise_usleep(philo->table->time_to_eat, philo->table);
	if (philo->table->limit_meals_num > 0
		&& philo->meals_counter == philo->table->limit_meals_num)
		set_bool(&philo->philo_mutex, &philo->full, true);
	pthread_mutex_unlock(&philo->first_fork->fork);
	pthread_mutex_unlock(&philo->second_fork->fork);
}

void	*dinner_simulation(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_threads(philo->table);
	set_long(&philo->philo_mutex, &philo->last_meal_time,
		gettime("millisecond"));
	increase_long(&philo->table->table_mutex,
		&philo->table->threads_running_num);
	de_synchronize_philos(philo);
	while (!is_simulation_done(philo->table))
	{
		if (philo->full)
			break ;
		eating(philo);
		write_status("sleeping", philo);
		precise_usleep(philo->table->time_to_sleep, philo->table);
		thinking(philo, false);
	}
	return (NULL);
}

void	start_dinner(t_table *table)
{
	int	i;

	i = -1;
	if (table->philo_num == 1)
		pthread_create(&table->philos[0].thread_id, NULL,
			lone_philo, &table->philos[0]);
	else
	{
		while (++i < table->philo_num)
			pthread_create(&table->philos[i].thread_id, NULL,
				dinner_simulation, &table->philos[i]);
	}
	pthread_create(&table->monitor, NULL, monitor_dinner, table);
	table->start_simulation = gettime("millisecond");
	set_bool(&table->table_mutex, &table->all_threads_ready, true);
	i = -1;
	while (++i < table->philo_num)
		pthread_join(table->philos[i].thread_id, NULL);
	set_bool(&table->table_mutex, &table->end_simulation, true);
	pthread_join(table->monitor, NULL);
}
