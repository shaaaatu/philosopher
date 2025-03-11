/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luebina <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 18:20:37 by luebina           #+#    #+#             */
/*   Updated: 2024/09/26 18:20:43 by luebina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	parse_input(t_data *data, int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		return (1);
	data->philo_num = ft_atol(argv[1]);
	data->time_to_die = ft_atol(argv[2]) * 1000;
	data->time_to_eat = ft_atol(argv[3]) * 1000;
	data->time_to_sleep = ft_atol(argv[4]) * 1000;
	if (argc == 6)
	{
		data->limit_meals_num = ft_atol(argv[5]);
		if (data->limit_meals_num <= 0)
			return (1);
	}
	else
		data->limit_meals_num = -1;
	if (data->philo_num < 1 || data->time_to_die < 0
		|| data->time_to_eat < 0 || data->time_to_sleep < 0)
		return (1);
	return (0);
}

static void	init_semaphores(t_data *data)
{
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_WRITE);
	sem_unlink(SEM_DEAD);
	sem_unlink(SEM_DONE);
	sem_unlink(SEM_EATING);

	data->forks_sem = sem_open(SEM_FORKS, O_CREAT, 0644, data->philo_num);
	if (data->forks_sem == SEM_FAILED)
		exit(1);
	data->write_sem = sem_open(SEM_WRITE, O_CREAT, 0644, 1);
	if (data->write_sem == SEM_FAILED)
		exit(1);
	data->dead_sem = sem_open(SEM_DEAD, O_CREAT, 0644, 0);
	if (data->dead_sem == SEM_FAILED)
		exit(1);
	data->done_sem = sem_open(SEM_DONE, O_CREAT, 0644, 0);
	if (data->done_sem == SEM_FAILED)
		exit(1);
	data->eating_sem = sem_open(SEM_EATING, O_CREAT, 0644, 0);
	if (data->eating_sem == SEM_FAILED)
		exit(1);
}

void	create_sem_name(char *dest, int num)
{
	int		i;
	char	*prefix;
	char	digit;

	prefix = "/sem_meals_";
	i = 0;
	while (prefix[i])
	{
		dest[i] = prefix[i];
		i++;
	}
	digit = num + '0';
	dest[i] = digit;
	dest[i + 1] = '\0';
}

int	init_data(t_data *data, int argc, char **argv)
{
	int		i;
	char	sem_name[20];

	if (parse_input(data, argc, argv))
		return (1);
	data->philos = malloc(sizeof(t_philo) * data->philo_num);
	if (!data->philos)
		return (1);
	init_semaphores(data);
	i = -1;
	while (++i < data->philo_num)
	{
		data->philos[i].id = i + 1;
		data->philos[i].meals_counter = 0;
		data->philos[i].data = data;

		create_sem_name(sem_name, i);
		sem_unlink(sem_name);
		data->philos[i].meals_sem = sem_open(sem_name, O_CREAT, 0644, 1);
		if (data->philos[i].meals_sem == SEM_FAILED)
			return (1);
	}
	return (0);
}
