/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yli <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 12:47:05 by yli               #+#    #+#             */
/*   Updated: 2023/04/10 12:47:06 by yli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_rules	*rules;

	rules = NULL;
	if (argc == 5 || argc == 6)
	{
		rules = init_rules(argv);
	}
	else
		ft_error(rules, "wrong argument");
	ft_execute(rules);
	return (0);
}
