/* ************************************************************************** */
/*                                                                            */
/*                                                     ██   ██ ██████         */
/*   lexer.c                                           ██   ██      ██        */
/*                                                     ███████  █████         */
/*   By: maroy <maroy@student.42.qc>                        ██ ██             */
/*                                                          ██ ███████.qc     */
/*   Created: 2023/08/29 20:15:26 by maroy                                    */
/*   Updated: 2023/08/30 18:14:06 by maroy            >(.)__ <(.)__ =(.)__    */
/*                                                     (___/  (___/  (___/    */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	readchar(t_lexer *lexer)
{
	if (!lexer || !lexer->buffer)
		return ;
	if (lexer->readpos >= lexer->bufsize)
		lexer->c = EOF;
	else
		lexer->c = lexer->buffer[lexer->readpos];
	lexer->curpos = lexer->readpos;
	lexer->readpos++;
}

void	skip_space(t_lexer *lexer)
{
	if (!lexer || !lexer->buffer)
		return ;
	while (lexer->readpos <= lexer->bufsize && (lexer->c == 32
			|| lexer->c == '\t' || lexer->c == '\n'))
		readchar(lexer);
	lexer->is_quoted = 0;
}

t_token	*ret_str(t_lexer *lexer, char *s, int type)
{
	if (type == greater || type == here_doc)
		readchar(lexer);
	readchar(lexer);
	return (init_token(type, s, lexer));
}

t_token	*ret_char(t_lexer *lexer, char c, t_token_type type)
{
	char	str[2];
	t_token	*token;

	str[0] = c;
	str[1] = '\0';
	token = ret_str(lexer, str, type);
	return (token);
}

t_token	*get_next_token(t_lexer *lexer)
{
	while (lexer->c != EOF && (lexer->curpos <= lexer->bufsize))
	{
		skip_space(lexer);
		if (lexer->c == EOF)
			break ;
		if (lexer->c == PIPE)
			return (ret_char(lexer, lexer->c, pip));
		else if (lexer->c == GREAT)
		{
			if (peek_char(lexer) == GREAT)
				return (ret_str(lexer, ">>", greater));
			return (ret_char(lexer, lexer->c, great));
		}
		else if (lexer->c == LESS)
		{
			if (peek_char(lexer) == LESS)
				return (ret_str(lexer, "<<", here_doc));
			return (ret_char(lexer, lexer->c, less));
		}
		else
			return (string_token(lexer));
	}
	return (ret_char(lexer, lexer->c, eof));
}