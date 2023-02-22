/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnearing <cnearing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 22:39:03 by cnearing          #+#    #+#             */
/*   Updated: 2022/10/31 17:25:08 by cnearing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	fork_cmd(t_info *data)
{
	int	pid;
	int	status;

	pid = fork();
	if (!pid)
	{
		signal(SIGINT, SIG_DFL);
		check_command(data->comand);
		data->comand->args = add_cmd(data->comand);
		if (execve(data->comand->args[0], \
			data->comand->args, g_info.env) == -1)
		{
			printf("minishell: %s: command not found\n", \
				data->comand->args[0]);
			exit(127);
		}
	}
	waitpid(pid, &status, 0);
	status_child(status);
}

void	set_redir(int *end)
{
	dup2(end[READ_FD], STDIN_FILENO);
	dup2(end[WRITE_FD], STDOUT_FILENO);
	dup2(end[ERR_FD], STDERR_FILENO);
}

void	one_cmd(t_info *data)
{
	int	fd[3];

	fd[0] = dup(0);
	fd[1] = dup(1);
	fd[2] = dup(2);
	set_redir(data->comand->fd_in_out);
	if (ft_builtins(data->comand))
		fork_cmd(data);
	close(data->comand->fd_in_out[0]);
	close(data->comand->fd_in_out[1]);
	close(data->comand->fd_in_out[2]);
	set_redir(fd);
}

int	executor(t_info *data)
{
	g_info.status = 0;
	signal(SIGINT, SIG_IGN);
	if (data->comand->next == NULL)
		one_cmd(data);
	else
		few_cmds(count_commands(data->comand));
	free_comand(data->comand);
	return (1);
}
