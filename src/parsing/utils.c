/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 20:21:18 by maroy             #+#    #+#             */
/*   Updated: 2024/01/02 00:07:34 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error_msg(char *str, char *var)
{
	ft_putstr_err(FT_RED);
	ft_putstr_err(str);
	if (var)
	{
		ft_putstr_err(" `");
		ft_putstr_err(var);
		ft_putstr_err("'");
	}
	ft_putstr_errnl(FT_COLOR_RESET);
	g_global->exit_status = EXIT_FAILURE;
}

int	peek_char(t_lexer *lexer)
{
	if (lexer->readpos >= lexer->bufsize)
		return (EOF);
	else
		return (lexer->buffer[lexer->readpos]);
}

t_bool	is_multi_lines(t_lexer *lexer, char c)
{
	if (lexer->c == EOF)
	{
		if (c == DOUBLE_QUOTE)
			print_error_msg(ERR_PROMPT "syntax error expected \"", NULL);
		else
			print_error_msg(ERR_PROMPT "syntax error expected \'", NULL);
		lexer->is_multi_line = TRUE;
		return (FALSE);
	}
	return (TRUE);
}
