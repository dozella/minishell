/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dozella <dozella@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 22:51:46 by cnearing          #+#    #+#             */
/*   Updated: 2022/10/31 13:59:11 by dozella          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_spaces(int *i, t_info *info, char *line)
{
	int	j;

	j = *i;
	while (line[j] && ft_isspace(line[j]))
		j++;
	if (j > *i)
		ft_pushback(&(info->token), ft_create_token(ft_strdup(" "), SEP));
	else
		return (0);
	*i = j;
	return (1);
}

int	check_words(int *i, t_info *info, char *line)
{
	int	j;

	j = *i;
	while (line[j] && ft_isprint(line[j]) && !ft_isspace(line[j]) && \
		line[j] != '|' && line[j] != '$' && line[j] != '>' && \
		line[j] != '<' && line[j] != '|' && line[j] != '\'' && \
		line[j] != '\"' && line[j] != '\\' && line[j] != ';')
		j++;
	if (j > *i)
		ft_pushback(&(info->token), \
			ft_create_token(ft_makestr((line + *i), *i, j), WORD));
	else
		return (0);
	*i = j;
	return (1);
}

int	check_double_quotes(int *i, t_info *info, char *line)
{
	int	j;

	j = *i;
	if (line[j] != '\"')
		return (0);
	j++;
	while (line[j] && line[j] != '\"')
		j++;
	if (!line[j])
	{
		printf("ERROR\n");
		exit(1);
	}
	if (j > *i)
		ft_pushback(&(info->token), ft_create_token \
			(ft_makestr((line + *i + 1), *i, j - 1), EXP_FIELD));
	*i = j + 1;
	return (1);
}

int	check_quotes(int	*i, t_info *info, char *line)
{
	int	j;

	j = *i;
	if (line[j] != '\'')
		return (0);
	j++;
	while (line[j] && line[j] != '\'')
		j++;
	if (!line[j])
	{
		printf("ERROR\n");
		exit(1);
	}
	if (j > *i)
		ft_pushback(&(info->token), ft_create_token \
			(ft_makestr((line + *i + 1), *i, j - 1), FIELD));
	*i = j + 1;
	return (1);
}

int	lexer(t_info *info, char *line)
{
	int	i;

	i = 0;
	while (line && line[i])
	{
		if (line[i] == '\\' || line[i] == ';')
		{
			printf("ERROR: \\, ; is not supported\n");
			free_parser(info);
			return (-1);
		}
		check_spaces(&i, info, line);
		check_pipe(&i, info, line);
		check_quotes(&i, info, line);
		check_heredoc(&i, info, line);
		check_words(&i, info, line);
		check_double_quotes(&i, info, line);
		check_dollar(&i, info, line);
		check_redirect(&i, info, line);
	}
	parser(info);
	return (0);
}
