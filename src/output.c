#include "philo.h"

void	write_status(char *status, t_philo *philo)
{
	pthread_mutex_lock(&philo->table->write_mutex);
	if ((ft_strncmp(status, "take_first_fork", ft_strlen(status)) == 0
			|| ft_strncmp(status, "take_second_fork", ft_strlen(status)) == 0)
			&& !is_simulation_done(philo->table))
		printf("%d has taken a fork\n", philo->id);
	else if (ft_strncmp(status, "eating", ft_strlen(status)) == 0
			&& !is_simulation_done(philo->table))
		printf("%d is eating\n", philo->id);
	else if (ft_strncmp(status, "sleeping", ft_strlen(status)) == 0
			&& !is_simulation_done(philo->table))
		printf("%d is sleeping\n", philo->id);
	else if (ft_strncmp(status, "thinking", ft_strlen(status)) == 0
			&& !is_simulation_done(philo->table))
		printf("%d is thinking\n", philo->id);
	else if (ft_strncmp(status, "died", ft_strlen(status)) == 0
			&& !is_simulation_done(philo->table))
		printf("%d died\n", philo->id);
	pthread_mutex_unlock(&philo->table->write_mutex);
}

