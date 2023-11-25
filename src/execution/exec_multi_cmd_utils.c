/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_multi_cmd_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 18:12:50 by maroy             #+#    #+#             */
/*   Updated: 2023/11/24 18:55:50 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	setup_input(t_cmd *cmd, t_data *data, int j)
{
	int	fd;

	fd = open(cmd->redir[j].filename, O_RDWR);
	if (fd < 0)
	{
		data->redir->is_error = TRUE;
		print_error(cmd->redir[j].filename);
	}
	else
		data->redir->infile = fd;
	close(fd);
}

void	setup_output(t_cmd *cmd, t_data *data, int j)
{
	int	fd;

	fd = 0;
	if (cmd->redir[j].type == great)
	{
		fd = open(cmd->redir[j].filename, O_RDWR | O_CREAT | O_TRUNC, S_IRWXU);
		if (fd < 0)
		{
			data->redir->is_error = TRUE;
			print_error(cmd->redir[j].filename);
		}
		close(fd);
	}
	else if (cmd->redir[j].type == greater)
	{
		fd = open(cmd->redir[j].filename, O_RDWR | O_CREAT | O_APPEND, S_IRWXU);
		if (fd < 0)
		{
			data->redir->is_error = TRUE;
			print_error(cmd->redir[j].filename);
		}
		close(fd);
	}
	data->redir->outfile = fd;
}
