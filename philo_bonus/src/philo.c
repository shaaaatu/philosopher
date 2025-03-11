/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luebina <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 18:21:50 by luebina           #+#    #+#             */
/*   Updated: 2024/09/26 18:21:56 by luebina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*monitor_routine(void *arg)
{
	t_philo	*philo;
	long	time_since_meal;

	philo = (t_philo *)arg;
	while (1)
	{
		sem_wait(philo->meals_sem);
		time_since_meal = get_time() - philo->last_meal_time;
		if (time_since_meal > philo->data->time_to_die)
		{
			sem_wait(philo->data->write_sem);
			printf("%ld %d died\n", (get_time() - philo->data->start_time) / 1000,
				philo->id);
			sem_post(philo->data->dead_sem);
			sem_post(philo->meals_sem);
			exit(1);
		}
		sem_post(philo->meals_sem);
		usleep(100);
	}
	return (NULL);
}

void	philo_routine(t_philo *philo)
{
	pthread_t	monitor;

    philo->last_meal_time = get_time();
	if (pthread_create(&monitor, NULL, &monitor_routine, philo))
		exit(1);
	pthread_detach(monitor);

	while (1)
	{
		// 自分の順番を待つ
		sem_wait(philo->data->eating_sem);

		// フォークを取得
		sem_wait(philo->data->forks_sem);
		print_status(philo, "has taken a fork");
		sem_wait(philo->data->forks_sem);
		print_status(philo, "has taken a fork");

		sem_wait(philo->meals_sem);
		philo->last_meal_time = get_time();
		sem_post(philo->meals_sem);
		print_status(philo, "is eating");
		ft_usleep(philo->data->time_to_eat);
		philo->meals_counter++;

		// フォークを解放
		sem_post(philo->data->forks_sem);
		sem_post(philo->data->forks_sem);

		if (philo->meals_counter == philo->data->limit_meals_num)
			exit(0);

		print_status(philo, "is sleeping");
		ft_usleep(philo->data->time_to_sleep);
		print_status(philo, "is thinking");
	}
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (init_data(&data, argc, argv))
		return (1);
	start_dinner(&data);
	clean_all(&data);
	return (0);
} 