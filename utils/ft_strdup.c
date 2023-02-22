/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dozella <dozella@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 13:50:45 by dozella           #+#    #+#             */
/*   Updated: 2022/10/31 13:51:08 by dozella          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_strdup(const char *s)
{
	char	*str;
	int		i;

	str = malloc (sizeof(char) * (ft_strlen(s) + 1));
	if (!str)
		return (NULL);
	str[ft_strlen(s)] = '\0';
	i = 0;
	while (s && s[i])
	{
		str[i] = s[i];
		i++;
	}
	return (str);
}
