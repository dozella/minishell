/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_fds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnearing <cnearing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 22:38:25 by cnearing          #+#    #+#             */
/*   Updated: 2022/10/30 22:38:54 by cnearing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	define_fds(t_comand *cmd)
{
	int	end[2];

	pipe(end);
	if (cmd->fd_in_out[WRITE_FD] == STDOUT_FILENO)
		cmd->fd_in_out[WRITE_FD] = end[WRITE_FD];
	else
		close(end[WRITE_FD]);
	if (cmd->next->fd_in_out[READ_FD] == STDIN_FILENO)
		cmd->next->fd_in_out[READ_FD] = end[READ_FD];
	else
		close(end[READ_FD]);
	if (cmd->fd_close[0] == -1)
		cmd->fd_close[0] = cmd->next->fd_in_out[READ_FD];
	else
		cmd->fd_close[1] = cmd->next->fd_in_out[READ_FD];
	if (cmd->next->fd_close[0] == -1)
		cmd->next->fd_close[0] = cmd->fd_in_out[WRITE_FD];
	else
		cmd->next->fd_close[1] = cmd->fd_in_out[WRITE_FD];
}

void	cmds_fds(t_comand *cmd, int size)
{
	t_comand	*temp;
	t_comand	*last;
	int			i;

	i = 0;
	temp = cmd;
	while (i < size && temp != NULL)
	{
		if ((size != 1) && (i != size - 1))
			define_fds(temp);
		if (i == size - 1 && (size != 1))
			temp->fd_close[0] = last->fd_in_out[WRITE_FD];
		i++;
		last = temp;
		temp = temp->next;
	}
}
