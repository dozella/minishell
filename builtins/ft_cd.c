/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnearing <cnearing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 22:09:36 by cnearing          #+#    #+#             */
/*   Updated: 2022/10/30 22:28:51 by cnearing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	change(char *path)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!chdir(path))
	{
		if (pwd)
		{
			set_env("OLDPWD=", pwd);
			free(pwd);
		}
		pwd = getcwd(NULL, 0);
		if (pwd)
		{
			set_env("PWD=", pwd);
			free(pwd);
		}
		return (1);
	}
	return (0);
}

void	change_directory(char *path)
{
	struct stat	st;

	if (change(path))
		return ;
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(path, 2);
	g_info.status = 1;
	if (stat(path, &st) == -1)
		ft_putstr_fd(": No such file or directory", 2);
	else if (!(st.st_mode & S_IXUSR))
		ft_putstr_fd(": Permission denied", 2);
	else
		ft_putstr_fd(": Not a directory", 2);
	ft_putchar_fd('\n', 2);
	g_info.status = 0;
}

void	directory_home(char *home_path, char *new_path)
{
	if (home_path)
	{
		change_directory(ft_strchr(home_path, '=') + 1);
		if (!ft_strncmp(new_path, "~/", 2))
			change_directory(new_path + 2);
	}
	else
		ft_putstr_fd("cd:, HOME not set\n", 2);
	g_info.status = 0;
}

void	directory_oldpwd(char *path)
{
	if (path)
	{
		change_directory(ft_strchr(path, '=') + 1);
		ft_putstr_fd(ft_strchr(get_env("PWD"), '=') + 1, 1);
	}
	else
		ft_putstr_fd("cd: OLDPWD not set\n", 2);
}

void	ft_cd(char **args)
{
	char	*path;

	if (args[0] && args[1])
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd("too many arguments\n", 2);
		return ;
	}
	if (!ft_strncmp(args[0], "-", 2))
	{	
		directory_oldpwd(get_env("OLDPWD"));
		ft_putstr_fd("\n", 1);
	}
	else if (!ft_strncmp(args[0], "~", 1) || !ft_strncmp(args[0], "--", 3))
		directory_home(get_env("HOME"), args[0]);
	else
	{
		path = get_env("HOME");
		if (!path || ft_strncmp(path, "~/", 2))
			change_directory(args[0]);
		else
			change_directory(ft_strjoin(ft_strchr(path, '=') + 1, args[0] + 1));
	}
}
