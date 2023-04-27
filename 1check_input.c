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

int	atoi_unsigned_integer(char *str)
{
	unsigned long long int	num;
	int						i;

	i = 0;
	num = 0;
	if (check_digits(str))
		return (ft_error(NULL, "need interger"));
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + str[i] - '0';
		i++;
	}
	if (num > 2147483647)
		return (ft_error(NULL, "limit values exceeded"));
	return ((int)num);
}

void	ft_argument_check(char	**str)
{
	int	a;
	int	b;
	int	c;
	int	d;
	int	e;

	a = atoi_unsigned_integer(str[1]);
	b = atoi_unsigned_integer(str[2]);
	c = atoi_unsigned_integer(str[3]);
	d = atoi_unsigned_integer(str[4]);
	if (str[5])
		e = atoi_unsigned_integer(str[5]);
	else
		(e = 1);
	if (a <= 0 || b <= 0 || c <= 0 || d <= 0 || e <= 0)
		ft_error(NULL, "give me positive argument:/");
}
