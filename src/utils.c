#include "philo.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	int		res;

	i = 0;
	res = 0;
	while (i < n && res == 0 && (s1[i] || s2[i]))
	{
		res = ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (res);
}

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

void	clean(t_table *table)
{
	t_philo *philo;
	int		i;

	i = -1;
	while (++i < table->philo_num)
	{
		philo = table->philos + i;
		pthread_mutex_destroy(&philo->philo_mutex);
	}
	pthread_mutex_destroy(&table->write_mutex);
	pthread_mutex_destroy(&table->table_mutex);
	free(table->forks);
	free(table->philos);
}

