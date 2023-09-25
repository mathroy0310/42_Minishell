/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 02:44:01 by maroy             #+#    #+#             */
/*   Updated: 2023/09/25 02:50:59 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	pipe_free(int **pipe_fd, int nbr_cmd)
{
	int	i;

	i = nbr_cmd - 2;
	while (i >= 0)
	{
		free(pipe_fd[i]);
		pipe_fd[i] = NULL;
		i--;
	}
	free(pipe_fd);
	pipe_fd = NULL;
}

void	free_path(char **path)
{
	int	i;

	i = 0;
	while (path[i])
	{
		free (path[i]);
		path[i] = NULL;
		i++;
	}
	free(path);
	path = NULL;
}

void	main_free(t_data *data, t_cmd *cmd)
{
	int	i;

	if (cmd->nbr_cmd == 1)
	{
		free(data->redir);
		data->redir = NULL;
		free (data);
		data = NULL;
	}
	else
	{
		i = cmd->nbr_cmd - 1;
		while (i >= 0)
		{
			if (data[i].redir->pipe_fd != NULL)
				pipe_free (data[i].redir->pipe_fd, cmd->nbr_cmd);
			free (data[i].redir);
			i--;
		}
		free(data);
	}
}

void	ft_freeptr(void *ptr)
{
	free(ptr);
	ptr = NULL;
}
