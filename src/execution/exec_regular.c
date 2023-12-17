/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_regular.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 02:31:18 by maroy             #+#    #+#             */
/*   Updated: 2023/12/16 18:37:07 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_u8	execute_regular_cmd(t_cmd *cmd, t_data *data)
{
	int ret;

	if (DEBUG)
		ft_debug_printf(" -- execute_regular_cmd -- ");
	ret = check_error(cmd, data);
	if (ret != EXIT_SUCCESS)
		return (ret);
	if (is_builtin(cmd))
		return (execute_builtin(cmd, data));
	data->cmd_path = find_cmd_path(cmd, data);
	if (!data->cmd_path)
		return (EXIT_FAILURE);
	else
		ret = execute(data->cmd_path, cmd, data);
	return (ret);
}