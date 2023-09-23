/* ************************************************************************** */
/*                                                                            */
/*                                                     ██   ██ ██████         */
/*   exec_multi_cmd.c                                  ██   ██      ██        */
/*                                                     ███████  █████         */
/*   By: maroy <maroy@student.42.qc>                        ██ ██             */
/*                                                          ██ ███████.qc     */
/*   Created: 2023/09/23 14:48:08 by maroy                                    */
/*   Updated: 2023/09/23 16:40:14 by maroy            >(.)__ <(.)__ =(.)__    */
/*                                                     (___/  (___/  (___/    */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "stdbool.h"

uint8_t	execute_multi_cmd(t_cmd *cmd, t_data *data)
{
	(void)data;
	(void)cmd;
	
	bool is_redir = false;
	int i = 0;
	while (i < cmd->nbr_cmd)
	{
		if (cmd[i].redir_nbr != 0)
			is_redir = true;
		i++;	
	}
	if (!is_redir)
	{
		execute_simple_pipe(cmd, data);
	}
	else
	{
		printf("execute_multi_cmd\n");
	}
	
	return (OK);
}