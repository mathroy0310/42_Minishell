/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 20:33:28 by maroy             #+#    #+#             */
/*   Updated: 2023/12/05 17:08:20 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_args(t_ast *ast)
{
	int	k;

	k = 0;
	while (k < ast->args_size)
	{
		if (ast->args[k])
			ft_free(ast->args[k]->value);
		ft_free(ast->args[k]);
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
		ft_free(parser->prev_token->value);
		ft_free(parser->prev_token);
	}
	free(parser);
}

void	free_parser_helper(t_parser *parser, int i)
{
	if (!parser)
		return ;
	if (parser->lexer)
	{
		ft_free(parser->lexer->buffer);
		ft_free(parser->lexer);
	}
	if (parser->curr_token && i == 1)
	{
		ft_free(parser->curr_token->value);
		ft_free(parser->curr_token);
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
			ft_free(cmd[i].argvs[j]);
		}
		free(cmd[i].argvs);
		j = -1;
		while (++j < cmd[i].redir_nbr)
		{
			ft_free(cmd[i].redir[j].filename);
		}
		free(cmd[i].redir);
	}
	free(cmd);
}
