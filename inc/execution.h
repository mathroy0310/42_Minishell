/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 21:37:15 by maroy             #+#    #+#             */
/*   Updated: 2023/09/07 11:43:35 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

/*
 * -- Local Includes --
 */
# include "lexer.h"

typedef struct s_redir
{
	t_token_type	type;
	char			*filename;
	int				is_quoted;
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
	int				infile;
	int				outfile;
	int				here_doc;
	int				error;
}					t_shell_red;
typedef struct s_state
{
	char			**env_;
	char			**path;
	int				read_end;
	int				write_end;
}					t_state;
typedef struct s_data
{
	int				saved_stdout;
	int				saved_stdin;
	t_state			*state;
	t_shell_red		*redir;
}					t_data;

/*
 * exec.c *
 */

void				execution(t_cmd *cmd, t_state *state);

/*
 * signals.c *
 */

void			sigint_handler(int signum);

/*
 * builtins.c *
 */

uint8_t			check_builtin(t_cmd *cmd, t_data *data);


/*
 * utils.c *
 */


int		env_count(void);
char	**realloc_new_env(int env_num, char *arg, char **env_pointer);
int		find_env(char *key, char **env_pointer);

#endif