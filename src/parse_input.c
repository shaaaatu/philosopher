#include "philo.h"

long	ft_atol(char *str)
{
	int		i;
	long	num;
	
	i = -1;
	num = 0;
	while (str[++i])
	{
		num = num * 10 + (str[i] - '0');
	}
	return (num);
}

void	parse_input(t_table *table, char **argv)
{
	table->philo_num = ft_atol(argv[1]);
	table->time_to_die = ft_atol(argv[2]) * 1e3;
	table->time_to_eat = ft_atol(argv[3]) * 1e3;
	table->time_to_sleep = ft_atol(argv[4]) * 1e3;
	if (argv[5])
		table->limit_meals_num = ft_atol(argv[5]);
	else
		table->limit_meals_num = -1;
}
