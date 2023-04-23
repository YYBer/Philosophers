/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3execute.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yli <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 16:58:24 by yli               #+#    #+#             */
/*   Updated: 2023/04/06 16:58:25 by yli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_eat(t_philosopher *philos)
{
	t_rules	*rules;

	rules = philos->rules;
	if (!philos->rules->dieded)
	{
		pthread_mutex_lock(&(rules->fork[philos->left_fork]));
		action_print(rules, philos->id, "has taken left fork");
		pthread_mutex_lock(&(rules->fork[philos->right_fork]));
		action_print(rules, philos->id, "has taken right fork");
		action_print(rules, philos->id, "is eating");
		rules->philos[philos->id].last_meal = timestamp();
		ft_sleep(rules->time_eat, rules);
		rules->philos[philos->id].id_ate += 1;
		pthread_mutex_unlock(&(rules->fork[philos->left_fork]));
		pthread_mutex_unlock(&(rules->fork[philos->right_fork]));
	}
}

void	check_death(t_rules *rules)
{
	int	i;

	i = 1;
	while (i <= rules->num_philos)
	{
		if ((timestamp() - rules->philos[i].last_meal) > rules->time_death)
		{
			action_print(rules, rules->philos[i].id, "died");
			rules->dieded = 1;
			break ;
		}
		i++;
	}
}

static void	*lonely_philo(t_philosopher *philos)
{
	t_rules	*rules;

	rules = philos->rules;
	pthread_mutex_lock(&(rules->fork[philos->left_fork]));
	action_print(rules, philos->id, "has taken left fork");
	usleep(rules->time_death * 1000);
	action_print(rules, philos->id, "died");
	pthread_mutex_unlock(&(rules->fork[philos->left_fork]));
	return (NULL);
}

void	*philo_action(void *philo)
{
	t_rules			*rules;
	int				i;
	t_philosopher	*philos;

	i = 0;
	philos = (t_philosopher *)philo;
	if (philos->id % 2 == 0)
		usleep(philos->rules->time_eat * 100);
	rules = philos->rules;
	if (rules->num_philos == 1)
		return (lonely_philo(philos));
	while (!rules->dieded && rules->all_ate_times == 0)
	{
		philo_eat(philos);
		num_times_eat_check(rules);
		action_print(rules, philos->id, "is sleeping");
		ft_sleep(rules->time_sleep, rules);
		action_print(rules, philos->id, "is thinking");
		check_death(rules);
		i++;
	}
	return (NULL);
}

void	ft_execute(t_rules *rules)
{
	t_philosopher	*philos;
	int				i;

	philos = rules->philos;
	rules->first_timestamp = timestamp();
	i = 1;
	while (i <= rules->num_philos)
	{
		if (pthread_create(&(philos[i].thread_id), NULL,
				philo_action, &(philos[i])))
			ft_error(rules, "pthread_create failed");
		i++;
	}
	ft_exit(rules, philos);
}
