/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 02:44:01 by maroy             #+#    #+#             */
/*   Updated: 2023/11/28 21:07:10 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	pipe_free(int **pipe_fd, int nbr_cmd)
{
	int	i;

	i = nbr_cmd - 2;
	while (i >= 0)
	{
		ft_free(pipe_fd[i]);
		pipe_fd[i] = NULL;
		i--;
	}
	ft_free(pipe_fd);
	pipe_fd = NULL;
}

void	free_path(char **path)
{
	int	i;

	i = 0;
	while (path[i])
	{
		free(path[i]);
		path[i] = NULL;
		i++;
	}
	ft_free(path);
	path = NULL;
}

void	main_free(t_data *data, t_cmd *cmd)
{
	int	i;

	if (cmd->nbr_cmd == 1)
	{
		ft_free(data->redir);
		data->redir = NULL;
		ft_free(data);
		data = NULL;
	}
	else
	{
		i = cmd->nbr_cmd - 1;
		while (i >= 0)
		{
			if (data[i].redir->pipe_fd != NULL)
				pipe_free(data[i].redir->pipe_fd, cmd->nbr_cmd);
			ft_free(data[i].redir);
			i--;
		}
		ft_free(data);
	}
}
