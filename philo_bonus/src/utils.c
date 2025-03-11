/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luebina <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 18:22:26 by luebina           #+#    #+#             */
/*   Updated: 2024/09/26 18:22:36 by luebina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long	ft_atol(const char *str)
{
	long	result;
	int		sign;

	result = 0;
	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		if (result > (LONG_MAX - (*str - '0')) / 10)
			return (sign == 1 ? LONG_MAX : LONG_MIN);
		result = result * 10 + (*str - '0');
		str++;
	}
	return (result * sign);
}

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000000) + tv.tv_usec);
}

void	ft_usleep(long time)
{
	long	start;

	start = get_time();
	while ((get_time() - start) < time)
		usleep(500);
}

void	print_status(t_philo *philo, char *status)
{
	sem_wait(philo->data->write_sem);
	printf("%ld %d %s\n", (get_time() - philo->data->start_time) / 1000,
		philo->id, status);
	sem_post(philo->data->write_sem);
}

void	clean_all(t_data *data)
{
	int		i;
	char	sem_name[20];

	i = 0;
	while (i < data->philo_num)
	{
		create_sem_name(sem_name, i);
		sem_close(data->philos[i].meals_sem);
		sem_unlink(sem_name);
		i++;
	}
	sem_close(data->forks_sem);
	sem_close(data->write_sem);
	sem_close(data->dead_sem);

	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_WRITE);
	sem_unlink(SEM_DEAD);

	free(data->philos);
} 