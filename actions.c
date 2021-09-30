#include "philosophers.h"


void	p_eat(t_philosopher *philo)
{
	if (is_philo_dead(philo) == 0)
	{
		philo->is_eating = 1;
		start_screen(philo, EAT);
		usleep(philo->vars->t_eat * 1000);
		philo->last_meal = get_time();
		philo->meals_count++;
		philo->is_eating = 0;
	}
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	*philo->r_fork = AVAILABLE;
	*philo->l_fork = AVAILABLE;
}

void	p_sleep(t_philosopher *philo)
{
	long long start_sleep;

	if (is_philo_dead(philo) == 0)
	{
		start_sleep = get_time();
		start_screen(philo, SLEEP);
		while (get_time() - start_sleep < philo->vars->t_sleep)
		{
			if (is_philo_dead(philo) == 1)
				break;
			usleep(100);
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
		printf("la %d\n", philo->id);
		start_screen(philo, TAKE);
		printf("ici\n");
		while (is_philo_dead(philo) == 0)
			usleep(100);
	}
	if (is_philo_dead(philo) == 0)
	{
		if (*philo->l_fork == AVAILABLE)
		{
			pthread_mutex_lock(philo->right_fork);
			*philo->r_fork = UNAVAILABLE;
			start_screen(philo, TAKE);
			printf("ici\n");
			pthread_mutex_lock(philo->left_fork);
			printf("ici\n");
			*philo->l_fork = UNAVAILABLE;
			start_screen(philo, TAKE);
			return (1);
		}
	}
	return (0);
}

void	p_die(t_philosopher *philo)
{
	start_screen(philo, DEAD);
}
