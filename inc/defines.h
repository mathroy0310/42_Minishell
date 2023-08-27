/* ************************************************************************** */
/*                                                                            */
/*                                                     ██   ██ ██████         */
/*   defines.h                                         ██   ██      ██        */
/*                                                     ███████  █████         */
/*   By: maroy <maroy@student.42.qc>                        ██ ██             */
/*                                                          ██ ███████.qc     */
/*   Created: 2023/08/25 15:19:10 by maroy                                    */
/*   Updated: 2023/08/27 15:30:04 by maroy            >(.)__ <(.)__ =(.)__    */
/*                                                     (___/  (___/  (___/    */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

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

# define HISTORY_FILE "/tmp/.minishell_command_history"
# define TMP_FILE "/tmp/.minishell_here_doc"
# define INFILE 0
# define OUTFILE 1

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

#endif