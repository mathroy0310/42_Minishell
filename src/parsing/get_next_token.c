/* ************************************************************************** */
/*                                                                            */
/*                                                     ██   ██ ██████         */
/*   get_next_token.c                                  ██   ██      ██        */
/*                                                     ███████  █████         */
/*   By: maroy <maroy@student.42.qc>                        ██ ██             */
/*                                                          ██ ███████.qc     */
/*   Created: 2023/08/29 20:29:35 by maroy                                    */
/*   Updated: 2023/08/30 18:13:24 by maroy            >(.)__ <(.)__ =(.)__    */
/*                                                     (___/  (___/  (___/    */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*tokenize_dquoted_text(t_lexer *lexer)
{
	char	*str;

	readchar(lexer);
	str = ft_strdup("");
	while (lexer->c != DQUOTE && lexer->c != EOF)
	{
		if (lexer->c == DOLLAR)
			str = ft_strjoin_free(str, envar_token(lexer));
		else
		{
			str = ft_strjoin_char(str, lexer->c);
			readchar(lexer);
		}
	}
	if (!multi_lines(lexer, DQUOTE))
	{
		free(str);
		return (NULL);
	}
	lexer->is_quoted = 1;
	readchar(lexer);
	return (str);
}

char	*tokenize_squoted_text(t_lexer *lexer)
{
	char	*str;

	readchar(lexer);
	str = ft_strdup("");
	while (lexer->c != SQUOTE && lexer->c != EOF)
	{
		str = ft_strjoin_char(str, lexer->c);
		readchar(lexer);
	}
	if (!multi_lines(lexer, SQUOTE))
	{
		free(str);
		return (NULL);
	}
	lexer->is_quoted = 1;
	readchar(lexer);
	return (str);
}

t_token	*return_token(char *str, t_lexer *lexer, int i)
{
	t_token	*token;

	if (i == 0)
	{
		token = init_token(id, str, lexer);
		free(str);
		return (token);
	}
	else
	{
		free(str);
		return (init_token(illegal, NULL, lexer));
	}
	return (NULL);
}

char	*quoted_string(t_lexer *lexer, char *str)
{
	char	*s;

	if (lexer->c == DQUOTE)
	{
		s = tokenize_dquoted_text(lexer);
		if (!ft_strcmp(s, "\0") && !ft_strcmp(str, "\0"))
			g_global->exit_status = 127;
	}
	else
	{
		s = tokenize_squoted_text(lexer);
		if (!ft_strcmp(s, "\0") && !ft_strcmp(str, "\0"))
			g_global->exit_status = 127;
	}
	return (s);
}

t_token	*string_token(t_lexer *lexer)
{
	char	*str;
	char	*s;
	char	*temp;

	str = ft_strdup("");
	while (lexer->curpos <= lexer->bufsize && lexer->c != PIPE && lexer->c != GREAT
		&& lexer->c != LESS && lexer->c != EOF)
	{
		s = ft_strdup("");
		temp = s;
		if (lexer->c == DQUOTE || lexer->c == SQUOTE)
			s = quoted_string(lexer, str);
		else
			s = tokenize_text(lexer, s);
		if (!s && lexer->multi_line == 1)
		{
			free(temp);
			return (return_token(str, lexer, 1));
		}
		str = ft_strjoin_free(str, s);
		free(temp);
		if (lexer->c == 32)
			return (return_token(str, lexer, 0));
	}
	return (return_token(str, lexer, 0));
}