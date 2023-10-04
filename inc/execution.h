/* ************************************************************************** */
/*                                                                            */
/*                                                     ██   ██ ██████         */
/*   execution.h                                       ██   ██      ██        */
/*                                                     ███████  █████         */
/*   By: maroy <maroy@student.42.qc>                        ██ ██             */
/*                                                          ██ ███████.qc     */
/*   Created: 2023/08/29 21:37:15 by maroy                                    */
/*   Updated: 2023/10/04 18:01:49 by maroy            >(.)__ <(.)__ =(.)__    */
/*                                                     (___/  (___/  (___/    */
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
	int				here_doc;
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

void	execute_pipe_redir(t_cmd *cmd, t_data *data, t_state *state);
int	execute_pipe_cmd(t_cmd *cmd, t_data *data);

/*
 * exec_main.c *
 */
/// @brief Initialize the `t_data` structure
void				init_data(t_data *data, t_state *state);
/// @brief waitpid and give `g_global->exit_status` the exit status
void				wait_children(void);

/// @brief Main Executes a command seperated by type of command
/// @param cmd The commands to execute
/// @param state The state of the shell
uint8_t				execution(t_cmd *cmd, t_state *state);


/// @brief Resotre the stdin and stdout from the saved values
/// @param saved_stdout 
/// @param saved_stdin 
void				restore_std(int saved_stdout, int saved_stdin);

/// @brief Dup the parameters in the `g_global->env_var`
/// @param env the env to dup
/// @return Exit Status (0 if OK, 1 if KO)
uint8_t				dup_env_var(char **env);

/*
 * exec_reg_cmd.c *
 */


void				check_for_errors(t_cmd *cmd, t_data *data);

/// @brief executes a regular command,
///	@brief commands with no redirections and no pipes
/// @param cmd The command to execute
/// @param data The data structure
/// @return The exit status of the command (0 if OK, 1 if KO)
uint8_t				execute_reg_cmd(t_cmd *cmd, t_data *data);


/*
 * exec_multi_cmd.c *
*/

void				execute_multi_cmd(t_cmd *cmd, t_data *data, t_state *state);


/*
 * exec_multi_cmd_utils.c *
 */
void setup_input(t_cmd *cmd, t_data *data, int j);
void setup_output(t_cmd *cmd, t_data *data, int j);


/// @brief Executes a command and check for errors
/// @param cmd The command to execute
/// @param data The data structure
/// @return The exit status of the command.
void				find_cmd_path(t_cmd *cmd, t_data *data);

/*
 * exec_utils.c *
 */


/// @brief Get the value of an environment variable
/// @param key The key of the environment variable
/// @param env_pointer The pointer to the env table
/// @return Index of the env variable
int8_t				find_env_var_index(const char *key, char **env_pointer);
/// @brief Get the value of an environment variable
/// @param key The key of the environment variable
/// @return The value of the environment variable
char				*get_env_var_by_key(const char *key);
/// @brief 
char				**realloc_new_env(int env_num, char *arg,
						char **env_pointer);
char				*find_path(char *cmd, char **path);
/*
 * signals.c *
 */

/// @brief Handle the `SIGINT` and `SIGQUIT` signal
/// @brief also handle the case where the signal is sent to a child process
/// @param signum The signal number
void				sigint_handler(int signum);


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
void				 execute_simple_pipe(t_cmd *cmd, t_data *data, t_state *state);

/*
 * handle_pipes_utils.c *
*/

void				close_all_pipes(int **fd, int nbr_cmd);

uint8_t				setup_command_pipes(t_cmd *cmd, t_data *data);

/*
 * free.c
*/

void				free_path(char **path);
void				main_free(t_data *data, t_cmd *cmd);
void				ft_freeptr(void *ptr);



/*
 * here_doc_utils.c *
 */

/// @brief Count the number of redirections of a given type
/// @param cmd The command to check
/// @param type The type of redirection to count
/// @return The number of redirections of the given type
int					token_type_count(t_cmd *cmd, t_token_type type);
/// @brief Handle the case where there's envar in here_doc
/// @param buff The buffer to parse
/// @param i The index of the buffer
/// @return The string to replace the envar with
char				*envar_here_doc(char *buff, int i);

/// @brief Execute a single command (redirections , no pipes)
/// @param cmd The command to execute
/// @param data The data structure
void				execute_single_cmd(t_cmd *cmd, t_data *data);

/*
 * error.c *
 */

void				not_valid_id(char *arg);
void				fork_failed(void);
void				check_valid_fd(t_data *data, char *file_error, int fd);
void				print_error(char *file_error);
int8_t				path_error_print(t_cmd *cmd, t_data *data,
						char *possible_path);
#endif
