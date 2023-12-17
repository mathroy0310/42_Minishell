/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 19:46:44 by maroy             #+#    #+#             */
/*   Updated: 2023/12/16 19:49:35 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <dirent.h>

void	not_valid_id(char *arg)
{
	ft_putstr_err(FT_RED ERR_PROMPT "unset: `");
	ft_putstr_err(arg);
	ft_putstr_err("': not a valid identifier");
	ft_putstr_errnl(FT_COLOR_RESET);
	g_global->exit_status = EXIT_FAILURE;
}

int	check_error(t_cmd *cmd, t_data *data)
{
	if (!cmd->argvs)
		return (g_global->exit_status);
	if (data->redir->is_error)
	{
		g_global->exit_status = 1;
		return (g_global->exit_status);
	}
	if (!ft_strcmp(cmd->argvs[0], "\0"))
	{
		ft_putstr_err(ERR_PROMPT);
		ft_putstr_errnl(": command not found");
		return (g_global->exit_status);
	}
	return (g_global->exit_status);
}

int	check_for_permission(t_cmd *cmd)
{
	struct stat	sb;
	DIR			*dirp;

	dirp = opendir(cmd->argvs[0]);
	ft_putstr_err(ERR_PROMPT);
	ft_putstr_err(cmd->argvs[0]);
	if (dirp)
	{
		closedir(dirp);
		ft_putstr_errnl(": is a directory");
		return (126);
	}
	if (stat(cmd->argvs[0], &sb) == 0 || access(cmd->argvs[0], X_OK) != 0)
	{
		ft_putstr_errnl(": Permission denied");
		return (126);
	}
	if (!dirp)
		ft_putstr_errnl(" Not a directory");
	return (126);
}

int	error_message(char *path)
{
	DIR	*folder;
	int	fd;
	int	ret;

	fd = open(path, O_WRONLY);
	folder = opendir(path);
	ft_putstr_err(FT_RED ERR_PROMPT);
	ft_putstr_err(path);
	if (!ft_strchr(path, '/'))
		ft_putstr_errnl(": command not found");
	else if (fd == -1 && !folder)
		ft_putstr_errnl(": No such file or directory");
	else if (fd == -1 && folder)
		ft_putstr_errnl(": is a directory");
	else if (fd != -1 && !folder)
		ft_putstr_errnl(": Permission denied");
	if (!ft_strchr(path, '/') || (fd == -1 && !folder))
		ret = 127;
	else
		ret = 126;
	ft_putstr_err(FT_COLOR_RESET);
	if (folder)
		closedir(folder);
	ft_close(fd);
	return (ret);
}

void	print_error(char *error)
{
	ft_putstr_err(FT_RED ERR_PROMPT);
	ft_putstr_err(error);
	perror(" ");
	ft_putstr_errnl(FT_COLOR_RESET);
}