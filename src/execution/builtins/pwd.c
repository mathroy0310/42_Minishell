/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 15:20:18 by maroy             #+#    #+#             */
/*   Updated: 2023/12/08 20:01:52 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_u8	pwd_builtin(void)
{
	char cwd[PATH_MAX];

	g_global->exit_status = EXIT_SUCCESS;
	if (getcwd(cwd, PATH_MAX))
	{
		ft_putstr_nl(cwd);
		return (EXIT_SUCCESS);
	}
	ft_putstr_nl(get_env_var_by_key("PWD"));
	return (EXIT_FAILURE);
}