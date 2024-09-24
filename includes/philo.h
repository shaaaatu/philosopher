#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <pthread.h>
#include <sys/time.h>
#include <limits.h>

typedef struct	s_table t_table;

typedef struct	s_fork
{
	pthread_mutex_t	fork;
	int				fork_id;
}				t_fork;

typedef struct	s_philo
{
	int				id;
	long			meals_counter;
	bool			full;
	long			last_meal_time;
	t_fork			*first_fork;
	t_fork			*second_fork;
	pthread_mutex_t	philo_mutex;
	pthread_t		thread_id;
	t_table			*table;
}				t_philo;

struct	s_table
{
	long			philo_num;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			limit_meals_num;
	long			start_simulation;
	long			threads_running_num;
	bool			end_simulation;
	bool			all_threads_ready;
	pthread_t		monitor;
	pthread_mutex_t	table_mutex;
	pthread_mutex_t	write_mutex;
	t_fork			*forks;
	t_philo			*philos;
};

void	parse_input(t_table *table, char **argv);
void	init_data(t_table *table);
void	start_dinner(t_table *table);
void	set_bool(pthread_mutex_t *mutex, bool *dest, bool value);
bool	get_bool(pthread_mutex_t *mutex, bool *value);
void	set_long(pthread_mutex_t *mutex, long *dest, long value);
long	get_long(pthread_mutex_t *mutex, long *value);
bool	is_simulation_done(t_table *table);
void	wait_all_threads(t_table *table);
long	gettime(char *time_code);
void	precise_usleep(long usec, t_table *table);
void	write_status(char *status, t_philo *philo);
bool	all_threads_running(pthread_mutex_t *mutex, long *threads,
		long philo_num);
void	increase_long(pthread_mutex_t *mutex, long *val);
void	*monitor_dinner(void *data);
void	thinking(t_philo *philo, bool pre_simulation);
void	de_synchronize_philos(t_philo *philo);
void	clean(t_table *table);
size_t	ft_strlen(const char *str);
int	ft_strncmp(const char *s1, const char *s2, size_t n);

#endif
