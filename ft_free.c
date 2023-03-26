/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mael <mael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 21:56:04 by mael              #+#    #+#             */
/*   Updated: 2023/03/26 21:56:04 by mael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_destoy_mutex(t_var *var)
{
	unsigned int	i;

	i = 0;
	while (i < var->nb_philo)
	{
		pthread_mutex_destroy(&var->fork[i]);
		pthread_mutex_destroy(&var->last_eat[i]);
		i++;
	}
	pthread_mutex_destroy(&var->print);
	pthread_mutex_destroy(&var->check_finish);
	pthread_mutex_destroy(&var->finish_eat);
}

void	*ft_free_philo_var(t_var *var)
{
	unsigned int	i;

	if (!var)
		return (NULL);
	if (var->fork != NULL)
		free(var->fork);
	if (var->last_eat != NULL)
		free(var->last_eat);
	if (var->philo != 0)
	{
		i = 0;
		while (i < var->nb_philo)
		{
			if (var->philo[i] != NULL)
			{
				free(var->philo[i]);
			}
			i++;
		}
		free(var->philo);
	}
	free(var);
	return (NULL);
}

void	free_all(t_var *var)
{
	ft_destoy_mutex(var);
	ft_free_philo_var(var);
}
