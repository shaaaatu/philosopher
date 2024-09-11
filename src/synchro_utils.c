#include "philo.h"

void	wait_all_threads(t_table *table)
{
	while (!get_bool(&table->table_mutex, &table->all_threads_ready))
		;
}

bool	all_threads_running(pthread_mutex_t *mutex, long *threads,
		long philo_num)
{
	bool	ret;

	ret = false;
	pthread_mutex_lock(mutex);
	if (*threads == philo_num)
		ret = true;
	pthread_mutex_unlock(mutex);
	return (ret);
}

void	increase_long(pthread_mutex_t *mutex, long *val)
{
	pthread_mutex_lock(mutex);
	(*val)++;
	pthread_mutex_unlock(mutex);
}

