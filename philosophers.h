#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>

typedef	struct			s_philosopher
{
	int					id;
	int					t_ate;
	p_thread_mutex		*left_fork;
	p_thread_mutex		*right_fork;
	pthread_t			thread_id;
}						t_philosopher;

typedef struct s_vars {
	int t_eat;
	int t_sleep;
	int	t_die;
	int nb_phils;
	int nb_eats;
	int error;
	t_philosopher		philosophers[250];
}				t_vars;

void	set_vars(char **av, t_vars *vars, int ac);
void	init(t_vars *vars, int i);
void	*routine(void *data);

#endif