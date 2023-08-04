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
# include <limits.h> // pour PATH_MAX
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h> // pour EXIT_SUCCESS et EXIT_FAILURE
# include <termios.h>

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
void init_env(t_minishell *minishell, char **envp);

// Init
int8_t init(t_minishell *minishell, char **envp);

// Builtins
int8_t exec_env(t_env *env);
int8_t exec_pwd(void);

// Signal
void	set_signal(void);


#endif