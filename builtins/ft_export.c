/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dozella <dozella@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 22:34:09 by cnearing          #+#    #+#             */
/*   Updated: 2022/10/31 13:57:56 by dozella          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	print_export(void)
{
	char	**export;
	int		n;
	int		i;

	n = 0;
	while (g_info.env[n] && g_info.env)
		n++;
	export = malloc(sizeof(char *) * n);
	if (!export)
		return ;
	i = 0;
	while (i < n)
	{
		export[i] = g_info.env[i];
		i++;
	}
	sort_abc(export, n);
	i = 0;
	while (i < n)
		env_in_export(export[i++]);
	free(export);
}

void	init_p(int *size_name, int *i, char **name, char *new)
{
	*i = 0;
	*name = get_name(new);
	*size_name = ft_strlen(*name);
}

void	add_export(char *new)
{
	char	*name;
	int		size_name;
	int		i;

	init_p(&size_name, &i, &name, new);
	while (g_info.env[i] && name)
	{
		if (!ft_strncmp(g_info.env[i], name, size_name) \
		&& (g_info.env[i][size_name] == '=' \
			|| g_info.env[i][size_name] == '\0'))
		{
			if (new[index_equals(new) + 1] && ft_strchr(new, '='))
			{
				free(g_info.env[i]);
				g_info.env[i] = ft_strdup(new);
			}
			free(name);
			return ;
		}
		i++;
	}
	g_info.env = ft_realloc(g_info.env, i * sizeof(char *), \
							(i + 2) * sizeof(char *));
	g_info.env[i] = ft_strdup(new);
	free(name);
}

static int	check_args(char	*str)
{
	int	i;

	if (!((str[0] > 64 && str[0] < 91) || (str[0] > 96 && str[0] < 123) || \
				str[0] == 95))
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!((str[i] > 64 && str[i] < 91) || \
		(str[i] > 96 && str[i] < 123) || \
		(str[i] > 47 && str[i] < 58) || str[i] == 95))
			return (0);
		i++;
	}
	return (1);
}

void	ft_export(char **args)
{
	int	i;

	i = 0;
	g_info.status = 0;
	while (args[i])
	{
		if (check_args(args[i]))
		{
			add_export(args[i]);
			ft_lstclear(&g_info.env_list);
			env_list(&g_info);
		}
		else
		{
			ft_putstr_fd("export: '", 2);
			ft_putstr_fd(args[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			g_info.status = 1;
		}
		i++;
	}
	if (i == 0)
		print_export();
}
