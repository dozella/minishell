/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnearing <cnearing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 22:50:40 by cnearing          #+#    #+#             */
/*   Updated: 2022/10/30 22:50:41 by cnearing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_list
{
	void			*value;
	struct s_list	*next;
}					t_list;

typedef struct s_env
{
	char	*key;
	char	*value;
}			t_env;

typedef struct s_token
{
	int				key;
	char			*value;
}					t_token;

typedef struct s_help
{
	char	*cmd;
	char	**argv;
	int		fd;
	char	*redir_in;
	char	*redir_out;
	char	*heredok;
	int		pipe;
}		t_help;

typedef struct s_buildins_ptr
{
	int		pid;
}			t_exe;

typedef struct s_comand
{
	char			*cmd;
	char			**args;
	int				fd_in_out[3];
	int				fd_close[2];
	struct s_comand	*next;
}		t_comand;

typedef struct s_info
{
	char				**env;
	t_list				*env_list;
	t_comand			*comand;

	t_list				*token;
	t_list				*help;
	t_list				*cmd_info;
	char				*commands[7];
	char				env_f;
	char				exif_f;
	int					status;
}						t_info;

t_info	g_info;

#endif
