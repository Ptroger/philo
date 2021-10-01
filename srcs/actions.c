#include "philosophers.h"

void	p_eat(t_philosopher *philo)
{
	if (get_death_status(philo) == 0)
	{
		start_screen(philo, EAT);
		sleep_time(philo->vars->t_eat);
		philo->last_meal = get_time();
		philo->meals_count++;
	}
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	p_sleep(t_philosopher *philo)
{
	long long	start_sleep;

	if (get_death_status(philo) == 0)
	{
		start_sleep = get_time();
		start_screen(philo, SLEEP);
		while (get_time() - start_sleep < philo->vars->t_sleep)
		{
			if (get_death_status(philo) == 1)
				break ;
			sleep_time(100);
		}
	}
}

void	p_think(t_philosopher *philo)
{
	if (philo->vars->is_dead == 0)
		start_screen(philo, THINK);
}

int	p_take(t_philosopher *philo)
{
	if (philo->vars->nb_phils == 1)
	{
		start_screen(philo, TAKE);
		while (get_death_status(philo) == 0)
			sleep_time(100);
	}
	if (get_death_status(philo) == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		start_screen(philo, TAKE);
		pthread_mutex_lock(philo->left_fork);
		start_screen(philo, TAKE);
		return (1);
	}
	return (0);
}

void	p_die(t_philosopher *philo)
{
	start_screen(philo, DEAD);
}
