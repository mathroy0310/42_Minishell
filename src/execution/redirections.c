/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 16:36:10 by maroy             #+#    #+#             */
/*   Updated: 2024/01/02 00:13:39 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_valid_fd(t_data *data, char *filename)
{
	if (access(filename, F_OK) == -1)
	{
		ft_putstr_err(FT_RED ERR_PROMPT);
		ft_putstr_err(filename);
		ft_putstr_err(": No such file or directory");
		ft_putstr_errnl(FT_COLOR_RESET);
		data->redir->is_error = TRUE;
		g_global->exit_status = 127;
	}
	if (access(filename, R_OK) == -1)
	{
		ft_putstr_err(FT_RED ERR_PROMPT);
		ft_putstr_err(filename);
		ft_putstr_err(": Permission denied");
		ft_putstr_errnl(FT_COLOR_RESET);
		data->redir->is_error = TRUE;
		g_global->exit_status = 126;
	}
}

static t_bool	setup_infiles(t_cmd *cmd, t_data *data, int i)
{
	int	fd;

	if (cmd->redir[i].type == less)
	{
		fd = open(cmd->redir[i].filename, O_RDWR);
		data->redir->infile = fd;
		check_valid_fd(data, cmd->redir[i].filename);
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

static t_bool	setup_outfiles(t_cmd *cmd, t_data *data, int i)
{
	int	fd;

	if (cmd->redir[i].type == great && !data->redir->is_error)
	{
		fd = open(cmd->redir[i].filename, O_RDWR | O_CREAT | O_TRUNC, S_IRWXU);
		data->redir->outfile = fd;
		check_valid_fd(data, cmd->redir[i].filename);
	}
	else if (cmd->redir[i].type == greater && !data->redir->is_error)
	{
		fd = open(cmd->redir[i].filename, O_RDWR | O_CREAT | O_APPEND, S_IRWXU);
		data->redir->outfile = fd;
		check_valid_fd(data, cmd->redir[i].filename);
	}
	if (!data->redir->is_error)
	{
		dup2(data->redir->outfile, 1);
		ft_close(data->redir->outfile);
	}
	ft_close(data->redir->outfile);
	return (TRUE);
}

void	redirections_all_setup(t_cmd *cmd, t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (++i < cmd->nbr_cmd)
	{
		j = -1;
		while (++j < cmd[i].redir_nbr)
		{
			if (cmd[i].redir[j].type == less)
				setup_infiles(&cmd[i], &data[i], j);
			if ((cmd[i].redir[j].type == great
					|| cmd[i].redir[j].type == greater)
				&& !data->redir->is_error)
				setup_outfiles(&cmd[i], &data[i], j);
		}
	}
}

void	redirections_setup(t_cmd *cmd, t_data *data)
{
	int	i;

	i = -1;
	while (++i < cmd->redir_nbr)
	{
		if (cmd->redir[i].type == less)
			setup_infiles(cmd, data, i);
		if ((cmd->redir[i].type == greater || cmd->redir[i].type == great)
			&& !data->redir->is_error)
			setup_outfiles(cmd, data, i);
	}
}
