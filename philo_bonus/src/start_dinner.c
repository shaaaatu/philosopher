/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_dinner.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luebina <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 18:21:50 by luebina           #+#    #+#             */
/*   Updated: 2024/09/26 18:21:56 by luebina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	kill_processes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_num)
	{
		kill(data->philos[i].pid, SIGKILL);
		i++;
	}
}

void	*eating_controller(void *arg)
{
	t_data	*data;
	int		i;
	int		eating_count;

	data = (t_data *)arg;
	while (1)
	{
		eating_count = data->philo_num / 2;
		if (eating_count == 0)
			eating_count = 1;

		i = 0;
		while (i < eating_count)
		{
			sem_post(data->eating_sem);
			i++;
		}
		usleep(data->time_to_eat);
	}
	return (NULL);
}

void	start_dinner(t_data *data)
{
	int			i;
	int			status;
	int			finished;
	pthread_t	controller;

	data->start_time = get_time();
	if (pthread_create(&controller, NULL, &eating_controller, data))
		exit(1);
	pthread_detach(controller);

	i = 0;
	while (i < data->philo_num)
	{
		data->philos[i].pid = fork();
		if (data->philos[i].pid == -1)
			exit(1);
		if (data->philos[i].pid == 0)
		{
			philo_routine(&data->philos[i]);
			exit(0);
		}
		else
		{
			i++;
			usleep(50);
		}
	}
	finished = 0;
	while (finished < data->philo_num)
	{
		i = waitpid(-1, &status, 0);
		if (i > 0)
		{
			if (WEXITSTATUS(status) == 1)
			{
				kill_processes(data);
				break;
			}
			finished++;
		}
	}
} 