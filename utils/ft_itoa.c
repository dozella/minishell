/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dozella <dozella@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 13:50:01 by dozella           #+#    #+#             */
/*   Updated: 2022/10/31 13:50:34 by dozella          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	make_str(char str[50], unsigned int nb, int sign)
{
	int	i;

	i = 0;
	if (nb == 0)
		str[i++] = '0';
	while (nb > 0)
	{
		str[i] = nb % 10 + '0';
		nb = nb / 10;
		i++;
	}
	if (sign == -1)
	{
		str[i] = '-';
		i++;
	}
	str[i] = '\0';
}

static void	ft_strrev(char str[50])
{
	int		i;
	int		last;
	char	temp;

	last = ft_strlen(str) - 1;
	i = 0;
	while (str[i])
	{
		if (i < last)
		{
			temp = str[i];
			str[i] = str[last];
			str[last] = temp;
		}
		i++;
		last--;
	}
}

static char	*ft_another_strdup(char s[50])
{
	char	*str;
	int		i;

	str = (char *)malloc (sizeof(char) * (ft_strlen(s) + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (s[i])
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_itoa(int n)
{
	char			str[50];
	int				sign;
	unsigned int	nb;
	char			*result;

	sign = 1;
	if (n < 0)
	{
		sign = -1;
		nb = -n;
	}
	else
		nb = n;
	make_str(str, nb, sign);
	ft_strrev(str);
	result = ft_another_strdup(str);
	return (result);
}
