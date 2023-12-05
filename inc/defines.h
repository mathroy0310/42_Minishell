/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 15:19:10 by maroy             #+#    #+#             */
/*   Updated: 2023/12/05 17:03:01 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

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
// '/' character
# define BACKSLASH 47
// '~' character
# define TILDE 126
// `\\` character
# define BSLASH 92
// already exist in the chardefs of readline
//# define SPACE 32

#endif
