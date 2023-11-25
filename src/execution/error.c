/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 13:56:32 by maroy             #+#    #+#             */
/*   Updated: 2023/11/24 18:12:44 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(char *file_error)
{
	ft_putstr_err(ANSI_COLOR_BRIGHT_RED ERR_PROMPT);
	ft_putstr_err(file_error);
	perror(" ");
	ft_putstr_errnl(ANSI_COLOR_RESET);
}

void	check_valid_fd(t_data *data, char *file_error, int fd)
{
	if (fd < 0)
	{
		data->redir->is_error = true;
		ft_putstr_err(ANSI_COLOR_BRIGHT_RED ERR_PROMPT);
		ft_putstr_err(file_error);
		perror(" ");
		ft_putstr_err(ANSI_COLOR_RESET);
		g_global->exit_status = EXIT_FAILURE;
	}
}

void	fork_failed(void)
{
	ft_putstr_err(ANSI_COLOR_BRIGHT_RED "Fork failed");
	ft_putstr_errnl(ANSI_COLOR_RESET);
	exit(EXIT_FAILURE);
}

void	not_valid_id(char *arg)
{
	ft_putstr_err(ANSI_COLOR_BRIGHT_RED ERR_PROMPT "unset: `");
	ft_putstr_err(arg);
	ft_putstr_err("': not a valid identifier");
	ft_putstr_errnl(ANSI_COLOR_RESET);
	g_global->exit_status = EXIT_FAILURE;
}

int8_t	path_error_print(t_cmd *cmd, t_data *data, char *possible_path)
{
	if (data->state->path == NULL)
	{
		ft_putstr_err(ANSI_COLOR_BRIGHT_RED ERR_PROMPT);
		ft_putstr_err(cmd->argvs[0]);
		ft_putstr_err(": No such file or directory");
		ft_putstr_errnl(ANSI_COLOR_RESET);
		return (KO);
	}
	else if (ft_strncmp(cmd->argvs[0], "./", 2))
	{
		ft_putstr_err(ANSI_COLOR_BRIGHT_RED ERR_PROMPT);
		ft_putstr_err(possible_path);
		ft_putstr_err(": command not found");
		ft_putstr_errnl(ANSI_COLOR_RESET);
		return (KO);
	}
	return (OK);
}
