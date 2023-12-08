/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 21:37:15 by maroy             #+#    #+#             */
/*   Updated: 2023/12/08 16:24:43 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

/*
 * -- Local Includes --
 */
# include "lexer.h"
# include "minishell.h"

typedef struct s_redir
{
	t_token_type	type;
	char			*filename;
	t_bool			is_quoted;
}					t_redir;

typedef struct s_cmd
{
	int				nbr_cmd;
	int				args_size;
	char			**argvs;
	int				redir_nbr;
	t_redir			*redir;
	t_token_type	type;
}					t_cmd;

typedef struct s_shell_red
{
	t_file			*infile;
	t_file			*outfile;
	t_bool			is_here_doc;
	t_bool			is_error;
	char			*filename;
	int				**pipe_fd;
}					t_shell_red;

typedef struct s_state
{
	char			**env_;
	char			**path;
	t_u8			read_end;
	t_u8			write_end;
}					t_state;

typedef struct s_data
{
	int				saved_stdout_fd;
	int				saved_stdin_fd;
	t_state			*state;
	t_shell_red		*redir;
}					t_data;

/**
 * exec_main.c *
 */

t_u8				dup_env_var(char **env);
t_u8				execution(t_cmd *cmd, t_state *state);

/*
 * exec_multi.c *
 */

t_u8				execute_multi_cmd(t_cmd *cmd, t_data *data);

/*
 * exec_simple.c *
 */

t_u8				execute_simple_cmd(t_cmd *cmd, t_data *data);

/*
 * exec_regular.c *
 */

t_u8				execute_regular_cmd(t_cmd *cmd, t_data *data);

/*
 * free.c *
 */
void				free_data(t_data *data, t_cmd *cmd);

#endif