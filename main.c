#include "philosophers.h"

int		ft_usage(void)
{
	printf("usage = ./philosophers number etc\n");
	return (1);
}

void	start_threads(t_vars *vars)
{
	int temp;

	temp = 0;
	while (++temp <= vars->nb_phils)
	{
		init(vars, temp);
		pthread_join(vars->philosophers[temp].thread_id, NULL);
	}
}

int		main(int ac, char **av)
{
	t_vars	vars;

	if (ac < 5 || ac > 6)
		return (ft_usage());
	set_vars(av, &vars, ac);
	start_threads(&vars);

    return 0;
}
