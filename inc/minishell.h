/* ************************************************************************** */
/*                                                                            */
/*                                                     ██   ██ ██████         */
/*   minishell.h                                       ██   ██      ██        */
/*                                                     ███████  █████         */
/*   By: maroy <maroy@student.42.qc>                        ██ ██             */
/*                                                          ██ ███████.qc     */
/*   Created: 2023/06/26 21:49:41 by maroy                                    */
/*   Updated: 2023/07/31 17:55:54 by maroy            >(.)__ <(.)__ =(.)__    */
/*                                                     (___/  (___/  (___/    */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define OK 1
# define KO 0

# define ERROR_RL_H "\033[1;31m ERROR 🛑 : Failed to read history file \n\033[0m"
#define HISTORY_FILE ".minishell_history"
# define READLINE_LIBRARY
# define HISTORY_LIBRARY

# define PROMPT "minishell$ "

# include <stdint.h>
# include <limits.h> // Inclusion de <limits.h> pour PATH_MAX
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

// include for readline
# include "../libs/readline/inc/history.h"
# include "../libs/readline/inc/readline.h"
// include for libft
# include "../libs/libft/inc/libft.h"

# include "typedefs.h"



//Getenv
void init_env(t_env *env);

// Init
void init(t_minishell *minishell);

// Builtins
int exec_env(t_env *env);
int exec_pwd(void);


#endif