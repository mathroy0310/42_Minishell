/* ************************************************************************** */
/*                                                                            */
/*                                                     ██   ██ ██████         */
/*   minishell.h                                       ██   ██      ██        */
/*                                                     ███████  █████         */
/*   By: maroy <maroy@student.42.qc>                        ██ ██             */
/*                                                          ██ ███████.qc     */
/*   Created: 2023/06/26 21:49:41 by maroy                                    */
/*   Updated: 2023/08/24 20:16:56 by maroy            >(.)__ <(.)__ =(.)__    */
/*                                                     (___/  (___/  (___/    */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*
 * -- Libraries Defines --
 */

# define READLINE_LIBRARY
# define HISTORY_LIBRARY

/*
 *-- Error messages --
 */

/*
 * -- Global defines --
 */

# define PROMPT "minishell$ "
# define PROMPT_ERROR "minishell error: "
# define NONE -1

# define BUFFER_SIZE 1024
# define MAX_TOKENS 1024

# define SQ_DELIM_CHAR 29
# define DQ_DELIM_CHAR 30

# define OK 1
# define KO 0

/*
 * -- libc Includes --
 */

# ifdef __APPLE__
#  include <limits.h> // pour PATH_MAX
# endif

# ifdef __linux__
#  include <linux/limits.h>
# endif

# include <errno.h> // pour errno
# include <fcntl.h>
# include <signal.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h> // pour EXIT_SUCCESS et EXIT_FAILURE
# include <termios.h>
# include <unistd.h>

/*
 * -- Color Codes for users --
 */

# define DEFAULT "\001\033[0;39m\002"
# define GRAY "\001\033[1;90m\002"
# define RED "\001\033[1;91m\002"
# define GREEN "\001\033[1;92m\002"
# define YELLOW "\001\033[1;93m\002"
# define BLUE "\001\033[1;94m\002"
# define MAGENTA "\001\033[1;95m\002"
# define CYAN "\001\033[1;96m\002"
# define WHITE "\001\033[0;97m\002"

/*
 * -- Libs Includes --
 */

//  Readline
# include "../libs/readline/inc/history.h"
# include "../libs/readline/inc/readline.h"
//  Libft
# include "../libs/libft/inc/libft.h"

/*
 * -- Local Includes --
 */

# include "typedefs.h"

/*
 * -- Prototypes --
 */

//DEBUG
void    DEBUG_print_token_type(t_token *tokens);
void    DEBUG_print_tab(char **tab);
void    DEBUG_print_msg(char *msg, char *arg);

// Getenv
void	init_env(t_minishell *minishell, char **envp);
char	*get_env_content(char *arg, t_list *env);

//parsing
void parse(char *src, char **dest);

void parse_tokens(t_token *tokens);
int8_t case_dollar_sign(t_minishell *minishell, t_token *tokens);
int8_t case_quoted_string(t_minishell *minishell, t_token *tokens);

// Init
int8_t	init(t_minishell *minishell, char **envp);

// Builtins
int8_t	exec_env(t_list *env);
int8_t	exec_pwd(void);

// Signal
void	sig_interrupt(int sig);

int8_t	init_token(t_minishell *minishell, char *buffer);

// Readline
int8_t	take_input(char *buffer);

// valid
int8_t	using_valid_characters(char *buff, t_minishell *minishell);

// error
int8_t	print_token_error(char c);
int8_t	print_msg_error(char *msg);

// free
void	free_env(t_list *env);
#endif