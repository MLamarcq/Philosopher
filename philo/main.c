/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mael <mael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 21:47:48 by mael              #+#    #+#             */
/*   Updated: 2023/03/26 21:47:48 by mael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_var	*var;

	if (argc == 5 || argc == 6)
	{
		var = NULL;
		if (ft_error(argv) != 1)
			return (0);
		var = (init_base(var, argc, argv));
		if (!var)
			return (0);
		if (init_thread(var) != 1)
			return (0);
		if (join_thread(var) != 1)
			return (0);
		free_all(var);
	}
	else
	{
		printf("You should use 5 args like : ./philo nbr1 nbr2 nbr3 nbr4\n");
		printf("Or\n");
		printf("You should use 6 args like : ./philo nbr1 nbr2 nbr3 nbr4 nbr5");
		printf("\n");
	}
	return (0);
}
