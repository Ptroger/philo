#include "philosophers.h"

void	destroy(t_vars *vars)
{
	int	i;

	i = 0;
	while (++1 <= vars->nb_phils)
		pthread_mutex_destroy(vars->philosophers[i].right_fork);
}