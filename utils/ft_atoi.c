/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dozella <dozella@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 13:49:42 by dozella           #+#    #+#             */
/*   Updated: 2022/10/31 13:50:34 by dozella          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	norm_l(int *i, int *z, long *n)
{
	*i = 0;
	*z = 1;
	*n = 0;
}

int	ft_atoi(const char *str)
{
	long	n;
	int		i;
	int		z;

	norm_l(&i, &z, &n);
	while (str[i] == ' ' || (str[i] > 8 && str[i] < 14))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			z = -1;
		i++;
	}
	while (str[i] != '\0' && (str[i] >= 48 && str[i] <= 57))
	{
		if (n * z > 2147483647)
			return (-1);
		else
			if (n * z < -2147483648)
				return (0);
		n = n * 10 + (str[i] - 48);
		i ++;
	}
	return (n * z);
}
