/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0utils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yli <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 14:57:48 by yli               #+#    #+#             */
/*   Updated: 2023/03/29 14:57:50 by yli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_digits(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

static int	atoi_unsigned_integer(char *str)
{
	unsigned long long int	num;
	int						i;

	i = 0;
	num = 0;
	if (str[i] == '-')
		return (ft_error(NULL, "negative numbers"));
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + str[i] - '0';
		i++;
	}
	if (num > 2147483647)
		return (ft_error(NULL, "negative numbers"));
	return ((int)num);
}

int	check_input(char *str)
{
	int	num;

	if (check_digits(str))
		return (ft_error(NULL, "negative numbers"));
	num = atoi_unsigned_integer(str);
	if (num <= 0)
		return (ft_error(NULL, "negative numbers"));
	return (num);
}
