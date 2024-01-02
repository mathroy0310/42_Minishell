/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_regular.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 02:31:18 by maroy             #+#    #+#             */
/*   Updated: 2024/01/02 00:13:27 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_u8	execute_regular_cmd(t_cmd *cmd, t_data *data)
{
	int	ret;

	if (DEBUG)
		ft_debug_printf(" -- execute_regular_cmd -- ");
	ret = check_error(cmd, data);
	if (ret != EXIT_SUCCESS)
		return (ret);
	is_builtin(cmd, data);
	if (data->is_builtin)
		return (execute_builtin(cmd, data));
	if (data->cmd_path)
		ft_free(data->cmd_path);
	data->cmd_path = find_cmd_path(cmd, data);
	if (!data->cmd_path)
		return (EXIT_FAILURE);
	ret = execute(data->cmd_path, cmd, data);
	return (ret);
}
