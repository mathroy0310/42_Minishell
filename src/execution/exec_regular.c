/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_regular.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 02:31:18 by maroy             #+#    #+#             */
/*   Updated: 2023/12/08 15:59:43 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_u8	execute_regular_cmd(t_cmd *cmd, t_data *data)
{
	(void)cmd;
	(void)data;
	if (DEBUG)
		ft_debug_printf(" -- execute_regular_cmd -- ");
	// if (is_builtin(cmd->argvs[0]))
	// return (execute_builtin(cmd, data));
	return (0);
}