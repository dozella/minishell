/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnearing <cnearing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 13:49:15 by dozella           #+#    #+#             */
/*   Updated: 2022/10/31 17:32:16 by cnearing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

int	main(int argc, char **argv, char **env)
{
	char	*line;

	(void)argc;
	(void)argv;
	init(env, &g_info);
	while (1)
	{
		if (accept_signals())
			exit (-1);
		line = readline("minishell: ");
		if (line == NULL)
			exit(0);
		if ((*line == '\0') || (ft_isspace(*line)))
			continue ;
		add_history(line);
		if (lexer(&g_info, line) == -1)
			continue ;
		executor(&g_info);
		free(line);
	}
}
