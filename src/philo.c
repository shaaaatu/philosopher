#include "philo.h"

int	main(int argc, char **argv)
{
	t_table table;

	(void)argc;
	parse_input(&table, argv);
	init_data(&table);
	start_dinner(&table);
	printf("first_fork: %d\n", table.philos[0].first_fork->fork_id);
	printf("second_fork: %d\n", table.philos[0].second_fork->fork_id);
	printf("number of philo: %ld\n", table.philo_num);
	printf("time to die: %ld\n", table.time_to_die);
	printf("time to sleep: %ld\n", table.time_to_sleep);
	printf("time to eat: %ld\n", table.time_to_eat);
	printf("limit meals num: %ld\n", table.limit_meals_num);
	printf("start simulation: %ld\n", table.start_simulation);
	printf("end simulation: %d\n", table.end_simulation);
	return (0);
}
