/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_finish.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mael <mael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 21:50:41 by mael              #+#    #+#             */
/*   Updated: 2023/03/26 21:50:41 by mael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_time_eat_time_death(t_var *var, unsigned int i)
{
	long int	current_time;

	current_time = get_time();
	if (current_time == -1)
		return (0);
	pthread_mutex_lock(&var->last_eat[i]);
	if ((current_time - var->philo[i]->last_eat) >= var->time_to_die)
	{
		pthread_mutex_unlock(&var->last_eat[i]);
		print_output(var, var->philo[i]->id, "died");
		pthread_mutex_lock(&var->check_finish);
		var->check = 1;
		pthread_mutex_unlock(&var->check_finish);
		return (2);
	}
	pthread_mutex_unlock(&var->last_eat[i]);
	return (1);
}

int	philos_have_eated(t_var *var)
{
	pthread_mutex_lock(&var->finish_eat);
	if ((var->must_eat != -1) && (var->nb_philo == var->satisfied))
	{
		pthread_mutex_unlock(&var->finish_eat);
		pthread_mutex_lock(&var->check_finish);
		var->check = 1;
		pthread_mutex_unlock(&var->check_finish);
		return (0);
	}
	else
		pthread_mutex_unlock(&var->finish_eat);
	return (1);
}

int	end_of_simulation(t_var *var)
{
	unsigned int	i;

	i = 0;
	while (i < var->nb_philo)
	{
		if (var->must_eat != -1)
		{
			if (philos_have_eated(var) == 0)
				return (2);
		}
		else if (check_time_eat_time_death(var, i) == 2)
			return (0);
		i++;
	}
	return (1);
}

void	*watcher_routine(void *data)
{
	t_var	*var;

	var = (t_var *)data;
	if (var->must_eat == 0)
		return (NULL);
	while (end_of_simulation(var) == 1)
		usleep(1000);
	if (end_of_simulation(var) != 1)
		return (NULL);
	return (NULL);
}
