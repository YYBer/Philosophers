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
	pthread_mutex_lock(&(rules->dead));
	if (!philos->rules->dieded)
	{
		pthread_mutex_unlock(&(rules->dead));
		pthread_mutex_lock(&(rules->fork[philos->left_fork]));
		action_print(rules, philos->id, "has taken a fork");
		pthread_mutex_lock(&(rules->fork[philos->right_fork]));
		action_print(rules, philos->id, "has taken a fork");
		action_print(rules, philos->id, "is eating");
		pthread_mutex_lock(&(rules->meal));
		rules->philos[philos->id].last_meal = timestamp();
		pthread_mutex_unlock(&(rules->meal));
		ft_sleep(rules->time_eat, rules);
		rules->philos[philos->id].id_ate += 1;
		pthread_mutex_unlock(&(rules->fork[philos->left_fork]));
		pthread_mutex_unlock(&(rules->fork[philos->right_fork]));
		return ;
	}
	pthread_mutex_unlock(&(rules->dead));
	return ;
}

static void	*lonely_philo(t_philosopher *philos)
{
	t_rules	*rules;

	rules = philos->rules;
	pthread_mutex_lock(&(rules->fork[philos->left_fork]));
	action_print(rules, philos->id, "has taken a fork");
	usleep(rules->time_death * 1000);
	check_death(rules);
	pthread_mutex_unlock(&(rules->fork[philos->left_fork]));
	return (NULL);
}

static void	deadlock(t_philosopher *philos)
{
	int	max;

	max = philos->rules->num_philos;
	if (max % 2 == 0)
	{
		if (philos->id % 2 == 0)
			usleep(philos->rules->time_eat * 100);
	}
	else
	{
		if (philos->id == max || philos->id % 2 == 0)
			usleep(philos->rules->time_eat * 100);
	}
}

void	*philo_action(void *philo)
{
	t_rules			*rules;
	int				i;
	t_philosopher	*philos;

	i = 0;
	philos = (t_philosopher *)philo;
	deadlock(philos);
	rules = philos->rules;
	if (rules->num_philos == 1)
		return (lonely_philo(philos));
	while (!rules->dieded)
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
