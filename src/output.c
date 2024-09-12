#include "philo.h"

void	write_status(char *status, t_philo *philo)
{
	long	elapsed;

	if (philo->full)
		return ;
	elapsed = gettime("millisecond") - philo->table->start_simulation;
	pthread_mutex_lock(&philo->table->write_mutex);
	if ((ft_strncmp(status, "take_first_fork", ft_strlen(status)) == 0
			|| ft_strncmp(status, "take_second_fork", ft_strlen(status)) == 0)
			&& !is_simulation_done(philo->table))
		printf("%-6ld%d has taken a fork\n", elapsed, philo->id);
	else if (ft_strncmp(status, "eating", ft_strlen(status)) == 0
			&& !is_simulation_done(philo->table))
		printf("%-6ld%d is eating\n", elapsed, philo->id);
	else if (ft_strncmp(status, "sleeping", ft_strlen(status)) == 0
			&& !is_simulation_done(philo->table))
		printf("%-6ld%d is sleeping\n", elapsed, philo->id);
	else if (ft_strncmp(status, "thinking", ft_strlen(status)) == 0
			&& !is_simulation_done(philo->table))
		printf("%-6ld%d is thinking\n", elapsed, philo->id);
	else if (ft_strncmp(status, "died", ft_strlen(status)) == 0
			&& !is_simulation_done(philo->table))
		printf("%-6ld%d died\n", elapsed, philo->id);
	pthread_mutex_unlock(&philo->table->write_mutex);
}

