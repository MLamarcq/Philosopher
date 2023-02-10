#include "philo.h"

void	print_nb_error(t_var *var)
{
	free(var);
	printf("Error. You need 1 philo min to begin the simulation\n");
}

void	print_wrong_arg(t_var *var)
{
	free(var);
	printf("Philos have to eat 1 time minimum. 0 is an error\n");
}

void	mutex_error(t_var *var)
{
	unsigned int i;

	i = 0;
	if (init_mutex(var) == 2)
	{
		while (i < var->nb_philo)
		{
			pthread_mutex_destroy(&var->fork[i]);
			i++;
		}
	}
	i = 0;
	if (init_mutex(var) == 3)
	{
		while (i < var->nb_philo)
		{
			pthread_mutex_destroy(&var->fork[i]);
			pthread_mutex_destroy(&var->last_eat[i]);
			i++;
		}
	}
}

void	mutex_error_2(t_var *var)
{
	unsigned int i;

	i = 0;
	if (init_mutex(var) == 4)
	{
		while (i < var->nb_philo)
		{
			pthread_mutex_destroy(&var->fork[i]);
			pthread_mutex_destroy(&var->last_eat[i]);
			i++;
		}
		pthread_mutex_destroy(&var->print);
	}
	i = 0;
	if (init_mutex(var) == 5)
	{
		while (i < var->nb_philo)
		{
			pthread_mutex_destroy(&var->fork[i]);
			pthread_mutex_destroy(&var->last_eat[i]);
			i++;
		}
		pthread_mutex_destroy(&var->print);
		pthread_mutex_destroy(&var->check_finish);
	}
}

void	print_mutex_error(t_var *var)
{
	mutex_error(var);
	mutex_error_2(var);
	ft_free_philo_var(var);
	printf("Mutex initialization failed\n");
}