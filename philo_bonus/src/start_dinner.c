/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_dinner.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luebina <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 18:21:50 by luebina           #+#    #+#             */
/*   Updated: 2025/03/11 19:16:20 by luebina          ###   ########.fr       */
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

void	finish_dinner(t_data *data)
{
	int	finished;
	int	pid;
	int	status;

	finished = 0;
	while (finished < data->philo_num)
	{
		pid = waitpid(-1, &status, 0);
		if (pid > 0)
		{
			if (WEXITSTATUS(status) == 1)
			{
				kill_processes(data);
				break ;
			}
			finished++;
		}
	}
}

void	set_thread(t_data *data)
{
	pthread_t	controller;

	if (pthread_create(&controller, NULL, &eating_controller, data))
		exit(1);
	pthread_detach(controller);
}

void	start_dinner(t_data *data)
{
	int	i;

	i = 0;
	data->start_time = get_time();
	set_thread(data);
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
	finish_dinner(data);
}
