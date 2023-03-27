/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mael <mael@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 21:54:45 by mael              #+#    #+#             */
/*   Updated: 2023/03/26 21:54:45 by mael             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_check_error(char **argv)
{
	int	i;
	int	res;

	i = 1;
	if (ft_check(argv) == 0)
		return (0);
	while (argv[i])
	{
		res = ft_atoi(argv[i]);
		if (res == -1)
			return (2);
		i++;
	}
	return (1);
}

int	ft_error(char **argv)
{
	if (ft_check_error(argv) == 0)
	{
		printf("Error, invalid argument. It has to be an int\n");
		return (0);
	}
	else if (ft_check_error(argv) == 2)
	{
		printf("Error. Argument should be in int range and positive\n");
		return (2);
	}
	return (1);
}

void	print_philos_error(t_var *var)
{
	free(var);
	printf("Philos initalization failed\n");
}

// int		ft_error_init(t_var *var, int argc, char **argv)
// {
// 	if (init_base(var, argc, argv) == 0)
// 	{
// 		printf("Malloc error, var struct is not initialized\n");
// 		return (0);
// 	}
// 	else if (init_base(var, argc, argv) == (void*)1)
// 	{
// 		printf("Error. You must have, at leat, one philo minimum\n");
// 		return (2);
// 	}
// 	else if (init_base(var, argc, argv) == (void*)2)
// 	{
// 		printf("Error. Philos has to eat 1 time minimum !\n");
// 		return (3);
// 	}
// 	else if (init_base(var, argc, argv) ==(void*) 3)
// 	{
// 		printf("Error. Philos initialisation failed\n");
// 		return (4);
// 	}
// 	else if (init_base(var, argc, argv) == (void*)4)
// 	{
// 		printf("Error. Mutex initialisation failed\n");
// 		return (5);
// 	}
// 	return (1);
// }