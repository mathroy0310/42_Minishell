/* ************************************************************************** */
/*                                                                            */
/*                                                     ██   ██ ██████         */
/*   minishell.h                                       ██   ██      ██        */
/*                                                     ███████  █████         */
/*   By: maroy <maroy@student.42.qc>                        ██ ██             */
/*                                                          ██ ███████.qc     */
/*   Created: 2023/06/26 21:49:41 by maroy                                    */
/*   Updated: 2023/08/27 15:10:06 by maroy            >(.)__ <(.)__ =(.)__    */
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

/*
 * -- Local Includes --
 */

# include "typedefs.h"
# include "defines.h"
# include "prototypes.h"

#endif