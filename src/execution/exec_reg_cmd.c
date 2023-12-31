/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_reg_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 15:58:19 by maroy             #+#    #+#             */
/*   Updated: 2023/11/28 21:02:16 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <dirent.h>
#include <sys/stat.h>

void	check_for_errors(t_cmd *cmd, t_data *data)
{
	if (!cmd->argvs)
		exit(g_global->exit_status);
	if (data->redir->is_error)
	{
		g_global->exit_status = EXIT_FAILURE;
		exit(g_global->exit_status);
	}
	if (!ft_strcmp(cmd->argvs[0], "\0"))
	{
		ft_putstr_err(ANSI_COLOR_BRIGHT_RED ERR_PROMPT);
		ft_putstr_err(": command not found");
		ft_putstr_errnl(ANSI_COLOR_RESET);
		exit(g_global->exit_status);
	}
}

t_u8	check_for_permission(t_cmd *cmd)
{
	struct stat	sb;
	DIR			*dirp;

	dirp = opendir(cmd->argvs[0]);
	ft_putstr_err(ANSI_COLOR_BRIGHT_RED ERR_PROMPT);
	ft_putstr_err(cmd->argvs[0]);
	if (dirp)
	{
		closedir(dirp);
		ft_putstr_err(": is a directory");
		ft_putstr_errnl(ANSI_COLOR_RESET);
		return (126);
	}
	if (stat(cmd->argvs[0], &sb) == 0)
		ft_putstr_err(": Permission denied");
	else if (!dirp)
	{
		ft_putstr_err(" Not a directory");
		return (127);
	}
	ft_putstr_errnl(ANSI_COLOR_RESET);
	return (126);
}

void	find_cmd_path(t_cmd *cmd, t_data *data)
{
	char	*possible_path;
	int		fd;

	check_for_errors(cmd, data);
	possible_path = find_path(cmd->argvs[0], data->state->path);
	if (possible_path == NULL)
		possible_path = ft_strdup(cmd->argvs[0]);
	fd = open(possible_path, O_RDONLY);
	if (fd < 0)
	{
		if (!path_error_print(cmd, data, possible_path))
		{
			close(fd);
			ft_free(possible_path);
			exit(g_global->exit_status);
		}
	}
	close(fd);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (execve(possible_path, cmd->argvs, g_global->env_var) == -1)
		exit(check_for_permission(cmd));
}

t_u8	execute_reg_cmd(t_cmd *cmd, t_data *data)
{
	pid_t	child_pid;

	if (is_builtin(cmd))
	{
		debug_print_msg("is_builtin == true");
		return (check_builtin(cmd, data));
	}
	else
	{
		debug_print_msg("is_builtin == false");
		g_global->pid = 0;
		child_pid = fork();
		if (child_pid < 0)
			fork_failed();
		else if (child_pid == 0)
			find_cmd_path(cmd, data);
		wait_children();
		g_global->pid = 1;
		restore_std(data->saved_stdout, data->saved_stdin);
	}
	return (OK);
}
