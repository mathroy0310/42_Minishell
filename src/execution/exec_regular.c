/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_regular.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 02:31:18 by maroy             #+#    #+#             */
/*   Updated: 2023/12/09 04:20:30 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_u8	execute(char *path, t_cmd *cmd, t_data *data)
{
	int	ret;

	ret = EXIT_FAILURE;
	g_global->pid = fork();
	if (g_global->pid == -1)
		return (EXIT_FAILURE);
	else if (g_global->pid == 0)
	{
		if (ft_strchr(path, '/'))
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			execve(path, cmd->argvs, data->state->env_);
		}
		ret = error_message(path);
		ft_free(path);
		free_child(cmd, data);
		exit(ret);
	}
	else
		wait_children();
	return (ret);
}

char	*find_path(char *cmd, char **path)
{
	char	*temp;
	char	*possible_path;
	int		i;
	int		fd;

	i = -1;
	if (path == NULL)
		return (NULL);
	while (path[++i])
	{
		temp = ft_strjoin(path[i], "/");
		possible_path = ft_strjoin(temp, cmd);
		ft_free(temp);
		fd = open(possible_path, O_RDONLY);
		if (fd >= 0)
		{
			ft_close(fd);
			return (possible_path);
		}
	}
	ft_free(possible_path);
	ft_close(fd);
	return (NULL);
}

t_u8	path_error_print(t_cmd *cmd, t_data *data, char *possible_path)
{
	if (data->state->path == NULL)
	{
		ft_putstr_err(FT_RED ERR_PROMPT);
		ft_putstr_err(cmd->argvs[0]);
		ft_putstr_err(": No such file or directory");
		ft_putstr_errnl(FT_COLOR_RESET);
		return (KO);
	}
	else if (ft_strncmp(cmd->argvs[0], "./", 2))
	{
		ft_putstr_err(FT_RED ERR_PROMPT);
		ft_putstr_err(possible_path);
		ft_putstr_err(": command not found");
		ft_putstr_errnl(FT_COLOR_RESET);
		return (KO);
	}
	return (OK);
}

char	*find_cmd_path(t_cmd *cmd, t_data *data)
{
	char	*possible_path;
	int		fd;

	possible_path = find_path(cmd->argvs[0], data->state->path);
	if (possible_path == NULL)
	{
		ft_free(possible_path);
		possible_path = ft_strdup(cmd->argvs[0]);
	}
	fd = open(possible_path, O_RDONLY);
	if (fd < 0)
	{
		if (!path_error_print(cmd, data, possible_path))
		{
			ft_close(fd);
			ft_free(possible_path);
			return (NULL);
		}
	}
	ft_close(fd);
	return (possible_path);
}

int	check_for_errors(t_cmd *cmd, t_data *data)
{
	if (!cmd->argvs)
	{
		g_global->exit_status = EXIT_FAILURE;
		return (g_global->exit_status);
	}
	if (data->redir->is_error)
	{
		g_global->exit_status = EXIT_FAILURE;
		return (g_global->exit_status);
	}
	if (!ft_strcmp(cmd->argvs[0], "\0"))
	{
		ft_putstr_err(FT_RED ERR_PROMPT);
		ft_putstr_err(": command not found");
		ft_putstr_errnl(FT_RED);
		g_global->exit_status = EXIT_FAILURE;
		return (g_global->exit_status);
	}
	return (EXIT_SUCCESS);
}

t_u8	execute_regular_cmd(t_cmd *cmd, t_data *data)
{
	(void)cmd;
	(void)data;

	char *path;
	int ret;

	if (DEBUG)
		ft_debug_printf(" -- execute_regular_cmd -- ");
	if (is_builtin(cmd))
		return (execute_builtin(cmd, data));
	ret = check_for_errors(cmd, data);
	if (ret != EXIT_SUCCESS)
		return (ret);
	path = find_cmd_path(cmd, data);
	if (!path)
	{
		ft_free(path);
		return (EXIT_FAILURE);
	}
	else
		execute(path, cmd, data);
	ft_free(path);
	return (EXIT_FAILURE);
}