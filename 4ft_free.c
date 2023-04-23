/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4ft_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yli <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 18:17:51 by yli               #+#    #+#             */
/*   Updated: 2023/04/23 18:17:52 by yli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_exit(t_rules *rules, t_philosopher *philos)
{
	int	i;

	i = 1;
	while (i <= rules->num_philos)
	{
		pthread_join(philos[i].thread_id, NULL);
		pthread_mutex_destroy(&rules->fork[i]);
		i++;
	}
	pthread_mutex_destroy(&(rules->action));
	free_rules(rules);
}

void	*free_rules(t_rules	*rules)
{
	if (!rules)
		return (NULL);
	if (rules->fork != NULL)
		free(rules->fork);
	if (rules->philos != NULL)
		free(rules->philos);
	free(rules);
	return (NULL);
}
