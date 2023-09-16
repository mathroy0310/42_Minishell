/* ************************************************************************** */
/*                                                                            */
/*                                                     ██   ██ ██████         */
/*   defines.h                                         ██   ██      ██        */
/*                                                     ███████  █████         */
/*   By: maroy <maroy@student.42.qc>                        ██ ██             */
/*                                                          ██ ███████.qc     */
/*   Created: 2023/08/25 15:19:10 by maroy                                    */
/*   Updated: 2023/09/16 18:55:53 by maroy            >(.)__ <(.)__ =(.)__    */
/*                                                     (___/  (___/  (___/    */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

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
 *-- Exit Code --
 */
# define EXIT_PERM_DENIED 126
# define EXIT_CMD_NOT_FOUND 127
# define EXIT_INVALID_ARG 128
# define EXIT_SIGFATERR 128
# define EXIT_SIGKILL 129
# define EXIT_SIGINT 130
# define EXIT_SIGQUIT 131


/*
 * -- Global defines --
 */

// 1 == DEBUG mode , 0 == USER mode
# define DEBUG 0

// prompt
# define PROMPT "minishell$ "

// tmp file
# define HISTORY_FILE "./.tmp/.minishell_history"

# define OK 1
# define KO 0

// MAX_PATH_LEN
# define MAX_PATH_LEN 1024

// important char defines
# define PIPE 124
# define GREAT 62
# define LESS 60
# define DQUOTE 34
# define SQUOTE 39
# define DOLLAR 36
# define BSLASH 92
// already exist in the chardefs of readline
//# define SPACE 32

#endif