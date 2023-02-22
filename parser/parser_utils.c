/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dozella <dozella@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 13:51:25 by dozella           #+#    #+#             */
/*   Updated: 2022/10/31 14:00:47 by dozella          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_pipes(t_list	*token)
{
	int	i;

	i = 0;
	while (token)
	{
		if (((t_token *)token->value)->key == PIPE)
			i++;
		token = token->next;
	}
	return (i);
}

int	count_cmds(t_list *token, int p_i)
{
	int		pipe_num;
	int		i;

	i = 0;
	pipe_num = 0;
	while (token)
	{
		while (pipe_num < p_i)
		{
			if (((t_token *)token->value)->key == PIPE)
				pipe_num++;
			token = token->next;
		}
		if (((t_token *)token->value)->key == PIPE)
			break ;
		i++;
		token = token->next;
	}
	return (i);
}

char	*pull_dollar(char *value)
{
	t_list	*tmp;
	int		i;

	tmp = g_info.env_list;
	if (value[0] == '?')
		return (ft_itoa(g_info.status));
	else
	{
		i = 0;
		while (tmp)
		{
			if (!ft_strcmp(value, ((t_env *)tmp->value)->key))
				return (ft_strdup(((t_env *)tmp->value)->value));
			tmp = tmp->next;
		}
	}
	return (NULL);
}

int	count_dollar(char *line, int *i)
{
	int		j;
	int		k;
	char	*new;
	char	*help_new;

	j = *i + 1;
	k = 0;
	while (line[j] && ft_isprint(line[j]) && line[j] != ' ' \
		&& line[j] != '$')
		j++;
	help_new = ft_makestr((line + *i + 1), *i, j - 1);
	new = pull_dollar(help_new);
	while (new && new[k])
		k++;
	*i = j;
	free(help_new);
	free(new);
	return (k);
}

int	count_symb(char *str)
{
	int	i;
	int	counter;

	i = -1;
	counter = 0;
	while (str && str[++i])
	{
		if (str[i] == '$')
			counter += count_dollar(str, &i);
		counter++;
	}
	return (counter);
}
