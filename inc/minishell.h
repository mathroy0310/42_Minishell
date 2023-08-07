/* ************************************************************************** */
/*                                                                            */
/*                                                     ██   ██ ██████         */
/*   minishell.h                                       ██   ██      ██        */
/*                                                     ███████  █████         */
/*   By: maroy <maroy@student.42.qc>                        ██ ██             */
/*                                                          ██ ███████.qc     */
/*   Created: 2023/06/26 21:49:41 by maroy                                    */
/*   Updated: 2023/08/04 13:33:26 by maroy            >(.)__ <(.)__ =(.)__    */
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
# define NONE -1

# define OK 1
# define KO 0

/*
* -- libc Includes -- 
*/

# include <errno.h> // pour errno
# include <stdint.h>

# include <linux/limits.h>
# include <limits.h> // pour PATH_MAX
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h> // pour EXIT_SUCCESS et EXIT_FAILURE
# include <termios.h>
# include <signal.h>

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

// Getenv
void    init_env(t_minishell *minishell, char **envp);
char*   get_env_value(char* arg, t_env* env);
void	free_env(t_env *env);

// Init
int8_t init(t_minishell *minishell, char **envp);

// Builtins
int8_t exec_env(t_env *env);
int8_t exec_pwd(void);

// Signal
void	sig_interrupt(int sig);

// Readline
int take_input(char *buffer);

//valid
int	using_valid_characters(char *buff, t_minishell *minishell);

//error
int	print_token_error(t_minishell *minishell, char c);
int print_msg_error(t_minishell *minishell, char *msg);

#endif