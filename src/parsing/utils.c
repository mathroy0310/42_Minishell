/* ************************************************************************** */
/*                                                                            */
/*                                                     ██   ██ ██████         */
/*   utils.c                                           ██   ██      ██        */
/*                                                     ███████  █████         */
/*   By: maroy <maroy@student.42.qc>                        ██ ██             */
/*                                                          ██ ███████.qc     */
/*   Created: 2023/08/29 20:21:18 by maroy                                    */
/*   Updated: 2023/10/28 16:25:57 by maroy            >(.)__ <(.)__ =(.)__    */
/*                                                     (___/  (___/  (___/    */
/* ************************************************************************** */

#include "minishell.h"

t_token	*init_token(t_token_type type, char *str, t_lexer *lexer)
{
	t_token	*token;

	if (type == eof)
	{
		free(lexer->buffer);
		lexer->buffer = NULL;
	}
	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	if (str)
		token->value = ft_strdup(str);
	else
		token->value = NULL;
	token->type = type;
	token->is_quoted = lexer->is_quoted;
	return (token);
}

void	print_error_msg(char *str, char *var)
{
	ft_putstr_err(ANSI_COLOR_BRIGHT_RED);
	ft_putstr_err(str);
	if (var)
	{
		ft_putstr_err(" `");
		ft_putstr_err(var);
		ft_putstr_err("'");
	}
	ft_putstr_errnl(ANSI_COLOR_RESET);
	g_global->exit_status = EXIT_FAILURE;
}

int	peek_char(t_lexer *lexer)
{
	if (lexer->readpos >= lexer->bufsize)
		return (EOF);
	else
		return (lexer->buffer[lexer->readpos]);
}

bool	is_multi_lines(t_lexer *lexer, char c)
{
	if (lexer->c == EOF)
	{
		if (c == DOUBLE_QUOTE)
			print_error_msg(ERR_PROMPT "syntax error expected \"", NULL);
		else
			print_error_msg(ERR_PROMPT "syntax error expected \'", NULL);
		lexer->is_multi_line = true;
		return (false);
	}
	return (true);
}
