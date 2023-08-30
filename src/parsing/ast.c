/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 21:29:29 by maroy             #+#    #+#             */
/*   Updated: 2023/08/29 21:30:29 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	init_ast(t_ast *ast, t_ast_type type)
{
	ast->type = type;
	ast->pipecmd_values = (void *) 0;
	ast->pipecmd_size = 0;
	ast->args = 0;
	ast->redir_nbr = 0;
	ast->args_size = 0;
}

void	init_cmdargs(t_ast *ast, t_cmd *cmd, int n)
{
	cmd[n].redir_nbr = ast->redir_nbr;
	cmd[n].args_size = ast->args_size - (cmd[n].redir_nbr * 2) - 1;
	cmd[n].r = malloc(sizeof(t_redir) * ast->redir_nbr);
	if (cmd[n].args_size > 0)
		cmd[n].argvs = malloc(sizeof(char *) * (cmd[n].args_size + 1));
}

void	visitor_args(t_ast *ast, t_cmd *cmd, int n)
{
	t_index	x;

	x = (t_index){.k = 0, .l = 0, .m = 0};
	init_cmdargs(ast, cmd, n);
	if ((ast->args_size - 1) == (ast->redir_nbr * 2))
		cmd[n].argvs = NULL;
	while (x.k < ast->args_size - 1 && (ast->args[x.k]->type != eof
			|| ast->args[x.k]->type != pip))
	{
		if (ast->args[x.k]->type == id)
			cmd[n].argvs[x.l++] = ft_strdup(ast->args[x.k++]->value);
		else
		{
			if (is_redic(ast->args[++x.k - 1]) && x.k >= 1
				&& x.m < ast->redir_nbr)
			{
				cmd[n].r[x.m].type = ast->args[x.k - 1]->type;
				cmd[n].r[x.m].is_quoted = ast->args[x.k]->is_quoted;
				cmd[n].r[x.m++].filename = ft_strdup(ast->args[x.k++]->value);
			}
		}
	}
	if (x.l != 0)
		cmd[n].argvs[x.l] = NULL;
}

void	init_cmd(t_cmd cmd)
{
	(void)cmd;
	cmd.args_size = 0;
	cmd.argvs = NULL;
	cmd.redir_nbr = 0;
	cmd.r = NULL;
}

t_cmd	*visitor(t_ast *ast)
{
	t_cmd	*cmd;
	t_index	x;

	x = (t_index){.k = 0, .l = -1, .m = -1};
	cmd = malloc(sizeof(t_cmd) * (ast->pipecmd_size + 1));
	if (!cmd)
		return (NULL);
	if (ast->type == pipe_ast)
	{
		while (++(x.l) < ast->pipecmd_size && x.k < ast->pipecmd_size)
		{
			init_cmd(cmd[x.k]);
			visitor_args(ast->pipecmd_values[x.l], cmd, x.k);
			if (ast->pipecmd_size >= 2 && x.l < ast->pipecmd_size - 1)
				cmd[x.k].type = pip;
			else
				cmd[x.k].type = eof;
			(x.k)++;
		}
		x.m = -1;
		while (++(x.m) < x.k)
			cmd[x.m].nbr_cmd = x.k;
	}
	free_tree(ast);
	return (cmd);
}
