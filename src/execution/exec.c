/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 18:12:50 by maroy             #+#    #+#             */
/*   Updated: 2023/09/01 14:32:19 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	init_data(t_data *data, t_state *state)
{
	g_global->pid = 1;
	if (state->path != NULL)
		ft_free_tab(state->path);
	//state->path = get_path();
	data->saved_stdout = dup(0);
	data->saved_stdin = dup(1);
	data->state = state;
	data->redir = (t_shell_red *)malloc(sizeof(t_shell_red));
	data->redir->infile = 0;
	data->redir->outfile = 0;
	data->redir->here_doc = 0;
	data->redir->error = 0;
}

int	execute_cmd(t_cmd *cmd, t_data *data)
{
	(void)data;
	if (is_builtin(cmd))
	{
		DEBUG_print_msg("is_builtin == true");
		return (check_builtin(cmd, data));
	}
	return (OK);
}

void	execution(t_cmd *cmd, t_state *state)
{
	t_data *data;

	data = (t_data *)malloc(sizeof(t_data));
	if (cmd->redir_nbr == 0 && cmd->type == eof)
	{
		init_data(data, state);
		execute_cmd(cmd, data);
	}
}