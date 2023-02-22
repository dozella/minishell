/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnearing <cnearing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 13:51:30 by dozella           #+#    #+#             */
/*   Updated: 2022/10/31 15:52:42 by cnearing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	del_sep(t_info *info)
{
	t_list	*tmp;
	t_list	*help;

	tmp = info->token;
	help = tmp;
	while (tmp)
	{
		if (((t_token *)tmp->value)->key == SEP)
		{
			help->next = help->next->next;
			free(((t_token *)tmp->value)->value);
			free(tmp);
			tmp = help;
		}
		help = tmp;
		tmp = tmp->next;
	}
}

void	check_double_pipes(t_info *info)
{
	t_list	*tmp;

	tmp = info->token;
	while (tmp)
	{
		if (((t_token *)tmp->value)->key == PIPE && \
			((t_token *)tmp->next->value)->key == PIPE)
		{
			printf("ERROR\n");
			exit (1);
		}
		tmp = tmp->next;
	}
}

void	preparser(t_info *info)
{
	del_sep(info);
	check_double_pipes(info);
}
