/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 15:20:18 by maroy             #+#    #+#             */
/*   Updated: 2023/09/01 14:38:23 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

uint8_t	pwd_builtin(void)
{
	char    cwd[PATH_MAX];

	g_global->exit_status = 0;
	if (getcwd(cwd, PATH_MAX))
	{
		ft_putendl_fd(cwd, STDOUT_FILENO);
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}