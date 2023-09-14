/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 15:19:10 by maroy             #+#    #+#             */
/*   Updated: 2023/09/14 13:56:52 by maroy            ###   ########.fr       */
/*                                                                            */
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
 *-- Error messages --
 */

/*
 * -- Global defines --
 */

// 1 == DEBUG mode , 0 == USER mode
# define DEBUG 1

// prompt
# define PROMPT YELLOW"minishell$ "DEFAULT

// tmp file
# define HISTORY_FILE "./.tmp/.minishell_history"

# define OK 1
# define KO 0

// MAX_PATH_LEN
#define MAX_PATH_LEN 1024

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