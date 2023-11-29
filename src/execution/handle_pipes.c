/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 16:34:02 by maroy             #+#    #+#             */
/*   Updated: 2023/11/28 21:06:48 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_cmd_path(t_cmd *cmd, t_data *data, int *p_fd)
{
	int		fd;
	char	*possible_path;

	check_for_errors(cmd, data);
	possible_path = find_path(cmd->argvs[0], data->state->path);
	if (possible_path == NULL)
		possible_path = ft_strdup(cmd->argvs[0]);
	fd = open(possible_path, O_RDONLY);
	if (fd < 0)
		if (path_error_print(cmd, data, possible_path))
		{
			close(fd);
			free(possible_path);	
			exit(127);
		}
	if (p_fd != NULL)
	{
		close(p_fd[0]);
		close(p_fd[1]);
	}
	close(fd);
	if (execve(possible_path, cmd->argvs, g_global->env_var))
		exit(1);
}

int	execute_process(t_cmd *cmd, t_data *data, int *fd)
{
	g_global->pid = fork();
	if (g_global->pid == 0)
	{
		if (data->redir->infile && !data->redir->is_error)
			dup2(data->redir->infile, STDIN_FILENO);
		else if (data->state->read_end != STDIN_FILENO)
		{
			dup2(data->state->read_end, STDIN_FILENO);
			close(data->state->read_end);
		}
		if (data->redir->outfile && !data->redir->is_error)
			dup2(data->redir->outfile, STDOUT_FILENO);
		else if (data->state->write_end != STDOUT_FILENO)
		{
			dup2(data->state->write_end, STDOUT_FILENO);
			close(data->state->write_end);
		}
		if (cmd->argvs != NULL && is_builtin(cmd))
			check_builtin(cmd, data);
		else if (cmd->argvs != NULL)
			execute_cmd_path(cmd, data, fd);
		exit(EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

int	execute_pipe_cmd(t_cmd *cmd, t_data *data)
{
	int	i;

	i = 0;
	data->state->read_end = 0;
	setup_command_pipes(cmd, data);
	while (i < cmd->nbr_cmd - 1)
	{
		pipe(data->redir->pipe_fd[i]);
		data->state->write_end = data->redir->pipe_fd[i][1];
		g_global->pid = execute_process(&cmd[i], &data[i],
			data->redir->pipe_fd[i]);
		close(data->state->write_end);
		if (data->state->read_end != 0)
			close(data->state->read_end);
		data->state->read_end = data->redir->pipe_fd[i][0];
		i++;
	}
	data->state->write_end = STDOUT_FILENO;
	g_global->pid = execute_process(&cmd[i], &data[i], NULL);
	return (OK);
}

void	execute_simple_pipe(t_cmd *cmd, t_data *data, t_state *state)
{
	int	i;

	i = -1;
	while (++i < cmd->nbr_cmd)
		init_data(&data[i], state);
	execute_pipe_cmd(cmd, data);
	g_global->pid = 0;
	close_all_pipes(data->redir->pipe_fd, cmd->nbr_cmd - 1);
	wait_children();
}
