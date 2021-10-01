#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include "constants.h"
# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_vars			t_vars;
typedef struct s_philosopher	t_philosopher;

struct	s_philosopher
{
	int					id;
	int					meals_count;
	long long			last_meal;
	t_vars				*vars;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	pthread_t			thread_id;
};

struct s_vars {
	int					t_eat;
	int					is_dead;
	int					t_sleep;
	int					t_die;
	int					nb_phils;
	int					printed_death;
	int					nb_eats;
	int					inited;
	struct timeval		start;
	int					malloced;
	pthread_mutex_t		screen_lock;
	pthread_mutex_t		die_lock;
	t_philosopher		*philosophers;
};

void			ft_putstr_fd(char *str, int fd);
void			ft_putnbr_fd(int n, int fd);
int				set_vars(char **av, t_vars *vars, int ac);
int				init_fork(t_vars *vars, int i);
int				init_philosopher(t_vars *vars, int i);
void			*routine(void *data);
int				destroy(t_vars *vars, int code, char *errmsg);
void			p_eat(t_philosopher *philo);
int				p_take(t_philosopher *philo);
void			p_die(t_philosopher *philo);
void			p_sleep(t_philosopher *philo);
void			p_think(t_philosopher *philo);
void			start_screen(t_philosopher *philo, int state);
int				get_death_status(t_philosopher *philo);
int				ft_atoi(const char *str);
void			sleep_time(int time);
long long int	elapsed_time(struct timeval start);
long long int	utc_time_in_usec(struct timeval time);
void			take_forks(t_philosopher *philo, int i);
struct timeval	now(void);

#endif