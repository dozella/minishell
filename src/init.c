/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dozella <dozella@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 13:51:13 by dozella           #+#    #+#             */
/*   Updated: 2022/10/31 13:51:39 by dozella          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	copy_env(t_info *info, char **env)
{
	int		i;
	int		count;

	count = 0;
	while (env[count])
		count++;
	info->env = malloc (sizeof(char *) * (count + 1));
	if (!info->env)
		return ;
	i = 0;
	while (i < count)
	{
		info->env[i] = ft_strdup(env[i]);
		i++;
	}
	info->env[i] = NULL;
}

void	env_list(t_info *info)
{
	char	**strs;
	int		i;

	i = 0;
	while (info->env[i])
	{
		strs = ft_split(info->env[i], '=');
		ft_pushback(&(info->env_list), ft_create_env(strs[0], strs[1]));
		i++;
	}
}

void	make_commands(t_info *info)
{
	info->commands[0] = "echo";
	info->commands[1] = "cd";
	info->commands[2] = "pwd";
	info->commands[3] = "export";
	info->commands[4] = "unset";
	info->commands[5] = "env";
	info->commands[6] = "exit";
}

void	init(char **env, t_info *info)
{
	info->exif_f = 0;
	info->env_f = 1;
	info->status = 0;
	copy_env(info, env);
	env_list(info);
	make_commands(info);
}
