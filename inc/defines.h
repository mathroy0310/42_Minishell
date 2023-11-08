/* ************************************************************************** */
/*                                                                            */
/*                                                     ██   ██ ██████         */
/*   defines.h                                         ██   ██      ██        */
/*                                                     ███████  █████         */
/*   By: maroy <maroy@student.42.qc>                        ██ ██             */
/*                                                          ██ ███████.qc     */
/*   Created: 2023/08/25 15:19:10 by maroy                                    */
/*   Updated: 2023/11/08 15:44:45 by maroy            >(.)__ <(.)__ =(.)__    */
/*                                                     (___/  (___/  (___/    */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

/*
 * -- Color Codes for users --
 */

# define ANSI_COLOR_RESET "\001\x1b[0m\002"
# define ANSI_COLOR_BRIGHT_BLACK "\001\x1b[30;1m\002"
# define ANSI_COLOR_BRIGHT_RED "\001\x1b[31;1m\002"
# define ANSI_COLOR_BRIGHT_GREEN "\001\x1b[32;1m\002"
# define ANSI_COLOR_BRIGHT_YELLOW "\001\x1b[33;1m\002"
# define ANSI_COLOR_BRIGHT_BLUE "\001\x1b[34;1m\002"
# define ANSI_COLOR_BRIGHT_MAGENTA "\001\x1b[35;1m\002"
# define ANSI_COLOR_BRIGHT_CYAN "\001\x1b[36;1m\002"
# define ANSI_COLOR_BRIGHT_WHITE "\001\x1b[37;1m\002"
# define ANSI_STYLE_BOLD "\001\x1b[1m\002"
# define ANSI_STYLE_UNDERLINE "\001\x1b[4m\002"
# define ANSI_STYLE_REVERSED "\001\x1b[7m\002"

# define ERR_SYNTAX "syntax error near unexpected token"
/*
 * -- Global defines --
 */

// 1 == DEBUG mode , 0 == USER mode
# ifdef DEBUG
#  define PROMPT "DEBUG minishell$ "
#  define ERR_PROMPT "DEBUG minishell: "
# else
#  define DEBUG 0
#  define PROMPT "minishell$ "
#  define ERR_PROMPT "minishell: "
# endif

/// @brief Temporary file for command history
# define HISTORY_FILE ".minishell_history"
/// @brief Temporary file for here_doc
# define HERE_DOC_FILE ".minishell_here_doc"

/// @brief Return Success
# define OK 1
/// @brief Return Failure
# define KO 0

# define W EXIT_SUCCESS
# define L EXIT_FAILURE

/*
 * -- Char defines --
 */

/// @brief `|` character
# define PIPE 124
/// @brief `>` character
# define GREAT 62
/// @brief `<` character
# define LESS 60
/// @brief `"` character
# define DOUBLE_QUOTE 34
/// @brief `'` character
# define SINGLE_QUOTE 39
/// @brief `$` character
# define DOLLAR 36
/// @brief `\\` character
# define BSLASH 92
// already exist in the chardefs of readline
//# define SPACE 32

#endif
