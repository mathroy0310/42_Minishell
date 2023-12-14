/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_multi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 02:31:18 by maroy             #+#    #+#             */
/*   Updated: 2023/12/12 17:36:33 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_pipes(t_cmd *cmd, t_data *data)
{
	int	i;

	i = -1;
	while (cmd->nbr_cmd > ++i)
	{
		pipe(data[i].redir->pipe_fd[i]);
	}
}

static void	left_pipe(t_data *data)
{
	if (data->redir->infile && !data->redir->is_error)
		dup2(data->redir->infile, STDIN_FILENO);
	else if (data->state->read_end != STDIN_FILENO)
	{
		dup2(data->state->read_end, STDIN_FILENO);
		close(data->state->read_end);
	}
}

static void	right_pipe(t_data *data)
{
	if (data->redir->outfile && !data->redir->is_error)
		dup2(data->redir->outfile, STDOUT_FILENO);
	else if (data->state->write_end != STDOUT_FILENO)
	{
		dup2(data->state->write_end, STDOUT_FILENO);
		close(data->state->write_end);
	}
}

t_u8	execute_multi_cmd(t_cmd *cmd, t_data *data, t_state *state)
{
	int i;
	int ret;

	ret = EXIT_SUCCESS;
	i = -1;
	if (DEBUG)
		ft_debug_printf(" -- execute_multi_cmd -- ");
	redirections_all_setup(cmd, data);
	init_pipes(cmd, data);
	data->state->read_end = 0;
	while (cmd->nbr_cmd > ++i)
	{
		init_data(&data[i], state);
		if (cmd[i].redir_nbr > 0)
			ret = execute_simple_cmd(&cmd[i], &data[i]);
		else
			ret = execute_regular_cmd(&cmd[i], &data[i]);
	}

	return (ret);
}