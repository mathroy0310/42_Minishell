/* ************************************************************************** */
/*                                                                            */
/*                                                     ██   ██ ██████         */
/*   parser_utils.c                                    ██   ██      ██        */
/*                                                     ███████  █████         */
/*   By: maroy <maroy@student.42.qc>                        ██ ██             */
/*                                                          ██ ███████.qc     */
/*   Created: 2023/08/29 21:27:18 by maroy                                    */
/*   Updated: 2023/09/26 14:39:36 by maroy            >(.)__ <(.)__ =(.)__    */
/*                                                     (___/  (___/  (___/    */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_parser	*init_parser(t_lexer *lexer)
{
	t_parser	*parser;

	if (!lexer)
		return (NULL);
	parser = malloc(sizeof(t_parser));
	if (!parser)
		return (NULL);
	parser->lexer = lexer;
	parser->prev_token = NULL;
	parser->curr_token = get_next_token(lexer);
	if (parser->curr_token->type == pip)
	{
		print_error_msg(ERR_PROMPT ERR_SYNTAX,
			parser->curr_token->value);
		free_parser(parser);
		return (NULL);
	}
	if (parser->curr_token->type == illegal)
	{
		free(lexer->buffer);
		lexer->buffer = NULL;
		free_parser(parser);
		return (NULL);
	}
	return (parser);
}

int	is_redirect(t_token *token)
{
	if (token->type == great || token->type == greater || token->type == less
		|| token->type == here_doc)
		return (OK);
	return (KO);
}

char	*quoted_delim(t_parser *parser, char *s, int *i)
{
	char	*word;
	int		start;

	start = *i;
	while (s[*i] != SPACE && s[*i] != LESS)
		(*i)--;
	if (s[(*i) + 1] == DOUBLE_QUOTE || s[(*i) + 1] == SINGLE_QUOTE)
		(*i) += 2;
	if (s[*i] == DOLLAR)
	{
		word = ft_strdup("");
		while ((s[*i] != DOUBLE_QUOTE || s[*i] != SINGLE_QUOTE) && (*i) < start)
		{
			word = ft_strjoin_char(word, s[*i]);
			(*i)++;
		}
	}
	else
		word = ft_strdup(parser->curr_token->value);
	return (word);
}

char	*get_stop_word(t_parser *parser)
{
	int		i;
	char	*s;
	char	*word;

	i = parser->lexer->curpos - 1;
	s = ft_strdup(parser->lexer->buffer);
	if (parser->curr_token->is_quoted == 0)
	{
		while (s[i] != SPACE && s[i] != LESS)
			i--;
		i += 1;
		word = ft_substr(s, i, parser->lexer->curpos - i);
	}
	else
		word = quoted_delim(parser, s, &i);
	free(s);
	return (word);
}

int	syntax_error(t_parser *parser)
{
	if (parser->prev_token->type == pip && parser->curr_token->type == pip)
	{
		print_error_msg(ERR_PROMPT ERR_SYNTAX,
			parser->prev_token->value);
		return (KO);
	}
	if ((is_redirect(parser->prev_token) && parser->curr_token->type == eof)
		|| (parser->prev_token->type == pip && parser->curr_token->type == eof))
	{
		print_error_msg(ERR_PROMPT ERR_SYNTAX, NULL);
		return (KO);
	}
	return (OK);
}
