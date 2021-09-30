#include "philosophers.h"

int	start_screen(t_philosopher *philo, int state)
{
	int			ret;

	usleep(100);
	printf("start screen debut %d\n", philo->id);
	if (is_philo_dead(philo) == 0
		|| (philo->vars->is_dead == philo->id && state == DEAD))
	{
		pthread_mutex_lock(&philo->vars->screen_lock);
		ft_putnbr_fd(get_time(), 1);
		ft_putstr_fd(" -- ", 1);
		ft_putstr_fd("Philosopher ", 1);
		ft_putnbr_fd(philo->id, 1);
		if (state == TAKE)
			ft_putstr_fd(TAKE_STR, 1);
		else if (state == EAT)
			ft_putstr_fd(EAT_STR, 1);
		else if (state == SLEEP)
			ft_putstr_fd(SLEEP_STR, 1);
		else if (state == THINK)
			ft_putstr_fd(THINK_STR, 1);
		else if (state == DEAD)
			ft_putstr_fd(DEAD_STR, 1);
		pthread_mutex_unlock(&philo->vars->screen_lock);
	}
	return (ret);
}

int	is_philo_dead(t_philosopher *philo)
{
	if (philo->vars->is_dead > 0)
	{
		printf("ici philo->%d\n", philo->id);
		return (1);
	}
	if (get_time() - philo->last_meal >= philo->vars->t_die)
	{
		printf("oula\n");
		philo->vars->is_dead = philo->id;
		return (1);
	}
	if (philo->meals_count >= philo->vars->nb_eats)
	{
		if (philo->vars->nb_eats > -1)
		{
			philo->vars->is_dead = philo->id;
			printf("ouencoreici  %d\n", philo->vars->is_dead);
			return (1);
		}
	}
//	printf("ouencorela\n");
	return (0);
}

void	*routine(void *data)
{
	t_philosopher	*philo;
	int				can_eat;

	philo = (t_philosopher *)data;
	pthread_mutex_unlock(philo->left_fork);
	while (is_philo_dead(philo) == 0)
	{
		can_eat = p_take(philo);
		if (can_eat == 1)
		{
			p_eat(philo);
			p_sleep(philo);
			p_think(philo);
		}
	}
	if (philo->vars->is_dead == philo->id)
		p_die(philo);
	return (NULL);
}
