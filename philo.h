/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yli <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 17:55:50 by yli               #+#    #+#             */
/*   Updated: 2023/03/28 17:55:51 by yli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>

typedef struct s_philosopher
{
	struct s_rules	*rules;
	long long		last_meal;
	pthread_t		thread_id;
	int				id_ate;
	int				id;
	int				left_fork;
	int				right_fork;
}	t_philosopher;

typedef struct s_rules
{
	long long		first_timestamp;
	pthread_mutex_t	*fork;
	pthread_mutex_t	meal;
	pthread_mutex_t	dead;
	t_philosopher	*philos;
	int				num_philos;
	int				time_death;
	int				time_eat;
	int				time_sleep;
	int				num_times_eat;
	int				dieded;
}	t_rules;

int			ft_error(t_rules *rules, char *str);
long long	timestamp(void);
void		*ft_sleep(long long time, t_rules *rules);
void		*action_print(t_rules *rules, int id, char *str);
void		num_times_eat_check(t_rules *rules);
int			atoi_unsigned_integer(char *str);
void		ft_argument_check(char	**str);
t_rules		*init_rules(char **argv);
void		check_death(t_rules *rules);
void		*philo_action(void *philo);
void		ft_execute(t_rules *rules);
void		ft_exit(t_rules *rules, t_philosopher *philos);
void		free_rules(t_rules	*rules);
int			main(int argc, char **argv);

#endif
