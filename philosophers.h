#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include "constants.h"
# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_vars			t_vars;
typedef	struct s_philosopher	t_philosopher;
typedef struct s_buff
{
	pthread_mutex_t	mutex;
}	t_buff;

struct	s_philosopher
{
	int					id;
	int					meals_count;
	long long			last_meal;
	int					*r_fork;
	int					*l_fork;
	t_vars				*vars;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	pthread_t			thread_id;
};

struct s_vars {
	int t_think;
	int t_eat;
	int is_dead;
	int t_sleep;
	int	t_die;
	int nb_phils;
	int nb_eats;
	int error;
	int	inited;
	int malloced;
	pthread_mutex_t		screen_lock;
	t_philosopher		*philosophers;
};

void    ft_putstr_fd(char *str, int fd);
void	ft_putnbr_fd(int n, int fd);
int 	set_vars(char **av, t_vars *vars, int ac);
int 	init_fork(t_vars *vars, int i);
int 	init_philosopher(t_vars *vars, int i);
void	*routine(void *data);
int		destroy(t_vars *vars, int code, char *errmsg);
long long	get_time(void);
void	p_eat(t_philosopher *philo);
int	p_take(t_philosopher *philo);
void	p_die(t_philosopher *philo);
void	p_sleep(t_philosopher *philo);
void	p_think(t_philosopher *philo);
int		start_screen(t_philosopher *philo, int state);
int		is_philo_dead(t_philosopher *philo);
int	ft_atoi(const char *str);

#endif