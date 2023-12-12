/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 00:49:46 by maroy             #+#    #+#             */
/*   Updated: 2023/12/09 20:44:46 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*find_path(char *cmd, char **path)
{
	char	*temp;
	char	*possible_path;
	int		i;
	int		fd;

	i = -1;
	if (cmd[0] == '/')
		return (ft_strdup(cmd));
	while (path[++i])
	{
		temp = ft_strjoin(path[i], "/");
		possible_path = ft_strjoin(temp, cmd);
		//ft_debug_printf("possible_path: %s", possible_path);
		ft_free(temp);
		fd = open(possible_path, O_RDONLY);
		if (fd >= 0)
		{
			ft_close(fd);
			return (possible_path);
		}
	}
	ft_close(fd);
	return (ft_strdup("(null)"));
}

static void	path_error_print(t_cmd *cmd, t_data *data)
{
	ft_putstr_err(FT_RED ERR_PROMPT);
	ft_putstr_err(cmd->argvs[0]);
	if (data->state->path == NULL)
	{
		ft_putstr_err(": No such file or directory");
		ft_putstr_errnl(FT_COLOR_RESET);
		g_global->exit_status = 127;
	}
	else if (ft_strncmp(cmd->argvs[0], "//", 2))
	{
		ft_putstr_err(": No such file or directory");
		ft_putstr_errnl(FT_COLOR_RESET);
		g_global->exit_status = 127;
	}
	else if (ft_strncmp(cmd->argvs[0], "./", 2))
	{
		ft_putstr_err(": command not found");
		ft_putstr_errnl(FT_COLOR_RESET);
		g_global->exit_status = 127;
	}
}

char	*find_cmd_path(t_cmd *cmd, t_data *data)
{
	char	*possible_path;
	int		fd;

	possible_path = find_path(cmd->argvs[0], data->state->path);
	fd = open(possible_path, O_RDONLY);
	if (fd < 0)
	{
		path_error_print(cmd, data);
		ft_close(fd);
		ft_free(possible_path);
		return (NULL);
	}
	ft_close(fd);
	return (possible_path);
}

t_u8	execute(char *path, t_cmd *cmd, t_data *data)
{
	int ret;

	ret = EXIT_FAILURE;
	g_global->pid = fork();
	if (g_global->pid == -1)
		return (EXIT_FAILURE);
	else if (g_global->pid == 0)
	{
		if (ft_strchr(path, '/'))
			execve(path, cmd->argvs, data->state->env_);
		ret = error_message(path);
		ft_free(path);
		free_child(cmd, data);
		exit(ret);
	}
	else
		wait_children();
	return (ret);
}