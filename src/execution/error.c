/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 13:56:32 by maroy             #+#    #+#             */
/*   Updated: 2023/09/11 14:10:04 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	print_error(char *file_error)
{
	ft_putstr_fd (RED"minishell: ", STDERR_FILENO);
	ft_putstr_fd (file_error, STDERR_FILENO);
	perror(" ");
}

void	check_valid_fd(t_data *data, char *file_error, int fd)
{
	if (fd < 0)
	{
		data->redir->error = 1;
		ft_putstr_fd (RED"minishell: ", STDERR_FILENO);
		ft_putstr_fd(file_error, STDERR_FILENO);
		perror(" ");
		g_global->exit_status = 1;
	}
}

void	fork_failed(void)
{
	ft_putstr_fd(RED"Fork failed"DEFAULT, STDERR_FILENO);
	exit(EXIT_FAILURE);
}

void	not_valid_id(char *arg)
{
	ft_putstr_fd (RED"minishell: unset: `", STDERR_FILENO);
	ft_putstr_fd (arg, STDERR_FILENO);
	ft_putendl_fd ("': not a valid identifier"DEFAULT, STDERR_FILENO);
	g_global->exit_status = 1;
}