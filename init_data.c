#include "philo.h"

void	assign_forks(t_philo *philo, t_fork *forks, int position)
{
	int	philo_num;

	philo_num = philo->table->philo_num;
	philo->first_fork = &forks[(position + 1) % philo_num];
	philo->second_fork = &forks[position];
	if (philo->id % 2 == 0)
	{
		philo->first_fork = &forks[position];
		philo->second_fork = &forks[(position + 1) % philo_num];
	}
}

void	init_philo(t_table *table)
{
	int		i;
	t_philo	*philo;

	i = -1;
	while (++i < table->philo_num)
	{
		philo = table->philos[i];
		philo->id = i + 1;
		philo->full = false;
		philo->meals_counter = 0;
		philo->table = table;
		assign_forks(philo, table->forks, i)
	}
}

void	init_data(t_table *table)
{
	int	i;

	i = -1;
	table->end_simulation = false;
	table->philos = malloc(sizeof(t_philo) * table->philo_num);
	table->forks = malloc(sizeof(t_fork) * table->philo_num);
	while (++i < table->philo_num)
	{
		pthread_mutex_init(&table->forks[i].fork, NULL);
		table->forks[i].fork_id = i;
	}
	philo_init(table);
}

