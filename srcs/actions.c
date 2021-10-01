#include "philosophers.h"

void	p_eat(t_philosopher *philo)
{
	if (get_death_status(philo) == 0)
	{
		start_screen(philo, EAT);
		philo->last_meal = elapsed_time(philo->vars->start);
		sleep_time(philo->vars->t_eat);
		philo->meals_count++;
	}
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	p_sleep(t_philosopher *philo)
{
	if (get_death_status(philo) == 0)
	{
		start_screen(philo, SLEEP);
		sleep_time(philo->vars->t_sleep);
	}
}

void	p_think(t_philosopher *philo)
{
	if (get_death_status(philo) == 0)
		start_screen(philo, THINK);
}

int	p_take(t_philosopher *philo)
{
	int	ret;

	if (philo->vars->nb_phils == 1)
	{
		start_screen(philo, TAKE);
		while (get_death_status(philo) == 0)
			sleep_time(100);
	}
	ret = get_death_status(philo);
	if (ret == 0)
	{
		take_forks(philo, philo->id % 2);
		return (1);
	}
	return (0);
}

void	p_die(t_philosopher *philo)
{
	start_screen(philo, DEAD);
}
