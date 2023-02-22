/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnearing <cnearing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 22:46:48 by cnearing          #+#    #+#             */
/*   Updated: 2022/10/31 19:17:17 by cnearing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	status_child(int pid)
{
	if (WIFEXITED(pid))
		g_info.status = WEXITSTATUS(pid);
	if (WIFSIGNALED(pid))
	{
		g_info.status = WTERMSIG(pid);
		if (g_info.status != 131)
			g_info.status += 128;
	}
}

void	free_comand(t_comand *command)
{
	int			i;
	t_comand	*temp;

	while (command != NULL)
	{
		temp = command;
		if (command->cmd)
		{
			free(command->cmd);
			command->cmd = NULL;
		}
		i = 0;
		if (command->args)
		{
			while (command->args[i])
				free(command->args[i++]);
			free(command->args);
			command->args = NULL;
		}
		command = command->next;
		free(temp);
	}
}

int	count_commands(t_comand *comand)
{
	int	i;

	i = 0;
	while (comand != NULL)
	{
		i++;
		comand = comand->next;
	}
	return (i);
}

char	**add_cmd(t_comand *data)
{
	char	**copy;
	int		i;

	i = 0;
	while (data->args[i])
		i++;
	copy = malloc(sizeof(char *) * (i + 2));
	if (!copy)
		return (NULL);
	copy[i + 1] = 0;
	while (i != 0 && data->args[i - 1])
	{
		copy[i] = ft_strdup(data->args[i - 1]);
		i--;
	}
	copy[0] = ft_strdup(data->cmd);
	return (copy);
}
