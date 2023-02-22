/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnearing <cnearing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 13:51:05 by dozella           #+#    #+#             */
/*   Updated: 2022/10/31 20:21:25 by cnearing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_list	*ft_create_help(t_list *token, int p_i)
{
	t_help	*help;
	int		counter;

	counter = count_cmds(token, p_i);
	help = malloc(sizeof(t_help));
	if (!help)
		return (NULL);
	help->argv = (char **) malloc (sizeof(char *) * (counter));
	if (!help->argv)
		return (NULL);
	help->argv[counter - 1] = NULL;
	help->fd = 0;
	help->pipe = 0;
	help->redir_in = NULL;
	help->redir_out = NULL;
	help->heredok = NULL;
	fill_argv(help, token, p_i);
	return (ft_lstnew(help));
}

void	free_strs(char **strs)
{
	int	i;

	i = 0;
	if (strs)
	{
		while (strs[i])
		{
			free(strs[i]);
			strs[i] = NULL;
			i++;
		}
		free(strs);
		strs = NULL;
	}
}
