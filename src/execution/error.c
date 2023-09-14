/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 13:56:32 by maroy             #+#    #+#             */
/*   Updated: 2023/09/14 13:01:45 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	print_error(char *file_error)
{
	ft_putstr_fd (RED"minishell: ", STDERR_FILENO);
	ft_putstr_fd (file_error, STDERR_FILENO);
	ft_putendl_fd(DEFAULT, STDERR_FILENO);
	perror(" ");
}

void	check_valid_fd(t_data *data, char *file_error, int fd)
{
	if (fd < 0)
	{
		data->redir->error = 1;
		ft_putstr_fd (RED"minishell: ", STDERR_FILENO);
		ft_putstr_fd(file_error, STDERR_FILENO);
		ft_putendl_fd(DEFAULT, STDERR_FILENO);
		perror(" ");
		g_global->exit_status = 1;
	}
}

void	fork_failed(void)
{
	ft_putstr_fd(RED"Fork failed", STDERR_FILENO);
	ft_putendl_fd(DEFAULT, STDERR_FILENO);
	exit(EXIT_FAILURE);
}

void	not_valid_id(char *arg)
{
	ft_putstr_fd (RED"minishell: unset: `", STDERR_FILENO);
	ft_putstr_fd (arg, STDERR_FILENO);
	ft_putstr_fd ("': not a valid identifier", STDERR_FILENO);
	ft_putendl_fd(DEFAULT, STDERR_FILENO);
	g_global->exit_status = 1;
}

int8_t	path_error_print(t_cmd *cmd, t_data *data, char *possible_path)
{
	if (data->state->path == NULL)
	{
		ft_putstr_fd (RED"minishell: ", STDERR_FILENO);
		ft_putstr_fd (cmd->argvs[0], STDERR_FILENO);
		ft_putstr_fd (": No such file or directory", STDERR_FILENO);
		ft_putendl_fd (DEFAULT, STDERR_FILENO);
		return (KO);
	}
	else if (ft_strncmp(cmd->argvs[0], "./", 2))
	{
		ft_putstr_fd (RED"minishell: ", STDERR_FILENO);
		ft_putstr_fd (possible_path, STDERR_FILENO);
		ft_putstr_fd(": command not found", STDERR_FILENO);
		ft_putendl_fd (DEFAULT, STDERR_FILENO);
		return (KO);
	}
	return (OK);
}
