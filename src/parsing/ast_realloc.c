/* ************************************************************************** */
/*                                                                            */
/*                                                     ██   ██ ██████         */
/*   ast_realloc.c                                     ██   ██      ██        */
/*                                                     ███████  █████         */
/*   By: maroy <maroy@student.42.qc>                        ██ ██             */
/*                                                          ██ ███████.qc     */
/*   Created: 2023/08/29 21:29:12 by maroy                                    */
/*   Updated: 2023/08/30 15:56:11 by maroy            >(.)__ <(.)__ =(.)__    */
/*                                                     (___/  (___/  (___/    */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_lexer	*init_lexer(t_lexer	*lexer)
{
	lexer = malloc(sizeof(t_lexer));
	if (!lexer)
		return (NULL);
	lexer->buffer = NULL;
	lexer->bufsize = 0;
	lexer->c = ' ';
	lexer->curpos = 0;
	lexer->readpos = 0;
	return (lexer);
}

t_ast	**realloc_ast_node(t_ast *ast, int size)
{
	t_ast	**new;
	int		i;

	if (ast->type == pipe_ast)
	{
		new = (t_ast **)malloc(sizeof(t_ast *) * size);
		i = -1;
		while (++i < ast->pipecmd_size)
			new[i] = ast->pipecmd_values[i];
		new[i] = NULL;
		free(ast->pipecmd_values);
		ast->pipecmd_values = NULL;
		return (new);
	}
	return (NULL);
}

t_token	**realloc_ast_args(t_ast *ast, int size)
{
	t_token	**new;
	int		i;

	if (ast->type == arg_ast)
	{
		new = (t_token **)malloc(sizeof(t_token *) * (size + 1));
		i = -1;
		while (++i < size - 1)
			new[i] = ast->args[i];
		new[i] = NULL;
		free(ast->args);
		ast->args = NULL;
		return (new);
	}
	return (NULL);
}

char	*tokenize_text(t_lexer *lexer, char *s)
{
	char	*str;
	int		i;

	i = 0;
	str = ft_strdup(s);
	while (lexer->c != EOF && !ft_strchar("|>< \"\'", lexer->c))
	{
		while (lexer->c == 32 && lexer->c != EOF)
			readchar(lexer);
		if (lexer->c == DOLLAR)
		{
			str = ft_strjoin_free(str, envar_token(lexer));
			i += 1;
		}
		else if (lexer->c == EOF)
			return (str);
		else
		{
			str = ft_strjoin_char(str, lexer->c);
			readchar(lexer);
		}
	}
	return (str);
}

t_token	*check_token(t_parser *parser, t_ast *ast)
{
	char	*temp;

	if (parser->curr_token->type == illegal)
		return (NULL);
	if (!syntax_error(parser))
		return (NULL);
	if (is_redic(parser->prev_token))
	{
		if (parser->curr_token->type != id)
		{
			print_msg("minishell: syntax error near unexpected token 2",
				parser->curr_token->value);
			return (NULL);
		}
		ast->redir_nbr += 1;
		if (parser->prev_token->type == here_doc)
		{
			temp = parser->curr_token->value;
			parser->curr_token->value = get_stop_word(parser);
			free(temp);
		}
	}
	return (parser->curr_token);
}
