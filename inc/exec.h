/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 21:37:15 by maroy             #+#    #+#             */
/*   Updated: 2023/08/29 21:40:14 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "lexer.h"

typedef struct s_state
{
	char			**env_;
	char			**path;
	int				read_end;
	int				write_end;
}	t_state;

typedef struct s_redir
{
	t_token_type	type;
	char			*filename;
	int				is_quoted;
}					t_redir;

typedef struct s_cmd
{
	int				nbr_cmd;
	int				args_size;
	char			**argvs;
	int				redir_nbr;
	t_redir			*r;
	t_token_type	type;
}	t_cmd;

#endif