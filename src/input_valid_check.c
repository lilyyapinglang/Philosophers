/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_valid_check.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylang <ylang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 12:01:59 by ylang             #+#    #+#             */
/*   Updated: 2026/04/29 16:36:41 by ylang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	skip_spaces(char *str)
{
	int	i;

	i = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	return (i);
}

int	atoi_overflow(int sign)
{
	if (sign == 1)
		return (INT_MAX);
	return (INT_MIN);
}

int	ft_atoi(char *str)
{
	int		i;
	long	nbr;
	int		sign;
	int		digit;

	nbr = 0;
	sign = 1;
	if (!str)
		return (0);
	i = skip_spaces(str);
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		digit = str[i] - '0';
		if (nbr > (INT_MAX - digit) / 10)
			return (atoi_overflow(sign));
		nbr = digit + nbr * 10;
		i++;
	}
	return ((int)(nbr * sign));
}

bool	contains_only_digit(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] > '9' || argv[i][j] < '0')
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}
