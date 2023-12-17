/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 14:21:46 by maroy             #+#    #+#             */
/*   Updated: 2023/12/16 19:56:49 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_u8	execute_simple_cmd(t_cmd *cmd, t_data *data)
{
	int ret;

	if (DEBUG)
		ft_debug_printf(" -- execute_simple_cmd -- ");
	redirections_setup(cmd, data);
	ret = check_error(cmd, data);
	if (ret != EXIT_SUCCESS)
		return (ret);
	data->cmd_path = find_cmd_path(cmd, data);
	if (!data->cmd_path)
		return (EXIT_FAILURE);
	if (is_builtin(cmd))
		return (execute_builtin(cmd, data));
	else
		ret = execute(data->cmd_path, cmd, data);
	return (ret);
}