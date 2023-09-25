/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipes_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 02:06:20 by maroy             #+#    #+#             */
/*   Updated: 2023/09/25 02:43:19 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	close_all_pipes(int **fd, int nbr_cmd)
{
	int	i;

	i = -1;
	while (++i < nbr_cmd)
	{
		close(fd[i][0]);
		close(fd[i][1]);
	}
}

uint8_t	setup_command_pipes(t_cmd *cmd, t_data *data)
{
	int	i;

	i = 0;
	data->redir->pipe_fd = (int **)malloc(sizeof(int *) * cmd->nbr_cmd - 1);
	while (i < cmd->nbr_cmd - 1)
	{
		data->redir->pipe_fd[i] = (int *)malloc(sizeof(int) * 2);
		data->redir->pipe_fd[i][0] = -1;
		data->redir->pipe_fd[i][1] = -1;
		i++;
	}
	return (OK);
}