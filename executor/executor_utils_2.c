/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_string.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnearing <cnearing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 22:46:53 by cnearing          #+#    #+#             */
/*   Updated: 2022/10/30 22:46:54 by cnearing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	env_in_export(char *str)
{
	char	*arg;

	ft_putstr_fd("declare -x ", 1);
	while (*str != '=' && *str)
		ft_putchar_fd(*str++, 1);
	arg = ft_strchr(str, '=');
	if (arg)
	{
		ft_putchar_fd('=', 1);
		ft_putchar_fd('\"', 1);
		ft_putstr_fd(arg + 1, 1);
		ft_putchar_fd('\"', 1);
	}
	ft_putchar_fd('\n', 1);
}

char	**get_paths(char **env)
{
	int	i;

	i = 0;
	while (ft_strncmp(env[i], "PATH=", 5))
		i++;
	return (ft_split(env[i] + 5, ':'));
}

void	free_path(char **paths, char *path_cmd)
{
	int	i;

	i = 0;
	while (paths[i])
		free(paths[i++]);
	free(paths);
	free(path_cmd);
}

void	check_command(t_comand *c)
{
	char	**paths;
	char	*path;
	char	*path_cmd;
	int		i;

	i = 0;
	paths = get_paths(g_info.env);
	path_cmd = ft_strjoin("/", c->cmd);
	while (paths[i])
	{
		path = ft_strjoin(paths[i], path_cmd);
		if (!access(path, X_OK))
		{
			if (c->cmd)
				free(c->cmd);
			c->cmd = path;
			break ;
		}
		free(path);
		i++;
	}
	free_path(paths, path_cmd);
}
