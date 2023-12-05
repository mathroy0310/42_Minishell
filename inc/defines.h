/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 15:19:10 by maroy             #+#    #+#             */
/*   Updated: 2023/11/14 01:49:02 by maroy            ###   ########.fr       */
/*                                                                            */
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

# define HISTORY_FILE ".minishell_history"
# define HERE_DOC_FILE ".minishell_here_doc"


# define OK 1
# define KO 0

# define W EXIT_SUCCESS
# define L EXIT_FAILURE

/*
 * -- Char defines --
 */

// `|` character
# define PIPE 124
// `>` character
# define GREAT 62
// `<` character
# define LESS 60
// `"` character
# define DOUBLE_QUOTE 34
// `'` character
# define SINGLE_QUOTE 39
// `$` character
# define DOLLAR 36
// `\\` character
# define BSLASH 92
// already exist in the chardefs of readline
//# define SPACE 32

#endif
