/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 22:40:21 by maroy             #+#    #+#             */
/*   Updated: 2023/09/29 14:05:29 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	setup_infiles(t_cmd *cmd, t_data *data, int i)
{
	int	fd;

	if (cmd->redir[i].type == less)
	{
		fd = open(cmd->redir[i].filename, O_RDWR);
		data->redir->infile = fd;
		check_valid_fd(data, cmd->redir[i].filename, fd);
	}
	if (!data->redir->is_error)
	{
		if (dup2(data->redir->infile, 0) < 0)
		{
			print_error("Unable to duplicate file descriptor.");
			exit(EXIT_FAILURE);
		}
		close(data->redir->infile);
	}
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
		close(data->redir->outfile);
	}
}

int8_t	redirections_setup(t_cmd *cmd, t_data *data)
{
	int	i;

	i = 0;
	while (i < cmd->redir_nbr)
	{
		if (cmd->redir[i].type == less)
			setup_infiles(cmd, data, i);
		if ((cmd->redir[i].type == greater || cmd->redir[i].type == great) && \
			!data->redir->is_error)
			setup_outfiles(cmd, data, i);
		i++;
	}
	return (OK);
}

void	check_for_heredoc(t_data *data, t_cmd *cmd)
{
	int		i;
	char	*pfree;

	i = -1;
	if ((token_type_count(cmd, here_doc) == 0))
		return ;
	else
	{
		while (++i < cmd->redir_nbr)
		{
			if (cmd->redir[i].type == here_doc)
			{
				parse_here_doc(&cmd->redir[i], data);
				cmd->redir[i].type = less;
				pfree = cmd->redir[i].filename;
				cmd->redir[i].filename = data->redir->filename;
				free (pfree);
			}
		}
	}
}

void	execute_single_cmd(t_cmd *cmd, t_data *data)
{
	pid_t	child_pid;

	redirections_setup(cmd, data);
	if (is_builtin(cmd) && !data->redir->is_error)
	{
		check_builtin(cmd, data);
		restore_std(data->saved_stdout, data->saved_stdin);
		return ;
	}
	else
	{
		child_pid = fork();
		if (child_pid < 0)
			fork_failed();
		else if (child_pid == 0)
			find_cmd_path(cmd, data);
		else
			wait_children();
		restore_std(data->saved_stdout, data->saved_stdin);
	}
}
