/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_multi_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 14:48:08 by maroy             #+#    #+#             */
/*   Updated: 2023/09/25 02:27:52 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "stdbool.h"

void	execute_multi_cmd(t_cmd *cmd, t_data *data, t_state *state)
{
	(void)data;
	(void)cmd;
	
	int i = 0;
	bool is_redir = false;
	while (i < cmd->nbr_cmd)
	{
		if (cmd[i].redir_nbr != 0)
			is_redir = true;
		i++;	
	}
	if (!is_redir)
	{
		execute_simple_pipe(cmd, data, state);
		return ;
	}
	else
	{
		printf("execute_multi_cmd\n");
	}
	g_global->pid = 0;
}