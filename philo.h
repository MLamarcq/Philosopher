#ifndef PHILO
#define PHILO
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <sys/time.h>

typedef struct s_var	t_var;

typedef struct s_philo
{
	pthread_t				philo;
	long int				last_eat;
	unsigned int			id;
	int						eat_count;
	int						right;
	int						left;
	t_var					*var;
}	t_philo;

typedef struct s_var
{
	pthread_t				watcher;
	unsigned int			nb_philo;
	long int				start;
	int						check;
	int						time_to_die;
	int						time_to_eat;
	int						time_to_sleep;
	int						must_eat;
	unsigned int			satisfied;
	pthread_mutex_t			*fork;
	pthread_mutex_t			*last_eat;
	pthread_mutex_t			print;
	pthread_mutex_t			check_finish;
	pthread_mutex_t			finish_eat;
	t_philo					**philo;
}	t_var;

// ft_check.c
int				ft_check(char **argv);
int				ft_is_digit(char c);
int				ft_atoi(char *str);

//ft_error.c
int				ft_check_error(char **argv);
int				ft_error(char **argv);
int		ft_error_init(t_var *var, int argc, char **argv);

//time.c
long int		get_time(void);
int				wait_time(t_var *var, long int time_type);

//init.c
int				init_fork(t_var *var);
int				init_eat(t_var *var);
int				init_mutex(t_var *var);
t_philo			**init_philo(t_var *var);
t_var			*init_base(t_var *var, int argc, char **argv);

//thread.c
int				init_thread(t_var *var);
int     		join_thread(t_var *var);

//routine.c
void    		*routine(void * data);
int				eat_routine(t_var *var, t_philo *philo);
void			only_one(t_var *var, t_philo *philo);
int				a_philo_is_satisfied(t_var *var, t_philo *philo);
void			philo_wait_start(t_philo *philo);

//print_output.c
void			print_output(t_var	*var, int i, char *str);

//ft_check_finish.c
int				check_time_eat_time_death(t_var *var, unsigned int i);
int				philo_have_eated(t_var *var);
int				end_of_simulation(t_var *var);
void			*watcher_routine(void *data);

//ft_free.c
void			ft_destoy_mutex(t_var *var);
void			*ft_free_philo_var(t_var *var);
void			free_all(t_var *var);

#endif