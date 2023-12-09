/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 16:20:59 by maroy             #+#    #+#             */
/*   Updated: 2023/12/09 17:29:40 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	restore_std_fd(t_data *data)
{
	dup2(data->saved_stdin_fd, STDIN_FILENO);
	dup2(data->saved_stdout_fd, STDOUT_FILENO);
	ft_close(data->saved_stdout_fd);
	ft_close(data->saved_stdin_fd);
}
void	free_data(t_data *data, t_cmd *cmd)
{
	int	i;

	restore_std_fd(data);
	if (cmd->nbr_cmd == 1)
	{
		ft_free(data->redir);
		ft_free(data);
	}
	else
	{
		i = cmd->nbr_cmd - 1;
		while (i >= 0)
		{
			// if (data[i].redir->pipe_fd != NULL)
			// 	pipe_free(data[i].redir->pipe_fd, cmd->nbr_cmd);
			ft_free(data[i].redir);
			i--;
		}
		free(data);
	}
}

void	free_child(t_cmd *cmd, t_data *data)
{
	free_state(data->state);
	free_data(data, cmd);
	free_cmd(cmd);
	free_global();
}
