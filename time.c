#include "philo.h"

long int	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	wait_time(t_var *var, long int time_type)
{
	long int	start;
	long int	current_time;

	if ((start = get_time()) == -1)
		return (0);
	while (1)
	{
		pthread_mutex_lock(&var->check_finish);
		if (var->check == 0)
		{
			pthread_mutex_unlock(&var->check_finish);
			if ((current_time = get_time()) == -1)
				return (2);
			if ((current_time - start >= time_type))
				return (usleep(100), 3);
			if (time_type == 0)
				return (usleep(100), 4);
			usleep(10);
		}
		else
		{
			pthread_mutex_unlock(&var->check_finish);
			break ;
		}
	}
	return (1);
}
