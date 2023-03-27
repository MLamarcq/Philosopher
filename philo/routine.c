/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mael <mael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 22:20:48 by mael              #+#    #+#             */
/*   Updated: 2023/03/26 22:20:48 by mael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	eat_routine(t_var *var, t_philo *philo)
{
	pthread_mutex_lock(&(var->fork[philo->right]));
	print_output(var, philo->id, "has taken a fork");
	pthread_mutex_lock(&(var->fork[philo->left]));
	print_output(var, philo->id, "has taken a fork");
	print_output(var, philo->id, "is eating");
	pthread_mutex_lock(&(var->last_eat[philo->id]));
	philo->last_eat = get_time();
	if (philo->last_eat == -1)
		return (0);
	pthread_mutex_unlock(&(var->last_eat[philo->id]));
	wait_time(var, (long int)var->time_to_eat);
	philo->eat_count = philo->eat_count + 1;
	print_output(var, philo->id, "is sleeping");
	pthread_mutex_unlock(&(var->fork[philo->left]));
	pthread_mutex_unlock(&(var->fork[philo->right]));
	wait_time(var, (long int)var->time_to_sleep);
	return (1);
}

void	only_one(t_var *var, t_philo *philo)
{
	pthread_mutex_lock(&var->fork[philo->right]);
	print_output(var, philo->id, "has taken a fork");
	wait_time(var, (long int)var->time_to_die);
	print_output(var, philo->id, "died");
	pthread_mutex_unlock(&var->fork[philo->right]);
}

int	a_philo_is_satisfied(t_var *var, t_philo *philo)
{
	if (var->must_eat == philo->eat_count)
	{
		pthread_mutex_lock(&var->finish_eat);
		var->satisfied++;
		pthread_mutex_unlock(&var->finish_eat);
		return (0);
	}
	return (1);
}

void	philo_wait_start(t_philo *philo)
{
	if (philo->id % 2)
		usleep(1000);
	else
		usleep(500);
}

void	*routine(void *data)
{
	t_philo	*philo;
	t_var	*var;

	philo = (t_philo *)data;
	var = philo->var;
	if (var->nb_philo == 1)
		return (only_one(var, philo), (int *)0);
	philo_wait_start(philo);
	while (1)
	{
		pthread_mutex_lock(&var->check_finish);
		if (var->check == 0)
		{
			pthread_mutex_unlock(&var->check_finish);
			if (eat_routine(var, philo) == 0)
				break ;
			if (a_philo_is_satisfied(var, philo) == 0)
				break ;
			print_output(var, philo->id, "is thinking");
		}
		else
			return (pthread_mutex_unlock(&var->check_finish), (int *)2);
	}
	return ((int *)1);
}
