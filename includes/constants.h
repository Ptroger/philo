#ifndef CONSTANTS_H
# define CONSTANTS_H

// STATE CONSTANTS

# define AVAILABLE 0
# define UNAVAILABLE 1
# define TAKE 0
# define EAT 1
# define SLEEP 2
# define THINK 3
# define DEAD 4

// STATE STRINGS

# define TAKE_STR " has taken a fork \n"
# define EAT_STR " is eating\n"
# define SLEEP_STR " is sleeping\n"
# define THINK_STR " is thinking\n"
# define DEAD_STR " died\n"

// ARGS ERRMSGS

# define SUCCESS "all good"
# define NB_PHIL "\nnot enough or too many philosophers\n"
# define T_T_DIE "\nnot enough time to die\n"
# define T_T_EAT "\nnot enough time to eat\n"
# define T_T_SLEEP "\nnot enough time to sleep\n"
# define NB_EATS "\nneed at least one meal before death\n"
# define USAGE "\nusage = ./philo nb_phils t_die t_eat t_sleep [nb_meals]\n"

// GENERAL ERRMSG

# define INIT_PHIL "\na fork init failed\n"
# define INIT_FORK "\ncreating a philosopher failed\n"
# define DESTROY_FORK "\ndestroying fork mutex failed\n"
# define JOIN_PHIL "\njoining a philosopher failed\n"
# define MALLOC_ERR "\nmalloc failed\n"

#endif