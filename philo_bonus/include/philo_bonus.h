/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luebina <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 18:22:47 by luebina           #+#    #+#             */
/*   Updated: 2024/09/26 18:23:39 by luebina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <limits.h>

# define SEM_FORKS "/sem_forks"
# define SEM_WRITE "/sem_write"
# define SEM_DEAD "/sem_dead"
# define SEM_DONE "/sem_done"
# define SEM_EATING "/sem_eating"

typedef struct s_data	t_data;

typedef struct s_philo
{
	int		id;
	pid_t	pid;
	long	meals_counter;
	long	last_meal_time;
	sem_t	*meals_sem;
	t_data	*data;
}				t_philo;

struct s_data
{
	int		philo_num;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	int		limit_meals_num;
	long	start_time;
	t_philo	*philos;
	sem_t	*forks_sem;
	sem_t	*write_sem;
	sem_t	*dead_sem;
	sem_t	*done_sem;
	sem_t	*eating_sem;
};

int		init_data(t_data *data, int argc, char **argv);
void	start_dinner(t_data *data);
void	*monitor_routine(void *arg);
void	philo_routine(t_philo *philo);
long	ft_atol(const char *str);
long	get_time(void);
void	print_status(t_philo *philo, char *status);
void	clean_all(t_data *data);
void	ft_usleep(long time);
void	create_sem_name(char *dest, int num);
void	create_turn_sem_name(char *dest, int num);

#endif 