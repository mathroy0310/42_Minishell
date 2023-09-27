/* ************************************************************************** */
/*                                                                            */
/*                                                     ██   ██ ██████         */
/*   free.c                                            ██   ██      ██        */
/*                                                     ███████  █████         */
/*   By: maroy <maroy@student.42.qc>                        ██ ██             */
/*                                                          ██ ███████.qc     */
/*   Created: 2023/08/29 20:33:28 by maroy                                    */
/*   Updated: 2023/09/26 14:27:21 by maroy            >(.)__ <(.)__ =(.)__    */
/*                                                     (___/  (___/  (___/    */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	free_args(t_ast *ast)
{
	int	k;

	k = 0;
	while (k < ast->args_size)
	{
		if (ast->args[k])
		{
			if (ast->args[k]->value)
				free(ast->args[k]->value);
			ast->args[k]->value = NULL;
		}
		if (ast->args[k])
			free(ast->args[k]);
		ast->args[k] = NULL;
		k++;
	}
	free(ast->args);
}

t_ast	*free_tree(t_ast *ast)
{
	int	j;

	if (!ast)
		return (NULL);
	if (ast->type == pipe_ast)
	{
		j = -1;
		while (++j < ast->pipecmd_size)
		{
			if (ast->pipecmd_values[j])
			{
				free_tree((ast->pipecmd_values[j]));
				ast->pipecmd_values[j] = NULL;
			}
		}
		free(ast->pipecmd_values);
	}
	if (ast->type == arg_ast)
		free_args(ast);
	free(ast);
	return (NULL);
}

void	free_parser(t_parser *parser)
{
	free_parser_helper(parser, 1);
	if (parser->prev_token)
	{
		if (parser->prev_token->value)
			free(parser->prev_token->value);
		parser->prev_token->value = NULL;
		free(parser->prev_token);
		parser->prev_token = NULL;
	}
	free(parser);
}

void	free_parser_helper(t_parser *parser, int i)
{
	if (!parser)
		return ;
	if (parser->lexer)
	{
		if (parser->lexer->buffer)
			free(parser->lexer->buffer);
		parser->lexer->buffer = NULL;
		free(parser->lexer);
		parser->lexer = NULL;
	}
	if (parser->curr_token && i == 1)
	{
		if (parser->curr_token->value)
			free(parser->curr_token->value);
		parser->curr_token->value = NULL;
		free(parser->curr_token);
		parser->curr_token = NULL;
	}
}

void	free_cmd(t_cmd *cmd)
{
	int	i;
	int	j;

	i = -1;
	while (++i < cmd->nbr_cmd)
	{
		j = -1;
		while (++j < cmd[i].args_size)
		{
			if (cmd[i].argvs[j])
				free(cmd[i].argvs[j]);
			cmd[i].argvs[j] = NULL;
		}
		free(cmd[i].argvs);
		j = -1;
		while (++j < cmd[i].redir_nbr)
		{
			if (cmd[i].redir[j].filename)
				free(cmd[i].redir[j].filename);
			cmd[i].redir[j].filename = NULL;
		}
		free(cmd[i].redir);
	}
	free(cmd);
}
