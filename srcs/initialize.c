#include "philosophers.h"

int	init_philosopher(t_vars *vars, int i)
{
	int				ret;

	vars->philosophers[i].last_meal = get_time();
	vars->philosophers[i].meals_count = 0;
	vars->philosophers[i].vars = vars;
	ret = pthread_create(&(vars->philosophers[i].thread_id),
			NULL, &routine, &(vars->philosophers[i]));
	return (ret);
}

int	init_fork(t_vars *vars, int i)
{
	pthread_mutex_t	*fork;
	int				*fok;

	fok = malloc(sizeof(int));
	fork = malloc(sizeof(pthread_mutex_t));
	if (!fork || !fok)
		return (destroy(vars, -3, MALLOC_ERR));
	if (pthread_mutex_init(fork, NULL) != 0)
		return (-1);
	*fok = AVAILABLE;
	vars->philosophers[i].left_fork = fork;
	vars->philosophers[i].l_fork = fok;
	if (i > 0)
	{
		vars->philosophers[i - 1].r_fork = vars->philosophers[i].l_fork;
		vars->philosophers[i - 1].right_fork = vars->philosophers[i].left_fork;
	}
	if (i == vars->nb_phils - 1)
	{
		vars->philosophers[i].right_fork = vars->philosophers[0].left_fork;
		vars->philosophers[i].r_fork = vars->philosophers[0].l_fork;
	}
	vars->inited += 1;
	return (0);
}

int	init_philo_consts(t_vars *vars)
{
	t_philosopher	*phils;
	int				i;

	i = -1;
	phils = malloc(sizeof(t_philosopher) * vars->nb_phils);
	if (!phils)
		return (destroy(vars, -3, MALLOC_ERR));
	vars->malloced = 1;
	vars->philosophers = phils;
	while (++i < vars->nb_phils)
	{
		vars->philosophers[i].vars = vars;
		vars->philosophers[i].id = i + 1;
	}
	return (0);
}

int	set_vars(char **av, t_vars *vars, int ac)
{
	pthread_mutex_init(&vars->screen_lock, NULL);
	vars->is_dead = 0;
	vars->nb_phils = ft_atoi(av[1]);
	if (vars->nb_phils < 1)
		return (destroy(vars, -2, NB_PHIL));
	vars->t_die = ft_atoi(av[2]);
	if (vars->t_die <= 0)
		return (destroy(vars, -2, T_T_DIE));
	vars->t_eat = ft_atoi(av[3]);
	if (vars->t_eat <= 0)
		return (destroy(vars, -2, T_T_EAT));
	vars->t_sleep = ft_atoi(av[4]);
	if (vars->t_sleep <= 0)
		return (destroy(vars, -2, T_T_SLEEP));
	if (ac == 6)
	{
		vars->nb_eats = ft_atoi(av[5]);
		if (vars->nb_eats <= 0)
			return (destroy(vars, -2, NB_EATS));
	}
	else
		vars->nb_eats = -1;
	vars->is_dead = -1;
	init_philo_consts(vars);
	return (0);
}
