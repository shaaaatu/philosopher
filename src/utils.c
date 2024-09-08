#include "philo.h"

long	gettime(char *time_code)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	if (ft_strncmp("second", time_code, ft_strlen(time_code)) == 0)
		return (tv.tv_sec + (tv.tv_usec / 1e6));
	else if (ft_strncmp("millisecond", time_code, ft_strlen(time_code)) == 0)
		return ((tv.tv_sec * 1e3) + (tv.tv_usec / 1e3));
	else if (ft_strncmp("microsecond", time_code, ft_strlen(time_code)) == 0)
		return ((tv.tv_sec * 1e6) + tv.tv_usec);
	else
		return (1337);
}

void	wait_all_threads(t_table *table)
{
	while (!get_bool(&table->table_mutex, &table->all_threads_ready))
		;
}

void	precise_usleep(long usec, t_table *table)
{
	long	start;
	long	elapsed;
	long	rem;

	start = gettime("microsecond");
	while (gettime("microsecond") - start < usec)
	{
		if (is_simulation_done(table))
			break ;
		elapsed = gettime("microsecond") - start;
		rem = usec - elapsed;
		if (rem > 1e3)
		{
			usleep(rem / 2);
		}
		else
			while (gettime("microsecond") - start < usec)
				;
	}
}

