/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mael <mael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 22:17:44 by mael              #+#    #+#             */
/*   Updated: 2023/03/26 22:17:44 by mael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_output(t_var *var, int i, char *str)
{
	long int	current_time;

	current_time = get_time();
	if (current_time == -1)
		return ;
	pthread_mutex_lock(&var->check_finish);
	if (var->check == 0)
	{
		pthread_mutex_lock(&(var->print));
		printf("%ld %d %s\n", (current_time - var->start), i + 1, str);
		pthread_mutex_unlock(&(var->print));
	}
	pthread_mutex_unlock(&var->check_finish);
}
