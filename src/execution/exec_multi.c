/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_multi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 02:31:18 by maroy             #+#    #+#             */
/*   Updated: 2023/12/16 20:28:44 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	setup_pipes(t_cmd *cmd, t_data *data)
{
	int	i;

	i = 0;
	data->redir->pipe_fd = (int **)ft_malloc(sizeof(int *) * cmd->nbr_cmd - 1);
	while (i < cmd->nbr_cmd - 1)
	{
		data->redir->pipe_fd[i] = (int *)ft_malloc(sizeof(int) * 2);
		data->redir->pipe_fd[i][0] = -1;
		data->redir->pipe_fd[i][1] = -1;
		i++;
	}
}

void	close_all_pipes(int **fd, int nbr_cmd)
{
	int	i;

	i = -1;
	while (++i < nbr_cmd)
	{
		ft_close(fd[i][0]);
		ft_close(fd[i][1]);
	}
}
void	execute_cmd_path(t_cmd *cmd, t_data *data, int pipe_fd[2])
{
	int	ret;

	if (pipe_fd != NULL)
	{
		ft_close(pipe_fd[0]);
		ft_close(pipe_fd[1]);
	}
	if (ft_strchr(data->cmd_path, '/'))
		execve(data->cmd_path, cmd->argvs, g_global->env_var);
	ret = error_message(data->cmd_path);
	free_child(cmd, data);
	exit(ret);
}

int	execute_process(t_cmd *cmd, t_data *data, int *pipe_fd)
{
	if (data->cmd_path == NULL)
		return (EXIT_FAILURE);
	g_global->pid = fork();
	if (g_global->pid == 0)
	{
		if (data->redir->infile && !data->redir->is_error)
			dup2(data->redir->infile, STDIN_FILENO);
		else if (data->state->read_end != STDIN_FILENO)
		{
			dup2(data->state->read_end, STDIN_FILENO);
			ft_close(data->state->read_end);
		}
		if (data->redir->outfile && !data->redir->is_error)
			dup2(data->redir->outfile, STDOUT_FILENO);
		else if (data->state->write_end != STDOUT_FILENO)
		{
			dup2(data->state->write_end, STDOUT_FILENO);
			ft_close(data->state->write_end);
		}
		if (is_builtin(cmd))
			execute_builtin(cmd, data);
		else
			execute_cmd_path(cmd, data, pipe_fd);
	}
	return (EXIT_FAILURE);
}

void	execute_pipe_cmd(t_cmd *cmd, t_data *data)
{
	int	i;

	i = -1;
	setup_pipes(cmd, data);
	data->state->read_end = 0;
	while (++i < cmd->nbr_cmd - 1)
	{
		pipe(data->redir->pipe_fd[i]);
		data->state->write_end = data->redir->pipe_fd[i][1];
		g_global->pid = execute_process(&cmd[i], &data[i],
				data->redir->pipe_fd[i]);
		ft_close(data->state->write_end);
		if (data->state->read_end != 0)
			ft_close(data->state->read_end);
		data->state->read_end = data->redir->pipe_fd[i][0];
	}
	data->state->write_end = STDOUT_FILENO;
	g_global->pid = execute_process(&cmd[i], &data[i], NULL);
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
		pipe(data->redir->pipe_fd[i]);
		data->state->write_end = data->redir->pipe_fd[i][1];
		g_global->pid = execute_process(&cmd[i], &data[i],
				data->redir->pipe_fd[i]);
		ft_close(data->state->write_end);
		if (data->state->read_end != 0)
			ft_close(data->state->read_end);
		data->state->read_end = data->redir->pipe_fd[i][0];
	}
	data->state->write_end = 1;
	g_global->pid = execute_process(&cmd[i], &data[i], NULL);
}

t_u8	execute_multi_cmd(t_cmd *cmd, t_data *data, t_state *state)
{
	int i;
	int ret;

	ret = EXIT_SUCCESS;
	i = -1;
	if (DEBUG)
		ft_debug_printf(" -- execute_multi_cmd -- ");
	// redirections_all_setup(cmd, data);

	while (cmd->nbr_cmd > ++i)
	{
		init_data(&data[i], state);
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