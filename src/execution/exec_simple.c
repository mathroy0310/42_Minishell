/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 14:21:46 by maroy             #+#    #+#             */
/*   Updated: 2023/12/09 17:30:35 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_u8	execute_simple_cmd(t_cmd *cmd, t_data *data)
{
	int ret;
	char *path;

	if (DEBUG)
		ft_debug_printf(" -- execute_simple_cmd -- ");
	ret = check_error(cmd, data);
	if (ret != EXIT_SUCCESS)
		return (ret);
	redirections_setup(cmd, data);
	if (is_builtin(cmd))
		return (execute_builtin(cmd, data));
	path = find_cmd_path(cmd, data);
	if (!path)
	{
		ft_free(path);
		return (EXIT_FAILURE);
	}
	else
		ret = execute(path, cmd, data);
	ft_free(path);
	return (EXIT_FAILURE);
}