/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dozella <dozella@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 14:06:22 by dozella           #+#    #+#             */
/*   Updated: 2022/10/31 14:06:25 by dozella          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	index_equals(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (-1);
}

void	sort_abc(char **str, int n)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	while (i < n - 1)
	{
		j = i + 1;
		while (j < n)
		{
			if (ft_strncmp(str[i], str[j], ft_strlen(str[i])) > 0)
			{
				tmp = str[i];
				str[i] = str[j];
				str[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

char	*get_name(char *str)
{
	char	*name;
	int		i;
	int		n;

	n = index_equals(str);
	if (n == -1)
		n = ft_strlen(str);
	name = malloc(n);
	if (!name)
		return (NULL);
	i = 0;
	while (i < n)
	{
		name[i] = str[i];
		i++;
	}
	name[i] = '\0';
	return (name);
}

char	*get_env(char *name)
{
	int	length;
	int	i;

	i = 0;
	length = ft_strlen(name);
	while (g_info.env[i])
	{
		if (!ft_strncmp(g_info.env[i], name, length) \
			&& g_info.env[i][length] == '=')
			return (g_info.env[i]);
		i++;
	}
	return (NULL);
}

void	set_env(char *name, char *path)
{
	char	*env;

	env = ft_strjoin(name, path);
	add_export(env);
	free(env);
}
