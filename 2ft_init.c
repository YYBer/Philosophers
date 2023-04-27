/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2init.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yli <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 11:48:21 by yli               #+#    #+#             */
/*   Updated: 2023/04/06 11:48:23 by yli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static	void	init_mutex(t_rules *rules)
{
	int	i;

	rules->fork = malloc(sizeof(pthread_mutex_t) * (rules->num_philos + 1));
	if (!rules->fork)
		ft_error(rules, "init failed");
	i = rules->num_philos + 1;
	while (--i >= 1)
		if (pthread_mutex_init(&(rules->fork[i]), NULL))
			ft_error(rules, "init failed");
	if (pthread_mutex_init(&(rules->meal), NULL))
		ft_error(rules, "init failed");
	if (pthread_mutex_init(&(rules->dead), NULL))
		ft_error(rules, "init failed");
}

static	t_philosopher	*init_philosophers(t_rules *rules)
{
	t_philosopher	*philos;
	int				i;
	int				max;

	i = 0;
	max = rules->num_philos;
	philos = malloc(sizeof(t_philosopher) * (rules->num_philos + 1));
	if (!philos)
		ft_error(rules, "init failed");
	while (i <= rules->num_philos)
	{
		philos[i].rules = rules;
		philos[i].id = i;
		philos[i].left_fork = i - 1;
		philos[1].left_fork = max;
		philos[i].right_fork = i;
		philos[i].id_ate = 0;
		philos[i].last_meal = timestamp();
		i++;
	}
	return (philos);
}

t_rules	*init_rules(char **argv)
{
	t_rules	*rules;

	ft_argument_check(argv);
	rules = malloc(sizeof(t_rules) * 1);
	if (!rules)
		ft_error(rules, "init failed");
	rules->num_philos = atoi_unsigned_integer(argv[1]);
	rules->time_death = atoi_unsigned_integer(argv[2]);
	rules->time_eat = atoi_unsigned_integer(argv[3]);
	rules->time_sleep = atoi_unsigned_integer(argv[4]);
	rules->dieded = 0;
	rules->philos = init_philosophers(rules);
	if (argv[5])
		rules->num_times_eat = atoi_unsigned_integer(argv[5]);
	else
		rules->num_times_eat = 0;
	init_mutex(rules);
	return (rules);
}
