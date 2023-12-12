/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 16:36:10 by maroy             #+#    #+#             */
/*   Updated: 2023/12/09 17:29:27 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_valid_fd(t_data *data, char *filename, int fd)
{
	if (fd < 0)
	{
		ft_putstr_err(ERR_PROMPT);
		ft_putstr_err(filename);
		ft_putstr_errnl(": No such file or directory");
		data->redir->is_error = TRUE;
		g_global->exit_status = EXIT_FAILURE;
	}
}

t_bool	setup_infiles(t_cmd *cmd, t_data *data, int i)
{
	int	fd;

	if (cmd->redir[i].type == less)
	{
		fd = open(cmd->redir[i].filename, O_RDWR);
		data->redir->infile = fd;
		check_valid_fd(data, cmd->redir[i].filename, fd);
		ft_close(fd);
	}
	if (!data->redir->is_error)
	{
		if (dup2(data->redir->infile, 0) < 0)
		{
			ft_close(data->redir->infile);
			print_error("Unable to duplicate file descriptor.");
			return (FALSE);
		}
		ft_close(data->redir->infile);
	}
	ft_close(data->redir->infile);
	return (TRUE);
}

t_bool	setup_outfiles(t_cmd *cmd, t_data *data, int i)
{
	int	fd;

	if (cmd->redir[i].type == great && !data->redir->is_error)
	{
		fd = open(cmd->redir[i].filename, O_RDWR | O_CREAT | O_TRUNC, S_IRWXU);
		data->redir->outfile = fd;
		check_valid_fd(data, cmd->redir[i].filename, fd);
	}
	else if (cmd->redir[i].type == greater && !data->redir->is_error)
	{
		fd = open(cmd->redir[i].filename, O_RDWR | O_CREAT | O_APPEND, S_IRWXU);
		data->redir->outfile = fd;
		check_valid_fd(data, cmd->redir[i].filename, fd);
	}
	if (!data->redir->is_error)
	{
		dup2(data->redir->outfile, 1);
		ft_close(data->redir->outfile);
	}
	ft_close(data->redir->outfile);
	return (TRUE);
}

int	redirections_setup(t_cmd *cmd, t_data *data)
{
	int i;

	i = 0;
	while (i < cmd->redir_nbr)
	{
		if (cmd->redir[i].type == less)
			setup_infiles(cmd, data, i);
		if ((cmd->redir[i].type == greater || cmd->redir[i].type == great)
			&& !data->redir->is_error)
			setup_outfiles(cmd, data, i);
		i++;
	}
	return (1);
}