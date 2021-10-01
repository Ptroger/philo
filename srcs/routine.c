#include "philosophers.h"
#include <stdio.h>

void	start_screen(t_philosopher *philo, int state)
{
	int			ret;

	pthread_mutex_lock(&philo->vars->screen_lock);
	ret = get_death_status(philo);
	if (ret == 0 || (ret == philo->id && state == DEAD))
	{
		ft_putnbr_fd(elapsed_time(philo->vars->start), 1);
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
	}
	pthread_mutex_unlock(&philo->vars->screen_lock);
}

int	is_philo_dead(t_philosopher *philo)
{
	if (philo->vars->is_dead > 0)
		return (philo->id);
	if (elapsed_time(philo->vars->start) - philo->last_meal
		>= philo->vars->t_die)
	{
		philo->vars->is_dead = philo->id;
		return (philo->id);
	}
	return (0);
}

int	get_death_status(t_philosopher *philo)
{
	int	i;

	pthread_mutex_lock(&philo->vars->die_lock);
	i = is_philo_dead(philo);
	if (i == philo->id && philo->vars->printed_death == 0)
	{
		ft_putnbr_fd(elapsed_time(philo->vars->start), 1);
		ft_putstr_fd(" -- ", 1);
		ft_putstr_fd("Philosopher ", 1);
		ft_putnbr_fd(philo->id, 1);
		ft_putstr_fd(DEAD_STR, 1);
		philo->vars->printed_death = 1;
	}
	pthread_mutex_unlock(&philo->vars->die_lock);
	return (i);
}

void	*routine(void *data)
{
	t_philosopher	*philo;
	int				is_dead;
	int				can_eat;

	is_dead = 0;
	philo = (t_philosopher *)data;
	while (is_dead == 0)
	{
		is_dead = get_death_status(philo);
		can_eat = p_take(philo);
		if (can_eat == 1)
		{
			p_eat(philo);
			p_sleep(philo);
			p_think(philo);
		}
		if (philo->meals_count == philo->vars->nb_eats)
			return (NULL);
	}
	return (NULL);
}
