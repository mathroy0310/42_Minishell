/* ************************************************************************** */
/*                                                                            */
/*                                                     ██   ██ ██████         */
/*   parser.c                                          ██   ██      ██        */
/*                                                     ███████  █████         */
/*   By: maroy <maroy@student.42.qc>                        ██ ██             */
/*                                                          ██ ███████.qc     */
/*   Created: 2023/08/29 20:13:10 by maroy                                    */
/*   Updated: 2023/09/26 14:37:55 by maroy            >(.)__ <(.)__ =(.)__    */
/*                                                     (___/  (___/  (___/    */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static t_ast	*parse_args_helper(t_parser *parser)
{
	t_ast	*ast;

	ast = malloc(sizeof(t_ast));
	if (!ast)
		return (NULL);
	init_ast(ast, arg_ast);
	ast->args = (t_token **)malloc(sizeof(t_token *) * 2);
	if (!ast->args)
		return (NULL);
	ast->args[1] = NULL;
	if (ast->args_size == 0)
	{
		ast->args[0] = parser->curr_token;
		if (parser->curr_token->type == pip)
		{
			print_error_msg(ERR_PROMPT ERR_SYNTAX,
				parser->curr_token->value);
			free_parser(parser);
			free_tree(ast);
			return (NULL);
		}
		ast->args_size += 1;
	}
	return (ast);
}

static uint8_t	init_parse_args(t_ast *ast, t_parser *parser)
{
	ast->args_size += 1;
	ast->args = realloc_ast_args(ast, ast->args_size);
	parser->prev_token = parser->curr_token;
	parser->curr_token = get_next_token(parser->lexer);
	ast->args[ast->args_size - 1] = check_token(parser, ast);
	if (!ast->args[ast->args_size - 1])
		return (KO);
	return (OK);
}

static t_ast	*parse_args(t_parser *parser)
{
	t_ast		*ast;

	ast = parse_args_helper(parser);
	if (!ast)
		return (NULL);
	while (parser->curr_token->type != eof)
	{
		if (!init_parse_args(ast, parser))
			return (free_tree(ast));
		if (ast->args[ast->args_size - 1]->type == pip)
		{
			parser->prev_token = parser->curr_token;
			parser->curr_token = get_next_token(parser->lexer);
			break ;
		}
		if (ast->args[ast->args_size - 1]->type == eof)
			break ;
	}
	if (!syntax_error(parser))
	{
		if (ast)
			free_tree(ast);
		return (NULL);
	}
	return (ast);
}

static void	parser_multi_cmd(t_ast *ast)
{
	ast->pipecmd_size += 1;
	ast->pipecmd_values = realloc_ast_node(ast, ast->pipecmd_size + 1);
}

t_ast	*parse_pipe(t_parser *parser)
{
	t_ast	*ast;

	ast = malloc(sizeof(t_ast));
	if (!ast)
		return (NULL);
	init_ast(ast, pipe_ast);
	ast->pipecmd_values = (t_ast **)malloc(sizeof(t_ast *) * 2);
	if (!ast->pipecmd_values)
		return (NULL);
	ast->pipecmd_size = 1;
	ast->pipecmd_values[ast->pipecmd_size] = NULL;
	while (parser->curr_token->type != eof)
	{
		ast->pipecmd_values[ast->pipecmd_size - 1] = parse_args(parser);
		if (!ast->pipecmd_values[ast->pipecmd_size - 1])
		{
			free_parser_helper(parser, 1);
			return (free_tree(ast));
		}
		if (parser->prev_token->type == pip)
			parser_multi_cmd(ast);
	}
	free_parser_helper(parser, 0);
	return (ast);
}
