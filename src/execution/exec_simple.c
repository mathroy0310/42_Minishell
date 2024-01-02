/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 14:21:46 by maroy             #+#    #+#             */
/*   Updated: 2024/01/02 01:21:47 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_u8	execute_simple_cmd(t_cmd *cmd, t_data *data)
{
	int	ret;

	if (DEBUG)
		ft_debug_printf(" -- execute_simple_cmd -- ");
	redirections_setup(cmd, data);
	ret = check_error(cmd, data);
	if (ret != EXIT_SUCCESS)
		return (ret);
	is_builtin(cmd, data);
	if (data->is_builtin)
		return (execute_builtin(cmd, data));
	is_here_doc(cmd, data);
	if (data->redir->is_here_doc)
		return (execute_here_doc(cmd, data));
	if (data->cmd_path)
		ft_free(data->cmd_path);
	data->cmd_path = find_cmd_path(cmd, data);
	if (!data->cmd_path)
		return (EXIT_FAILURE);
	ret = execute(data->cmd_path, cmd, data);
	return (ret);
}
