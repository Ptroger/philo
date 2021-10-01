#include "philosophers.h"

static int	join_threads(t_vars *vars)
{
	int	temp;
	int	ret;

	temp = -1;
	while (++temp < vars->nb_phils)
	{
		ret = pthread_join(vars->philosophers[temp].thread_id, NULL);
		if (ret == -1)
			return (destroy(vars, 3, JOIN_PHIL));
	}
	return (0);
}

static int	start_threads(t_vars *vars)
{
	int				temp;
	int				ret;

	temp = 0;
	while (temp < vars->nb_phils)
	{
		ret = init_fork(vars, temp);
		if (ret == -1)
			return (destroy(vars, 1, INIT_FORK));
		temp++;
	}
	temp = 0;
	while (temp < vars->nb_phils)
	{
		ret = init_philosopher(vars, temp);
		sleep_time(100);
		if (ret == -1)
			return (destroy(vars, 2, INIT_PHIL));
		temp++;
	}
	ret = join_threads(vars);
	if (ret == -1)
		return (-1);
	return (0);
}

int	main(int ac, char **av)
{
	t_vars	*vars;
	int		ret;

	vars = malloc(sizeof(t_vars));
	vars->inited = 0;
	vars->malloced = 0;
	pthread_mutex_init(&vars->screen_lock, NULL);
	pthread_mutex_init(&vars->die_lock, NULL);
	vars->nb_phils = 0;
	if (ac < 5 || ac > 6)
		return (destroy(vars, -1, USAGE));
	ret = set_vars(av, vars, ac);
	if (ret != 0)
		return (-1);
	ret = start_threads(vars);
	if (ret != 0)
		return (-1);
	destroy(vars, 0, SUCCESS);
	return (0);
}
