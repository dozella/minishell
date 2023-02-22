/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dozella <dozella@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 13:51:27 by dozella           #+#    #+#             */
/*   Updated: 2022/10/31 13:51:39 by dozella          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_lstadd_back_c(t_comand **lst, t_comand *new)
{
	t_comand	*r;

	if (*lst == (void *)0)
		*lst = new;
	else
	{
		r = *lst;
		while (r != (void *)0)
		{
			if (r->next == (void *)0)
			{
				r->next = new;
				break ;
			}
			r = r->next;
		}
	}
}

char	**ft_mstrdup(char **s)
{
	char	**new;
	int		i;

	i = 0;
	while (s[i])
		i++;
	new = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (s[i])
	{
		new[i] = ft_strdup(s[i]);
		i++;
	}
	new[i] = NULL;
	return (new);
}

t_comand	*ft_lstnew_c(t_help *content)
{
	t_comand	*new;

	new = (t_comand *)malloc(sizeof(t_comand));
	if (!new)
		return (NULL);
	new->cmd = ft_strdup(content->cmd);
	new->args = ft_mstrdup(content->argv);
	new->fd_in_out[0] = 0;
	if (content->fd)
		new->fd_in_out[1] = content->fd;
	else
		new->fd_in_out[1] = 1;
	new->fd_in_out[2] = 2;
	new->fd_close[0] = -1;
	new->fd_close[1] = -1;
	new->next = NULL;
	return (new);
}

void	init_comand(t_info *info)
{
	t_comand	*comand;
	t_list		*temp;
	t_help		*t;

	comand = NULL;
	temp = info->help;
	if (temp != NULL)
	{
		t = ((t_help *)temp->value);
		ft_lstadd_back_c(&comand, ft_lstnew_c(t));
		temp = temp->next;
	}
	cmds_fds(comand, ((t_help *)info->help->value)->pipe + 1);
	info->comand = comand;
}

void	parser(t_info *info)
{
	preparser(info);
	split_tokens(info);
	init_comand(info);
	free_parser(info);
}
