/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mael <mael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 22:07:16 by mael              #+#    #+#             */
/*   Updated: 2023/03/26 22:29:36 by mael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	fill_philo(t_philo **philo, t_var *var, int i)
{
	philo[i] = (t_philo *)malloc(sizeof(t_philo) * 1);
	if (!philo[i])
		return (0);
	philo[i]->var = var;
	philo[i]->id = i;
	philo[i]->eat_count = 0;
	philo[i]->last_eat = 0;
	philo[i]->right = philo[i]->id;
	philo[i]->left = (philo[i]->id + 1) % var->nb_philo;
	if (philo[i]->id % 2)
	{
		philo[i]->right = (philo[i]->id + 1) % var->nb_philo;
		philo[i]->left = philo[i]->id;
	}
	return (1);
}

t_philo	**init_philo(t_var *var)
{
	t_philo			**philo;
	unsigned int	i;

	philo = malloc(sizeof(t_philo *) * var->nb_philo);
	if (!philo)
		return (NULL);
	i = 0;
	while (i < var->nb_philo)
	{
		if (fill_philo(philo, var, i) == 0)
			return (NULL);
		i++;
	}
	return (philo);
}

void	init_var(t_var *var)
{
	var->start = get_time();
	var->satisfied = 0;
	var->check = 0;
}

t_var	*init_base(t_var *var, int argc, char **argv)
{
	var = (t_var *)malloc(sizeof(t_var) * 1);
	if (!var)
		return (printf("Malloc error\n"), NULL);
	var->nb_philo = ft_atoi(argv[1]);
	if (var->nb_philo == 0)
		return (print_nb_error(var), NULL);
	var->time_to_die = ft_atoi(argv[2]);
	var->time_to_eat = ft_atoi(argv[3]);
	var->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
	{
		if (ft_atoi(argv[5]) == 0)
			return (print_wrong_arg(var), NULL);
		var->must_eat = ft_atoi(argv[5]);
	}
	else
		var->must_eat = -1;
	var->philo = init_philo(var);
	if (!var->philo)
		return (print_philos_error(var), NULL);
	if (init_mutex(var) != 1)
		return (print_mutex_error(var), NULL);
	init_var(var);
	return (var);
}
