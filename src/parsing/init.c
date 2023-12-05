/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 16:08:10 by maroy             #+#    #+#             */
/*   Updated: 2023/12/05 16:10:23 by maroy            ###   ########.fr       */
/*                                                                            */
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
	token = ft_malloc(sizeof(t_token));
	if (str && ft_strcmp(str, ""))
		token->value = ft_strdup(str);
	else
		token->value = NULL;
	token->type = type;
	token->is_quoted = lexer->is_quoted;
	return (token);
}

t_lexer	*init_lexer(t_lexer *lexer)
{
	lexer = malloc(sizeof(t_lexer));
	if (!lexer)
		return (NULL);
	lexer->buffer = NULL;
	lexer->bufsize = 0;
	lexer->c = SPACE;
	lexer->curpos = 0;
	lexer->readpos = 0;
	return (lexer);
}



void	init_ast(t_ast *ast, t_ast_type type)
{
	ast->type = type;
	ast->pipecmd_values = NULL;
	ast->pipecmd_size = 0;
	ast->args = 0;
	ast->redir_nbr = 0;
	ast->args_size = 0;
}