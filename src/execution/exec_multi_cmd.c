/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_multi_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 14:48:08 by maroy             #+#    #+#             */
/*   Updated: 2023/09/29 14:09:04 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	pipe_all(t_cmd *cmd, t_data *data)
{
	int	i;

	i = 0;
	data->redir->pipe_fd = (int **)malloc(sizeof(int *) * cmd->nbr_cmd -1);
	while (i < cmd->nbr_cmd - 1)
	{
		data->redir->pipe_fd[i] = (int *)malloc(sizeof(int) * 2);
		data->redir->pipe_fd[i][0] = -1;
		data->redir->pipe_fd[i][1] = -1;
		i++;
	}
}

void redirections_all_setup(t_cmd *cmd, t_data *data)
{
	int i;
	int j;
	i = -1;
	while (++i < cmd->nbr_cmd)
	{
		j = -1;
		check_for_heredoc(&data[i], &cmd[i]);
		while (++j < cmd[i].redir_nbr)
		{
			if (cmd[i].redir[j].type == less)
				setup_input(&cmd[i], &data[i], j);
			if ((cmd[i].redir[j].type == great || cmd[i].redir[j].type == greater) && !data->redir->is_error)
				setup_output(&cmd[i], &data[i], j);
		}
	}
}

void	execute_pipe_redir(t_cmd *cmd, t_data *data, t_state *state)
{
	int	i;

	i = -1;
	while (++i < cmd->nbr_cmd)
		init_data(&data[i], state);
	pipe_all(cmd, data);
	redirections_all_setup(cmd, data);
	i = -1;
	data->state->read_end = 0;
	while (++i < cmd->nbr_cmd - 1)
	{
		pipe(data->redir->pipe_fd[i]);
		data->state->write_end = data->redir->pipe_fd[i][1];
		g_global->pid = execute_process(&cmd[i], &data[i], data->redir->pipe_fd[i]);
		close(data->state->write_end);
		if (data->state->read_end != 0)
			close(data->state->read_end);
		data->state->read_end = data->redir->pipe_fd[i][0];
	}
	data->state->write_end = 1;
	g_global->pid = execute_process(&cmd[i], &data[i], NULL);
}

void	execute_multi_cmd(t_cmd *cmd, t_data *data, t_state *state)
{
	int		i;
	bool	is_redir;

	i = 0;
	is_redir = false;
	while (i < cmd->nbr_cmd)
	{
		if (cmd[i].redir_nbr != 0)
			is_redir = true;
		i++;
	}
	if (!is_redir)
	{
		execute_simple_pipe(cmd, data, state);
		return ;
	}
	else
	{
		execute_pipe_redir(cmd, data, state);
		close_all_pipes(data->redir->pipe_fd, cmd->nbr_cmd - 1);
		wait_children();
	}
	g_global->pid = 0;
}
