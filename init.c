/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mael <mael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 22:09:45 by mael              #+#    #+#             */
/*   Updated: 2023/03/26 22:09:45 by mael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_fork(t_var *var)
{
	unsigned int	i;

	i = 0;
	var->fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * \
		var->nb_philo);
	if (!var->fork)
		return (0);
	while (i < var->nb_philo)
	{
		if (pthread_mutex_init(&var->fork[i], 0) != 0)
			return (2);
		i++;
	}
	return (1);
}

int	init_eat(t_var *var)
{
	unsigned int	i;

	i = 0;
	var->last_eat = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) \
		* var->nb_philo);
	if (!var->last_eat)
		return (0);
	while (i < var->nb_philo)
	{
		if (pthread_mutex_init(&var->last_eat[i], 0) != 0)
			return (2);
		i++;
	}
	return (1);
}

int	init_mutex(t_var *var)
{
	if (init_fork(var) != 1)
		return (0);
	if (init_eat(var) != 1)
		return (2);
	if (pthread_mutex_init(&var->print, 0) != 0)
		return (3);
	if (pthread_mutex_init(&var->check_finish, 0) != 0)
		return (4);
	if (pthread_mutex_init(&var->finish_eat, 0) != 0)
		return (5);
	return (1);
}
