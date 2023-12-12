/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 16:36:10 by maroy             #+#    #+#             */
/*   Updated: 2023/12/11 19:23:01 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_valid_fd(t_data *data, char *filename, int fd)
{
	if (fd < 0)
	{
		ft_putstr_err(FT_RED ERR_PROMPT);
		ft_putstr_err(filename);
		ft_putstr_errnl(": No such file or directory" FT_COLOR_RESET);
		data->redir->is_error = TRUE;
		g_global->exit_status = EXIT_FAILURE;
	}
}

void	setup_infiles(t_cmd *cmd, t_data *data, int i)
{
	int	fd;

	if (cmd->redir[i].type == less && !data->redir->is_error)
	{
		fd = open(cmd->redir[i].filename, O_RDONLY);
		data->redir->infile = fd;
		check_valid_fd(data, cmd->redir[i].filename, fd);
	}
	if (!data->redir->is_error)
	{
		if (dup2(data->redir->infile, STDIN_FILENO) == -1)
		{
			ft_close(data->redir->infile);
			print_error("Unable to duplicate file descriptor.");
		}
		ft_close(data->redir->infile);
	}
	ft_close(data->redir->infile);
}

void	setup_outfiles(t_cmd *cmd, t_data *data, int i)
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
		dup2(data->redir->outfile, STDOUT_FILENO);
		ft_close(data->redir->outfile);
	}
	ft_close(data->redir->outfile);
}

t_bool	redirections_all_setup(t_cmd *cmd, t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (++i < cmd->nbr_cmd)
	{
		j = -1;
		//check_for_heredoc(&data[i], &cmd[i]);
		while (++j < cmd[i].redir_nbr)
		{
			if (cmd[i].redir[j].type == less)
				setup_infiles(&cmd[i], &data[i], j);
			if ((cmd[i].redir[j].type == great || cmd[i].redir[j].type == greater) && !data->redir->is_error)
				setup_outfiles(&cmd[i], &data[i], j);
		}
		if (data->redir->is_error)
			return (FALSE);
	}
	return (TRUE);
}

t_bool	redirections_setup(t_cmd *cmd, t_data *data)
{
	int i;

	i = 0;
	while (i < cmd->redir_nbr)
	{
		//check_for_heredoc(data[i], cmd[i]);
		if (cmd->redir[i].type == less)
			setup_infiles(cmd, data, i);
		if ((cmd->redir[i].type == greater || cmd->redir[i].type == great)
			&& !data->redir->is_error)
			setup_outfiles(cmd, data, i);
		i++;
	}
	if (data->redir->is_error)
		return (FALSE);
	return (TRUE);
}