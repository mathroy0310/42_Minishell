/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 21:49:41 by maroy             #+#    #+#             */
/*   Updated: 2023/09/01 14:31:43 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*
 * -- Libraries Defines --
 */

# define READLINE_LIBRARY
# define HISTORY_LIBRARY

/*
 * -- libc Includes --
 */

# ifdef __APPLE__
#  include <limits.h> // pour PATH_MAX
# endif

# ifdef __linux__
#  include <linux/limits.h> // pour PATH_MAX
# endif

# include <errno.h> // pour errno
# include <fcntl.h>
# include <signal.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h> // pour EXIT_SUCCESS et EXIT_FAILURE
# include <termios.h>
# include <sys/wait.h>
# include <unistd.h>

/*
 * -- Libs Includes --
 */

//  Readline
# include "../libs/readline/inc/history.h"
# include "../libs/readline/inc/readline.h"
#include <readline/readline.h>
#include <readline/history.h>
//  Libft
# include "../libs/libft/inc/libft.h"
// termcap
# include "../libs/termcap/inc/termcap.h"

/*
 * -- Local Includes --
 */

# include "execution.h"
# include "lexer.h"
# include "parser.h"
# include "builtins.h"
# include "defines.h"

/*
 * -- Struct --
 */

typedef struct s_global
{
    char    **env_var;
    int     pid;
    int     exit_status;
}   t_global;

/*
 * -- My Global Variable --
 */
extern t_global *g_global; 


/*
 * -- Prototypes --
 */
uint8_t minishell_master(int argc, char **argv, char**env);


//DEBUG
void    DEBUG_print_tab(char **tab);
void    DEBUG_print_msg(char *msg);
void    DEBUG_print_string(char *msg, char *arg);
void    DEBUG_print_decimal(char *msg, int arg);
void    DEBUG_print_char(char *msg, char arg);
void	DEBUG_print_parser(t_parser *head);

//Signals.c

void	sigint_handler(int signum);

//env.c

int	dup_env_var(char **env);
char	**get_env_(char	**env_);

#endif