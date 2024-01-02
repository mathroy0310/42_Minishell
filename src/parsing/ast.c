/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 21:29:29 by maroy             #+#    #+#             */
/*   Updated: 2024/01/02 00:12:06 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_cmdargs(t_ast *ast, t_cmd *cmd, int n)
{
	cmd[n].redir_nbr = ast->redir_nbr;
	cmd[n].args_size = ast->args_size - (cmd[n].redir_nbr * 2) - 1;
	cmd[n].redir = ft_malloc(sizeof(t_redir) * ast->redir_nbr);
	if (cmd[n].args_size > 0)
		cmd[n].argvs = ft_malloc(sizeof(char *) * (cmd[n].args_size + 1));
}

static void	cmd_args_size(int n, t_cmd *cmd, int l)
{
	if (l != 0)
	{
		cmd[n].args_size = l;
		cmd[n].argvs[l] = NULL;
	}
}

static void	populate_cmd_from_ast(t_ast *ast, t_cmd *cmd, int n)
{
	t_index	x;

	x = (t_index){.k = 0, .l = 0, .m = 0};
	init_cmdargs(ast, cmd, n);
	if ((ast->args_size - 1) == (ast->redir_nbr * 2))
		cmd[n].argvs = NULL;
	while (x.k < ast->args_size - 1 && (ast->args[x.k]->type != eof
			|| ast->args[x.k]->type != pip))
	{
		if (ast->args[x.k]->type == id && ast->args[x.k]->value)
			cmd[n].argvs[x.l++] = ft_strdup(ast->args[x.k++]->value);
		else
		{
			if (is_redirect(ast->args[++x.k - 1]) && x.k >= 1
				&& x.m < ast->redir_nbr)
			{
				cmd[n].redir[x.m].type = ast->args[x.k - 1]->type;
				cmd[n].redir[x.m].is_quoted = ast->args[x.k]->is_quoted;
				cmd[n].redir[x.m++].filename = \
					ft_strdup(ast->args[x.k++]->value);
			}
		}
	}
	cmd_args_size(n, cmd, x.l);
}

static void	init_cmd(t_cmd cmd)
{
	(void)cmd;
	cmd.args_size = 0;
	cmd.argvs = NULL;
	cmd.redir_nbr = 0;
	cmd.redir = NULL;
}

t_cmd	*parse_pipeline_to_cmd(t_ast *ast)
{
	t_cmd	*cmd;
	t_index	x;

	x = (t_index){.k = 0, .l = -1, .m = -1};
	cmd = ft_malloc(sizeof(t_cmd) * (ast->pipecmd_size + 1));
	if (ast->type == pipe_ast)
	{
		while (++(x.l) < ast->pipecmd_size && x.k < ast->pipecmd_size)
		{
			init_cmd(cmd[x.k]);
			populate_cmd_from_ast(ast->pipecmd_values[x.l], cmd, x.k);
			if (ast->pipecmd_size >= 2 && x.l < ast->pipecmd_size - 1)
				cmd[x.k].type = pip;
			else
				cmd[x.k].type = eof;
			(x.k)++;
		}
		while (++(x.m) < x.k)
			cmd[x.m].nbr_cmd = x.k;
	}
	free_tree(ast);
	return (cmd);
}
