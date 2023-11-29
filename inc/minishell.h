/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 21:49:41 by maroy             #+#    #+#             */
/*   Updated: 2023/11/28 21:34:58 by maroy            ###   ########.fr       */
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
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h> // pour EXIT_SUCCESS et EXIT_FAILURE
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>

/*
 * -- Libs Includes --
 */

//  Readline
# include "../libs/readline/inc/history.h"
# include "../libs/readline/inc/readline.h"
# include <readline/history.h>
# include <readline/readline.h>
//	Libft
# include "../libs/libft/inc/libft.h"

/*
 * -- Local Includes --
 */
# include "builtins.h"
# include "defines.h"
# include "execution.h"
# include "lexer.h"
# include "parser.h"

/*
 * -- Struct --
 */

typedef struct s_global
{
	char				**env_var;
	pid_t				pid;
	t_u8				exit_status;
	t_u8				open_fds;
}						t_global;

/*
 * -- My Global Variable --
 */
extern t_global			*g_global;

/*
 * -- Prototypes --
 */
t_u8					minishell_master(char **env);
void					quit_minishell(char *buff);
/*
 * debug.c *
 */

void					debug_print_tab(char **tab);
void					debug_print_msg(char *msg);
void					debug_print_string(char *msg, char *arg);
void					debug_print_decimal(char *msg, int arg);
void					debug_print_char(char *msg, char arg);
void					debug_print_cmd(t_cmd *cmd);


#endif