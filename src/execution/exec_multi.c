/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_multi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maroy <maroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 02:31:18 by maroy             #+#    #+#             */
/*   Updated: 2023/12/11 18:24:10 by maroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	is_redirect_and_pipe(t_cmd *cmd)
{
	int i;

	i = 0;
	while (i < cmd->redir_nbr)
	{
		if (cmd->redir_nbr != 0)
			return (TRUE);
		i++;
	}
	return (FALSE);
}

t_u8	execute_multi_cmd(t_cmd *cmd, t_data *data)
{
	(void)cmd;
	(void)data;
	int ret;

	if (DEBUG)
		ft_debug_printf(" -- execute_multi_cmd -- ");
	ret = check_error(cmd, data);
	if (ret != EXIT_SUCCESS)
		return (ret);
	if (is_redirect_and_pipe(cmd))
	{
		//ret = execute_redirect_and_pipe(cmd, data);	
		return (ret);
	}
	else
		//execute_pipe(cmd, data);
	return (0);
}