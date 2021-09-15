#include "philosophers.h"

void	*routine(void *data)
{
	t_philosopher *philo;

	philo = (t_philosopher *)data;
	printf("je suis le philosophe [%d]\n", philo->id);

	return ((void *)philo->thread_id);
}