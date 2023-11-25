/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 21:37:15 by maroy             #+#    #+#             */
/*   Updated: 2023/11/24 16:25:49 by maroy            ###   ########.fr       */
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
	bool			is_here_doc;
	bool			is_error;
	char			*filename;
	int				**pipe_fd;
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

void				execute_pipe_redir(t_cmd *cmd, t_data *data,
						t_state *state);
int					execute_pipe_cmd(t_cmd *cmd, t_data *data);

/*
 * exec_main.c *
 */

void				init_data(t_data *data, t_state *state);

t_u8				execution(t_cmd *cmd, t_state *state);

void				restore_std(int saved_stdout, int saved_stdin);

t_u8				dup_env_var(char **env);

/*
 * exec_reg_cmd.c *
 */

void				check_for_errors(t_cmd *cmd, t_data *data);

t_u8				check_for_permission(t_cmd *cmd);
t_u8				execute_reg_cmd(t_cmd *cmd, t_data *data);

/*
 * exec_multi_cmd.c *
 */

void				execute_multi_cmd(t_cmd *cmd, t_data *data, t_state *state);

/*
 * exec_multi_cmd_utils.c *
 */
void				setup_input(t_cmd *cmd, t_data *data, int j);
void				setup_output(t_cmd *cmd, t_data *data, int j);

void				find_cmd_path(t_cmd *cmd, t_data *data);

/*
 * exec_utils.c *
 */

int8_t				find_env_var_index(const char *key, char **env_pointer);

char				*get_env_var_by_key(const char *key);

char				**realloc_new_env(int env_num, char *arg,
						char **env_pointer);
char				*find_path(char *cmd, char **path);
/*
 * signals.c *
 */

void				sigint_handler(int signum);
void				wait_children(void);
void				signals_init(void);

/*
 * redirections.c *
 */

void				check_for_heredoc(t_data *data, t_cmd *cmd);
int8_t				redirections_setup(t_cmd *cmd, t_data *data);
void				setup_infiles(t_cmd *cmd, t_data *data, int i);
void				setup_outfiles(t_cmd *cmd, t_data *data, int i);

/*
 * here_doc.c *
 */

void				parse_here_doc(t_redir *redir, t_data *data);

/*
 * handle_pipes.c
 */

int					execute_process(t_cmd *cmd, t_data *data, int *fd);
void				execute_simple_pipe(t_cmd *cmd, t_data *data,
						t_state *state);

/*
 * handle_pipes_utils.c *
 */

void				close_all_pipes(int **fd, int nbr_cmd);

t_u8				setup_command_pipes(t_cmd *cmd, t_data *data);

/*
 * free.c
 */

void				free_path(char **path);
void				main_free(t_data *data, t_cmd *cmd);

/*
 * here_doc_utils.c *
 */

int					token_type_count(t_cmd *cmd, t_token_type type);

char				*envar_here_doc(char *buff, int i);

void				execute_single_cmd(t_cmd *cmd, t_data *data);

/*
 * error.c *
 */

void				not_valid_id(char *arg);
void				fork_failed(void);
void				check_valid_fd(t_data *data, char *file_error, int fd);
void				print_error(char *file_error);
t_s8				path_error_print(t_cmd *cmd, t_data *data,
						char *possible_path);
void				sigint_here_doc_handler(int signum);
#endif