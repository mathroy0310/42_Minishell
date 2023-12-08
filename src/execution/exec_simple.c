/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 14:21:46 by maroy             #+#    #+#             */
/*   Updated: 2023/12/08 16:17:58 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_u8	execute_simple_cmd(t_cmd *cmd, t_data *data)
{
	(void)cmd;
	(void)data;
	if (DEBUG)
	{
		ft_debug_printf(" -- execute_simple_cmd -- ");
		if (ft_is_file_exists(cmd->redir->filename))
			ft_debug_printf("file exists");
		else
			ft_debug_printf("file doesn't exists");
	}
	// if (is_builtin(cmd->argvs[0]))
	// return (execute_builtin(cmd, data));
	return (0);
}