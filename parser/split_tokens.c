/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dozella <dozella@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 13:51:33 by dozella           #+#    #+#             */
/*   Updated: 2022/10/31 14:01:03 by dozella          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	copy_dollar(char *line, int *i, int *j, char *copy)
{
	int		l;
	int		k;
	char	*new;
	char	*new_help;

	k = -1;
	l = *j;
	while (line[*j] && ft_isprint(line[*j]) && line[*j] != ' ' \
		&& line[*j] != '$')
		(*j)++;
	new_help = ft_makestr((line + l), l, *j);
	new = pull_dollar(new_help);
	while (new && new[++k])
	{
		copy[*i] = new[k];
		(*i)++;
	}
	free (new);
	free (new_help);
}

char	*help_pull_quotes(char *copy, t_list *token, int *i, int *j)
{
	copy = malloc (sizeof(char *) * \
		(count_symb(((t_token *)token->value)->value) + 1));
	copy[count_symb(((t_token *)token->value)->value)] = '\0';
	while (((t_token *)token->value)->value && \
		((t_token *)token->value)->value[*j])
	{
		if (((t_token *)token->value)->value[*j] == '$')
		{
			(*j)++;
			copy_dollar(((t_token *) token->value)->value, i, j, copy);
			if (((t_token *)token->value)->value[*j] == '$')
				continue ;
			copy[*i] = ((t_token *)token->value)->value[*j];
		}
		else
			copy[*i] = ((t_token *)token->value)->value[*j];
		(*i)++;
		(*j)++;
	}
	return (copy);
}

char	*pull_quotes(t_list *token)
{
	char	*copy;
	int		i;
	int		j;

	i = 0;
	j = 0;
	copy = NULL;
	if (((t_token *)token->value)->key == FIELD)
		return (ft_strdup(((t_token *)token->value)->value));
	else
		copy = help_pull_quotes(copy, token, &i, &j);
	return (copy);
}

void	pull_redir(t_help *help, t_list *token)
{
	if (token->next == NULL)
		exit (100);
	if (help->fd != 0)
		close(help->fd);
	if (((t_token *)token->value)->key == REDIR_APPEND)
	{
		help->heredok = ft_strdup(((t_token *)token->next->value)->value);
		help->fd = open(((t_token *)token->next->value)->value, \
			O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
	else if (((t_token *)token->value)->key == REDIR_IN)
	{
		help->redir_in = ft_strdup(((t_token *)token->next->value)->value);
		help->fd = open(((t_token *)token->next->value)->value, \
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	else if (((t_token *)token->value)->key == REDIR_OUT)
	{
		help->redir_out = ft_strdup(((t_token *)token->next->value)->value);
		help->fd = open(((t_token *)token->next->value)->value, \
			O_RDONLY, 0644);
	}
}

void	split_tokens(t_info *info)
{
	t_list	*pipe;
	int		i;
	int		c_pipes;

	i = 0;
	c_pipes = count_pipes(info->token);
	while (i <= c_pipes)
	{
		ft_pushback(&(info->help), ft_create_help(info->token, i));
		i++;
	}
	pipe = ft_lstlast(info->help);
	((t_help *)pipe->value)->pipe = 0;
	((t_help *)info->help->value)->pipe = c_pipes;
}
