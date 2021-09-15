#include "philosophers.h"
#include <pthread.h>
#include "mutex.h"

void	init_philosopher(t_vars *vars, int i)
{
	vars->philosophers[i].id = i;

	if (pthread_create(&(vars->philosophers[i].thread_id), NULL, &routine, &(vars->philosophers[i])))
		vars->error = 1;
}

void	init_fork(t_vars *vars, int i)
{
	pthread_mutex_t	fork;

	fork = pthread_mutex_init(&fork, NULL);
	vars->philosophers[i].right_fork = fork;
	if (i > 1)
		vars->philosophers[i].left_fork = vars->philosophers[i - 1].right_fork;
	if (i == vars->nb_phils)
		vars->philosophers[1].left_fork = fork;
}

void	init(t_vars *vars, int i)
{
	init_fork(vars, i);
	init_philosopher(vars, i);
}

void	set_vars(char **av, t_vars *vars, int ac)
{
	vars->nb_phils = atoi(av[1]);
	vars->t_die = atoi(av[2]);
	vars->t_eat = atoi(av[3]);
	vars->t_sleep = atoi(av[4]);
	if (ac == 6)
		vars->nb_eats = atoi(av[5]);
}
