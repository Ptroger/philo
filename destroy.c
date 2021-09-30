#include "philosophers.h"

void	get_msg(int code, char *errmsg)
{
	if (code != 0)
	{
		if (code > 0)
		{
			ft_putstr_fd("Error == ", 2);
			ft_putnbr_fd(code, 2);
		}
		else
			ft_putstr_fd("Invalid args", 2);
		ft_putstr_fd(errmsg, 2);
	}
}

void free_phils(t_vars *vars)
{
	if (vars->malloced == 1)
		free(vars->philosophers);
	free(vars);
}

int	destroy(t_vars *vars, int code, char *errmsg)
{
	int	ret;
	int	i;

	i = 1;
	if (vars)
	{
		pthread_mutex_destroy(&vars->screen_lock);
		while (i <= vars->nb_phils && i <= vars->inited)
		{
			free(vars->philosophers[i].r_fork);
			ret = pthread_mutex_destroy(vars->philosophers[i].right_fork);
			if (ret != 0)
			{
				ft_putstr_fd(DESTROY_FORK, 2);
				return (ret);
			}
			i++;
		}
	}
	free_phils(vars);
	get_msg(code, errmsg);
	return (code);
}
