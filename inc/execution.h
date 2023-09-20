/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 21:37:15 by maroy             #+#    #+#             */
/*   Updated: 2023/09/19 23:58:13 by maroy            ###   ########.fr       */
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
	t_token_type type;
	char 		*filename;
	int 		is_quoted;
} t_redir;

typedef struct s_cmd
{
	int 		nbr_cmd;
	int 		args_size;
	char 		**argvs;
	int 		redir_nbr;
	t_redir 	*redir;
	t_token_type type;
} t_cmd;

typedef struct s_shell_red
{
	int 	infile;
	int		outfile;
	int 	here_doc;
	int 	error;
	char 	*filename;
} t_shell_red;

typedef struct s_state
{
	char 	**env_;
	char 	**path;
	int 	read_end;
	int 	write_end;
} t_state;

typedef struct s_data
{
	int 		saved_stdout;
	int 		saved_stdin;
	t_state 	*state;
	t_shell_red *redir;
} t_data;

/*
 * exec_main.c *
 */

void				wait_children(void);
void				execution(t_cmd *cmd, t_state *state);
void				restore_std(int saved_stdout, int saved_stdin);
uint8_t				dup_env_var(char **env);

/*
 * exec_reg_cmd.c *
 */

/// @brief executes a regular command, commands with no redirections and no pipes
/// @param cmd The command to execute
/// @param data The data structure
/// @return The exit status of the command (0 if OK, 1 if KO)
uint8_t		execute_reg_cmd(t_cmd *cmd, t_data *data);

void	find_cmd_path(t_cmd *cmd, t_data *data);

/*
 * exec_utils.c *
 */

int8_t				find_env(const char *key, char **env_pointer);
char				*get_env_var_by_key(const char *key);

/*
 * signals.c *
 */

void 		sigint_handler(int signum);

/*
 * builtins.c *
 */

uint8_t 	check_builtin(t_cmd *cmd, t_data *data);

/*
 * utils.c *
 */

<<<<<<< HEAD
int 		env_count(void);
char 		**realloc_new_env(int env_num, char *arg, char **env_pointer);
char		*find_path(char	*cmd, char **path);
/*
 * redirections.c *
 */
void		check_for_heredoc(t_data *data, t_cmd *cmd);


/*
 * here_doc.c *
 */
void		parse_here_doc(t_redir *redir, t_data *data);

/*
 * here_doc_utils.c *
 */

/// @brief Count the number of redirections of a given type
/// @param cmd The command to check
/// @param type The type of redirection to count
/// @return The number of redirections of the given type
int			token_type_count(t_cmd *cmd, t_token_type type);
/// @brief Handle the case where there's envar in here_doc
/// @param buff The buffer to parse
/// @param i The index of the buffer
/// @return The string to replace the envar with
char		*envar_here_doc(char *buff, int i);


/// @brief Execute a single command (redirections , no pipes)
/// @param cmd The command to execute
/// @param data The data structure
void	execute_single_cmd(t_cmd *cmd, t_data *data);
	
/*
* error.c *
*/

void		not_valid_id(char *arg);
void		fork_failed(void);
void		check_valid_fd(t_data *data, char *file_error, int fd);
void		print_error(char *file_error);
int8_t		path_error_print(t_cmd *cmd, t_data *data, char *possible_path);
=======
int					env_count(void);
char				**realloc_new_env(int env_num, char *arg,
						char **env_pointer);
