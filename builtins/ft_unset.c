/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnearing <cnearing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 22:38:13 by cnearing          #+#    #+#             */
/*   Updated: 2022/10/30 22:38:14 by cnearing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	move_up_args(int k)
{
	while (g_info.env[k + 1])
	{
		g_info.env[k] = g_info.env[k + 1];
		k++;
		if (!g_info.env[k + 1])
			g_info.env[k] = NULL;
	}
	g_info.env = ft_realloc(g_info.env, (k + 1) * sizeof(char *), \
							(k + 2) * sizeof(char *));
}

static int	check_args(char	*str)
{
	int	i;

	if (!((str[0] > 64 && str[0] < 91) || (str[0] > 96 && str[0] < 123) \
			|| str[0] == 95))
		return (0);
	i = 1;
	while (str[i])
	{
		if (!((str[i] > 64 && str[i] < 91) || \
		(str[i] > 96 && str[i] < 123) || \
		(str[i] > 47 && str[i] < 58) || str[i] == 95))
			return (0);
		i++;
	}
	return (1);
}

void	delete_arg(char	*arg)
{
	char	*temp;
	int		j;

	j = 0;
	if (!check_args(arg))
	{
		ft_putstr_fd("unset: `", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
	}
	else
	{
		while (g_info.env[j])
		{
			if (!ft_strncmp(g_info.env[j], arg, ft_strlen(arg)))
			{
				temp = g_info.env[j];
				g_info.env[j] = NULL;
				move_up_args(j);
				free(temp);
			}
			j++;
		}
	}
}

void	ft_unset(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		delete_arg(args[i]);
		i++;
	}
	g_info.status = 0;
}
