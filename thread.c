/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mael <mael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 22:21:57 by mael              #+#    #+#             */
/*   Updated: 2023/03/26 22:21:57 by mael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_thread(t_var *var)
{
	unsigned int	i;

	i = 0;
	while (i < var->nb_philo)
	{
		var->philo[i]->last_eat = get_time();
		if (pthread_create(&var->philo[i]->philo, NULL, &routine, \
			var->philo[i]) != 0)
			return (0);
		i++;
	}
	if (var->nb_philo > 1)
	{
		if (pthread_create(&var->watcher, NULL, &watcher_routine, var) != 0)
			return (2);
	}
	return (1);
}

int	join_thread(t_var *var)
{
	unsigned int	i;

	i = 0;
	while (i < var->nb_philo)
	{
		if (pthread_join(var->philo[i]->philo, NULL) != 0)
			return (0);
		i++;
	}
	if (var->nb_philo > 1)
	{
		if (pthread_join(var->watcher, NULL) != 0)
			return (2);
	}
	return (1);
}
