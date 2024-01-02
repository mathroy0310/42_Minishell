/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_multi_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 00:34:27 by maroy             #+#    #+#             */
/*   Updated: 2024/01/02 00:12:19 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	setup_pipes(t_cmd *cmd, t_data *data)
{
	int	i;

	i = -1;
	data->redir->pipe_fd = (int **)ft_malloc(sizeof(int *) * cmd->nbr_cmd - 1);
	while (++i < cmd->nbr_cmd - 1)
	{
		data->redir->pipe_fd[i] = (int *)ft_malloc(sizeof(int) * 2);
		data->redir->pipe_fd[i][0] = -1;
		data->redir->pipe_fd[i][1] = -1;
	}
}

void	close_pipe(int *fd)
{
	if (fd != NULL)
	{
		ft_close(fd[0]);
		ft_close(fd[1]);
	}
}

void	close_all_pipes(int **fd, int nbr_cmd)
{
	int	i;

	i = -1;
	while (++i < nbr_cmd)
		close_pipe(fd[i]);
}

void	handle_io_redirection(t_data *data)
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
}
