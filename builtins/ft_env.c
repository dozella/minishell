/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnearing <cnearing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 22:32:53 by cnearing          #+#    #+#             */
/*   Updated: 2022/10/30 22:32:54 by cnearing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_env(char **args)
{
	int	i;

	if (args[0])
	{
		ft_putstr_fd("env: ", 2);
		ft_putstr_fd(args[0], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return ;
	}
	i = 0;
	while (g_info.env[i])
	{
		if (ft_strchr(g_info.env[i], '='))
		{
			ft_putstr_fd(g_info.env[i], 1);
			ft_putstr_fd("\n", 1);
		}
		i++;
	}
	g_info.status = 0;
}
