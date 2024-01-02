/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_multi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 02:31:18 by maroy             #+#    #+#             */
/*   Updated: 2024/01/02 00:13:14 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_cmd_path(t_cmd *cmd, t_data *data, int pipe_fd[2])
{
	int	ret;

	close_pipe(pipe_fd);
	if (ft_strchr(data->cmd_path, '/'))
		execve(data->cmd_path, cmd->argvs, g_global->env_var);
	ret = error_message(data->cmd_path);
	free_child(cmd, data);
	exit(ret);
}

void	execute_process(t_cmd *cmd, t_data *data, int *pipe_fd)
{
	int	ret;

	g_global->pid = fork();
	if (g_global->pid == 0)
	{
		handle_io_redirection(data);
		if (data->is_builtin)
		{
			execute_builtin(cmd, data);
			close_pipe(pipe_fd);
			ret = g_global->exit_status;
		}
		else
		{
			if (ft_strchr(data->cmd_path, '/'))
				execve(data->cmd_path, cmd->argvs, g_global->env_var);
			close_pipe(pipe_fd);
			ret = error_message(data->cmd_path);
		}
		free_child(cmd, data);
		exit(ret);
	}
}

void	execute_pipe_cmd(t_cmd *cmd, t_data *data)
{
	int	i;

	i = -1;
	setup_pipes(cmd, data);
	data->state->read_end = 0;
	while (++i < cmd->nbr_cmd - 1)
	{
		is_builtin(&cmd[i], &data[i]);
		pipe(data->redir->pipe_fd[i]);
		data->state->write_end = data->redir->pipe_fd[i][1];
		execute_process(&cmd[i], &data[i], data->redir->pipe_fd[i]);
		ft_close(data->state->write_end);
		if (data->state->read_end != 0)
			ft_close(data->state->read_end);
		data->state->read_end = data->redir->pipe_fd[i][0];
	}
	data->state->write_end = 1;
	if (data->is_builtin)
		execute_builtin(&cmd[i], &data[i]);
	else
		execute_process(&cmd[i], &data[i], NULL);
}

void	execute_pipe_redir_cmd(t_cmd *cmd, t_data *data)
{
	int	i;

	i = -1;
	setup_pipes(cmd, data);
	redirections_all_setup(cmd, data);
	data->state->read_end = 0;
	while (++i < cmd->nbr_cmd - 1)
	{
		is_builtin(&cmd[i], &data[i]);
		pipe(data->redir->pipe_fd[i]);
		data->state->write_end = data->redir->pipe_fd[i][1];
		execute_process(&cmd[i], &data[i], data->redir->pipe_fd[i]);
		ft_close(data->state->write_end);
		if (data->state->read_end != 0)
			ft_close(data->state->read_end);
		data->state->read_end = data->redir->pipe_fd[i][0];
	}
	data->state->write_end = 1;
	execute_process(&cmd[i], &data[i], NULL);
}

t_u8	execute_multi_cmd(t_cmd *cmd, t_data *data, t_state *state)
{
	int	i;
	int	ret;

	ret = EXIT_SUCCESS;
	i = -1;
	if (DEBUG)
		ft_debug_printf(" -- execute_multi_cmd -- ");
	while (++i < cmd->nbr_cmd)
	{
		init_data(&data[i], state);
		if (data[i].cmd_path)
			ft_free(data[i].cmd_path);
		data[i].cmd_path = find_cmd_path(&cmd[i], &data[i]);
	}
	if (cmd->redir_nbr > 0)
		execute_pipe_cmd(cmd, data);
	else
		execute_pipe_redir_cmd(cmd, data);
	g_global->pid = 0;
	close_all_pipes(data->redir->pipe_fd, cmd->nbr_cmd - 1);
	wait_children();
	return (ret);
}
