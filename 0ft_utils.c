/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_ft_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yli <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 15:09:43 by yli               #+#    #+#             */
/*   Updated: 2023/03/29 15:09:44 by yli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_error(t_rules *rules, char *str)
{
	int	i;

	i = 0;
	if (rules != NULL)
		free_rules(rules);
	while (str[i])
		i++;
	write(2, "Error: ", 7);
	write(2, str, i);
	write(2, "\n", 1);
	exit(1);
}

long	long	timestamp(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return (t.tv_sec * 1000 + t.tv_usec / 1000);
}

void	action_print(t_rules *rules, int id, char *str)
{
	pthread_mutex_lock(&(rules->action));
	if (rules->dieded == 0)
		printf("%lli ms Nr. %d philo %s\n",
			timestamp() - rules->first_timestamp, id, str);
	pthread_mutex_unlock(&(rules->action));
}

void	ft_sleep(long long time_sleep, t_rules *rules)
{
	long long	wake_up;

	wake_up = time_sleep + timestamp();
	while (wake_up - timestamp() > 0)
	{
		check_death(rules);
		if (rules->dieded == 1)
			break ;
		usleep(100);
	}
}

int	num_times_eat_check(t_rules *rules)
{
	int	i;
	int	ate_time_all;

	i = 0;
	ate_time_all = 0;
	if (rules->num_times_eat)
	{
		while (i++ < rules->num_philos)
			ate_time_all += rules->philos[i].id_ate;
		if (ate_time_all >= rules->num_times_eat * rules->num_philos)
		{
			rules->all_ate_times = 1;
			rules->dieded = 1;
		}
	}
	return (rules->all_ate_times);
}