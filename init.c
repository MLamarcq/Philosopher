#include "philo.h"

int	init_fork(t_var *var)
{
	unsigned int	i;

	i = 0;
	var->fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * var->nb_philo);
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

// pthread_mutex_t	*init_fork(t_var *var)
// {
// 	unsigned int i;
// 	pthread_mutex_t	*fork;

// 	i = 0;
// 	fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * var->nb_philo);
// 	if (!fork)
// 		return (NULL);
// 	while (i < var->nb_philo)
// 	{
// 		if (pthread_mutex_init(&fork[i], 0) != 0)
// 			return (NULL);
// 		i++;
// 	}
// 	return (fork);
// }

int		init_eat(t_var *var)
{
	unsigned int i;

	i = 0;
	var->last_eat = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * var->nb_philo);
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

// pthread_mutex_t	*init_eat(t_var *var)
// {
// 	unsigned int i;
// 	pthread_mutex_t	*eat;

// 	i = 0;
// 	eat = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * var->nb_philo);
// 	if (!eat)
// 		return (NULL);
// 	while (i < var->nb_philo)
// 	{
// 		if (pthread_mutex_init(&eat[i], 0) != 0)
// 			return (NULL);
// 		i++;
// 	}
// 	return (eat);
// }

int		init_mutex(t_var *var)
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

t_philo	**init_philo(t_var *var)
{
	t_philo **philo;
	unsigned int i;

	philo = malloc(sizeof(t_philo *) * var->nb_philo);
	if (!philo)
		return (NULL);
	while (i < var->nb_philo)
	{
		philo[i] = (t_philo *)malloc(sizeof(t_philo) * 1);
		if (!philo[i])
			return (NULL);
		philo[i]->var = var;
		philo[i]->id = i;
		//printf("id = %d eat_count = %d  last_eat = %ld\n", philo[i]->id, philo[i]->eat_count, philo[i]->last_eat);
		philo[i]->eat_count = 0;
		//printf("eat_count = %d\n", philo[i]->eat_count);
		philo[i]->last_eat = 0;
		//printf("last_eat = %ld\n", philo[i]->last_eat);
		philo[i]->right = philo[i]->id;
		//printf("left = %d\n", philo[i]->left);
		philo[i]->left = (philo[i]->id + 1) % var->nb_philo;
		//printf("right = %d\n", philo[i]->right);
		if (philo[i]->id % 2)
		{
			philo[i]->right = (philo[i]->id + 1) % var->nb_philo;
			//printf("res car besoin comprendre %d\n", (i + 1) % var->nb_philo);
			philo[i]->left = philo[i]->id;
		}
		//printf("id = %d, left = %d, right = %d\n", philo[i]->id, philo[i]->left, philo[i]->right);
		i++;
	}
	return (philo);
}

t_var	*init_base(t_var *var, int argc, char **argv)
{
	var = (t_var *)malloc(sizeof(t_var) * 1);
	if (!var)
		return (printf("Malloc error\n"), NULL);
	var->nb_philo = ft_atoi(argv[1]);
	if (var->nb_philo == 0)
		return (printf("Error, 1 philo min\n"), NULL);
	var->time_to_die = ft_atoi(argv[2]);
	var->time_to_eat = ft_atoi(argv[3]);
	var->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
	{
		if (ft_atoi(argv[5]) == 0)
			return (printf("Wrong arg\n"), NULL);
		var->must_eat = ft_atoi(argv[5]);
	}
	else
		var->must_eat = -1;
	var->philo = init_philo(var);
	//  unsigned int i = 0;
	// while (i < var->nb_philo)
	// {
	// 	//printf("check = %d\n", var->philo[i]->id);
	// 	printf("id = %d\n", var->philo[i]->id);
	// 	//printf("eat_count = %d\n", var->philo[i]->eat_count);
	// 	//printf("last_eat = %ld\n", var->philo[i]->last_eat);
	//  	i++;
	// }
	if (!var->philo)
		return (printf("Philo init error\n"), NULL);
	if (init_mutex(var) != 1)
		return (printf("Mutex init error\n"), NULL);
	var->start = get_time();
	var->satisfied = 0;
	var->check = 0;
	return (var);
}


// int	init_base(t_var *var, int argc, char **argv)
// {
// 	var = (t_var *)malloc(sizeof(t_var) * 1);
// 	if (!var)
// 		return (0);
// 	var->nb_philo = ft_atoi(argv[1]);
// 	//printf("nb_philo = %d\n", var->nb_philo);
// 	var->time_to_die = ft_atoi(argv[2]);
// 	//printf("die = %d\n", var->time_to_die);
// 	var->time_to_eat = ft_atoi(argv[3]);
// 	//printf("eat = %d\n", var->time_to_eat);
// 	var->time_to_sleep = ft_atoi(argv[4]);
// 	//printf("sleep = %d\n", var->time_to_sleep);
// 	if (argc == 6)
// 	{
// 		if (ft_atoi(argv[5]) == 0)
// 			return (2);
// 		var->must_eat = ft_atoi(argv[5]);
// 		//printf("must_eat = %d\n", var->must_eat);
// 	}
// 	var->philo = init_philo(var);
// 	if (!var->philo)
// 		return (3);
// 	//printf("id = %d\n", var->philo[4]->id);
// 	if (init_mutex(var) != 1)
// 		return (4);
// 	var->start = get_time();
// 	var->check = 0;
// 	//printf("start = %ld\n", (var->start) - var->start);
// 	return (1);
// }
