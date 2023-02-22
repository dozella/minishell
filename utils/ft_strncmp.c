/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dozella <dozella@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 13:51:00 by dozella           #+#    #+#             */
/*   Updated: 2022/10/31 13:51:08 by dozella          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && str1 && str2)
	{
		if (str1[i] == '\0' || str2[i] == '\0')
		{
			return ((unsigned char)str1[i] - str2[i]);
			break ;
		}
		if (str1[i] == str2[i])
			i++;
		else
			return ((unsigned char)str1[i] - str2[i]);
	}
	return (0);
}
