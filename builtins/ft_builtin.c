/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnearing <cnearing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 22:06:57 by cnearing          #+#    #+#             */
/*   Updated: 2022/10/31 16:11:28 by cnearing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	get_command(t_comand *comand)
{
	int			i;
	const char	*cmds[] = {"echo", "env", "pwd", "cd", "exit", "export",
		"unset", NULL};

	i = 0;
	while (cmds[i])
	{
		if (!ft_strncmp(cmds[i], comand->cmd, ft_strlen(cmds[i])))
			return (i);
		i++;
	}
	return (-1);
}

static void	*init_commands(void)
{
	void	(**command)(char **);

	command = malloc(sizeof(void *) * 7);
	command[0] = ft_echo;
	command[1] = ft_env;
	command[2] = ft_pwd;
	command[3] = ft_cd;
	command[4] = ft_exit;
	command[5] = ft_export;
	command[6] = ft_unset;
	return (command);
}

int	ft_builtins(t_comand *comand)
{
	int		i;
	void	(**command)(char **);

	command = init_commands();
	i = get_command(comand);
	if (i > -1)
	{
		command[i](comand->args);
		free(command);
		return (0);
	}
	free(command);
	return (1);
}
