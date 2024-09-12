#include "philo.h"

static void	thinking(t_philo *philo)
{
	write_status("thinking", philo);
}

void	*lone_philo(void *arg)
{
	t_philo *philo;

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
	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime("millisecond"));
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
	while (!is_simulation_done(philo->table))
	{
		if (philo->full)
			break;
		eating(philo);
		write_status("sleeping", philo);
		precise_usleep(philo->table->time_to_sleep, philo->table);
		thinking(philo);
	}
	return (NULL);
}

void	start_dinner(t_table *table)
{
	int	i;

	i = -1;
//	if (0 == table->nbr_lit_meals)
//		return ;
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

