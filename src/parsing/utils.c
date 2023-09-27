/* ************************************************************************** */
/*                                                                            */
/*                                                     ██   ██ ██████         */
/*   utils.c                                           ██   ██      ██        */
/*                                                     ███████  █████         */
/*   By: maroy <maroy@student.42.qc>                        ██ ██             */
/*                                                          ██ ███████.qc     */
/*   Created: 2023/08/29 20:21:18 by maroy                                    */
/*   Updated: 2023/09/26 14:29:46 by maroy            >(.)__ <(.)__ =(.)__    */
/*                                                     (___/  (___/  (___/    */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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
	ft_putstr_fd(ANSI_COLOR_BRIGHT_RED, STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	if (var)
	{
		ft_putstr_fd(" `", STDERR_FILENO);
		ft_putstr_fd(var, STDERR_FILENO);
		ft_putstr_fd("'", STDERR_FILENO);
	}
	ft_putendl_fd(ANSI_COLOR_RESET, STDERR_FILENO);
	g_global->exit_status = 1;
}

int	peek_char(t_lexer *lexer)
{
	if (lexer->readpos >= lexer->bufsize)
		return (EOF);
	else
		return (lexer->buffer[lexer->readpos]);
}

int	multi_lines(t_lexer *lexer, char c)
{
	if (lexer->c == EOF)
	{
		if (c == DOUBLE_QUOTE)
			print_error_msg(ERR_PROMPT "syntax error expected \"", NULL);
		else
			print_error_msg(ERR_PROMPT "syntax error expected \'", NULL);
		lexer->multi_line = 1;
		return (KO);
	}
	return (OK);
}
